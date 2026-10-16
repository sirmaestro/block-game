#pragma once

#include <SDL3/SDL.h>

#include <array>
#include <cstdint>
#include <filesystem>
#include <optional>
#include <string_view>
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
// already playing restarts it. The sounds are built in as Ogg Vorbis; a .wav or .ogg of the same name in
// wave_dir replaces one, as the original game played whatever wav files it found there.
class Audio
{
  public:
    bool init(const std::filesystem::path &wave_dir);

    // Decodes a built-in mono sound, for tests.
    static std::optional<std::vector<std::int16_t>> decode_builtin(std::string_view name);
    void shutdown();

    // Stop-then-play, as the game always did.
    void play(Sfx id, bool loop = false);
    void stop(Sfx id);

    // Volume sliders, 0..128 each: the original master volume, and the rebuild's music and sound levels.
    void set_volumes(double master, double music, double sound);

    // Keeps looping sounds fed; call once per frame.
    void update();

  private:
    struct Voice
    {
        SDL_AudioStream *stream{};
        std::vector<Uint8> data;
        float gain = 1.0f;
        bool music = false;
        bool looping = false;
    };

    void apply_gain(Voice &voice) const;

    SDL_AudioDeviceID device_{};
    std::array<Voice, static_cast<std::size_t>(Sfx::count)> voices_{};
    float master_gain_ = 1.0f;
    float music_gain_ = 1.0f;
    float sound_gain_ = 1.0f;
};
