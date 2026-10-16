#pragma once

#include <SDL3/SDL.h>

#include <array>
#include <filesystem>
#include <vector>

// Sound ids, matching the original's EZSound slots.
enum class Sfx
{
    block,
    title,
    ball,
    pad,
    gameover,
    bgm,
    clear,
    block2,
    big,
    small,
    error,
    item,
    open,
    close,
    change,
    ending,
    ranking,
    nameentry,
    mugen,
    reverse,
    count
};

// One voice per sound, like the original's single DirectSound buffer per id: playing a sound that is
// already playing restarts it. Missing wav files are silent, as the original shipped without sounds.
class Audio
{
  public:
    bool init(const std::filesystem::path &wave_dir);
    void shutdown();

    // Stop-then-play, as the game always did.
    void play(Sfx id, bool loop = false);
    void stop(Sfx id);

    // Master volume from the options slider, 0..128.
    void set_master_volume(double slider);

    // Keeps looping sounds fed; call once per frame.
    void update();

  private:
    struct Voice
    {
        SDL_AudioStream *stream{};
        std::vector<Uint8> data;
        float gain = 1.0f;
        bool looping = false;
    };

    void apply_gain(Voice &voice) const;

    SDL_AudioDeviceID device_{};
    std::array<Voice, static_cast<std::size_t>(Sfx::count)> voices_{};
    float master_gain_ = 1.0f;
};
