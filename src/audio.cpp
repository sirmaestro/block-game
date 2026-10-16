#include "audio.hpp"

#include <cmath>

namespace
{

struct SoundFile
{
    const char *name;
    int volume_mb; // per-sound attenuation the original set, hundredths of a dB
};

constexpr SoundFile sound_files[] = {
    {"block.wav", -500},   {"title.wav", 0},     {"ball.wav", -1200},     {"pad.wav", -1200},
    {"gameover.wav", 0},   {"bgm.wav", 0},       {"clear.wav", 0},        {"block2.wav", -200},
    {"big.wav", -500},     {"small.wav", -500},  {"error.wav", 0},        {"item.wav", 0},
    {"open.wav", 0},       {"close.wav", 0},     {"change.wav", 0},       {"ending.wav", 0},
    {"ranking.wav", 0},    {"nameentry.wav", 0}, {"mugen.wav", 0},        {"reverse.wav", 0},
};
static_assert(std::size(sound_files) == static_cast<std::size_t>(Sfx::count));

float millibels_to_gain(double mb)
{
    return mb <= -10000.0 ? 0.0f : static_cast<float>(std::pow(10.0, mb / 2000.0));
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

void Audio::set_master_volume(double slider)
{
    // the original's curve: primary buffer volume = trunc(-10000 * (1 - (v/128)^0.1)) mB
    const double mb = std::trunc(-10000.0 * (1.0 - std::pow(slider / 128.0, 0.1)));
    master_gain_ = millibels_to_gain(mb);
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
        SDL_SetAudioStreamGain(voice.stream, voice.gain * master_gain_);
    }
}
