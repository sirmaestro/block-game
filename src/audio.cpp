#include "audio.hpp"

#include <cmath>
#include <iterator>

namespace
{

struct SoundFile
{
    const char *name;
    int volume_mb; // per-sound attenuation the original set, hundredths of a dB
    bool music;    // follows the music volume rather than the sound volume
};

constexpr SoundFile sound_files[] = {
    {"block.wav", -500, false},   {"title.wav", 0, true},      {"ball.wav", -1200, false},
    {"pad.wav", -1200, false},    {"gameover.wav", 0, true},   {"bgm.wav", 0, true},
    {"clear.wav", 0, true},       {"block2.wav", -200, false}, {"big.wav", -500, false},
    {"small.wav", -500, false},   {"error.wav", 0, false},     {"item.wav", 0, false},
    {"open.wav", 0, false},       {"close.wav", 0, false},     {"change.wav", 0, false},
    {"ending.wav", 0, true},      {"ranking.wav", 0, true},    {"nameentry.wav", 0, true},
    {"mugen.wav", 0, true},       {"reverse.wav", 0, false},
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

        const auto path = (wave_dir / sound_files[i].name).string();
        SDL_AudioSpec spec{};
        Uint8 *buffer = nullptr;
        Uint32 length = 0;
        if (!SDL_LoadWAV(path.c_str(), &spec, &buffer, &length))
        {
            continue;
        }
        voice.data.assign(buffer, buffer + length);
        SDL_free(buffer);

        voice.stream = SDL_CreateAudioStream(&spec, nullptr);
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
