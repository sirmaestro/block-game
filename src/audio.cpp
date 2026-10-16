#include "audio.hpp"

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iterator>
#include <optional>
#include <span>
#include <string>
#include <utility>

#include "assets.hpp"

#define STB_VORBIS_HEADER_ONLY // configured by the stb_vorbis target
#include "stb_vorbis.c"

namespace
{

struct SoundFile
{
    const char *name; // file stem: <name>.ogg built in, <name>.ogg or <name>.wav in wave/ to replace it
    int volume_mb; // per-sound attenuation the original set, hundredths of a dB
    bool music;    // follows the music volume rather than the sound volume
};

constexpr SoundFile sound_files[] = {
    {"block", -500, false},   {"title", 0, true},      {"ball", -1200, false},
    {"pad", -1200, false},    {"gameover", 0, true},   {"bgm", 0, true},
    {"clear", 0, true},       {"block2", -200, false}, {"big", -500, false},
    {"small", -500, false},   {"error", 0, false},     {"item", 0, false},
    {"open", 0, false},       {"close", 0, false},     {"change", 0, false},
    {"ending", 0, true},      {"ranking", 0, true},    {"nameentry", 0, true},
    {"mugen", 0, true},       {"reverse", 0, false},
};
static_assert(std::size(sound_files) == static_cast<std::size_t>(Sfx::count));

float millibels_to_gain(double mb)
{
    return mb <= -10000.0 ? 0.0f : static_cast<float>(std::pow(10.0, mb / 2000.0));
}

// the original's volume curve: trunc(-10000 * (1 - (v/128)^0.1)) hundredths of a dB
float slider_to_gain(double slider)
{
    return millibels_to_gain(std::trunc(-10000.0 * (1.0 - std::pow(slider / 128.0, 0.1))));
}

struct Pcm
{
    SDL_AudioSpec spec{};
    std::vector<Uint8> data;
};

std::optional<Pcm> decode_ogg(std::span<const std::uint8_t> file)
{
    int channels = 0, rate = 0;
    short *samples = nullptr;
    const int frames = stb_vorbis_decode_memory(file.data(), static_cast<int>(file.size()), &channels, &rate, &samples);
    if (frames < 0 || !samples)
    {
        return std::nullopt;
    }
    Pcm pcm;
    pcm.spec = {SDL_AUDIO_S16, channels, rate};
    const auto *bytes = reinterpret_cast<const Uint8 *>(samples);
    pcm.data.assign(bytes, bytes + std::size_t(frames) * channels * sizeof(short));
    std::free(samples);
    return pcm;
}

std::optional<Pcm> load_wav(const std::filesystem::path &path)
{
    Pcm pcm;
    Uint8 *buffer = nullptr;
    Uint32 length = 0;
    if (!SDL_LoadWAV(path.string().c_str(), &pcm.spec, &buffer, &length))
    {
        return std::nullopt;
    }
    pcm.data.assign(buffer, buffer + length);
    SDL_free(buffer);
    return pcm;
}

// A sound in wave/ replaces the built-in one, as the original game took all its sounds from there.
std::optional<Pcm> load_sound(const std::filesystem::path &wave_dir, const std::string &name)
{
    std::error_code ec;
    if (const auto wav = wave_dir / (name + ".wav"); std::filesystem::is_regular_file(wav, ec))
    {
        if (auto pcm = load_wav(wav))
        {
            return pcm;
        }
        SDL_Log("could not load %s: %s", wav.string().c_str(), SDL_GetError());
    }
    if (const auto ogg = wave_dir / (name + ".ogg"); std::filesystem::is_regular_file(ogg, ec))
    {
        std::ifstream file{ogg, std::ios::binary};
        const std::vector<std::uint8_t> bytes{std::istreambuf_iterator<char>{file}, {}};
        if (auto pcm = decode_ogg(bytes))
        {
            return pcm;
        }
        SDL_Log("could not decode %s", ogg.string().c_str());
    }
    return decode_ogg(assets::sound(name));
}

}

std::optional<std::vector<std::int16_t>> Audio::decode_builtin(std::string_view name)
{
    const auto pcm = decode_ogg(assets::sound(name));
    if (!pcm || pcm->spec.channels != 1)
    {
        return std::nullopt;
    }
    std::vector<std::int16_t> samples(pcm->data.size() / 2);
    std::memcpy(samples.data(), pcm->data.data(), samples.size() * 2);
    return samples;
}

bool Audio::init(const std::filesystem::path &wave_dir)
{
    device_ = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    if (!device_)
    {
        SDL_Log("no audio device: %s", SDL_GetError());
        return false;
    }

    for (std::size_t i = 0; i < voices_.size(); ++i)
    {
        auto &voice = voices_[i];
        voice.gain = millibels_to_gain(sound_files[i].volume_mb);
        voice.music = sound_files[i].music;

        auto pcm = load_sound(wave_dir, sound_files[i].name);
        if (!pcm)
        {
            continue;
        }
        voice.data = std::move(pcm->data);

        voice.stream = SDL_CreateAudioStream(&pcm->spec, nullptr);
        if (!voice.stream || !SDL_BindAudioStream(device_, voice.stream))
        {
            SDL_DestroyAudioStream(voice.stream);
            voice.stream = nullptr;
            voice.data.clear();
            continue;
        }
        apply_gain(voice);
    }
    return true;
}

void Audio::shutdown()
{
    for (auto &voice : voices_)
    {
        SDL_DestroyAudioStream(voice.stream);
        voice = {};
    }
    if (device_)
    {
        SDL_CloseAudioDevice(device_);
        device_ = 0;
    }
}

void Audio::play(Sfx id, bool loop)
{
    auto &voice = voices_[static_cast<std::size_t>(id)];
    if (!voice.stream)
    {
        return;
    }
    SDL_ClearAudioStream(voice.stream);
    SDL_PutAudioStreamData(voice.stream, voice.data.data(), static_cast<int>(voice.data.size()));
    voice.looping = loop;
}

void Audio::stop(Sfx id)
{
    auto &voice = voices_[static_cast<std::size_t>(id)];
    if (voice.stream)
    {
        SDL_ClearAudioStream(voice.stream);
    }
    voice.looping = false;
}

void Audio::set_volumes(double master, double music, double sound)
{
    master_gain_ = slider_to_gain(master);
    music_gain_ = slider_to_gain(music);
    sound_gain_ = slider_to_gain(sound);
    for (auto &voice : voices_)
    {
        apply_gain(voice);
    }
}

void Audio::update()
{
    for (auto &voice : voices_)
    {
        if (voice.stream && voice.looping &&
            SDL_GetAudioStreamQueued(voice.stream) < static_cast<int>(voice.data.size()))
        {
            SDL_PutAudioStreamData(voice.stream, voice.data.data(), static_cast<int>(voice.data.size()));
        }
    }
}

void Audio::apply_gain(Voice &voice) const
{
    if (voice.stream)
    {
        SDL_SetAudioStreamGain(voice.stream, voice.gain * master_gain_ * (voice.music ? music_gain_ : sound_gain_));
    }
}
