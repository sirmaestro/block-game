#pragma once

#include <cstdint>
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

// Stage replays.
//
// The simulation is deterministic: one seeded random number generator, a fixed 60 Hz tick with integer
// millisecond timers, and maths that gives the same bits on every platform (dmath.hpp). So a replay only stores
// the starting state and, for each tick in which the physics ran, the player's input: the cursor column the
// paddle follows, whether the left button was held (it lowers the paddle) and how many balls were launched.
namespace replay
{

struct Tick
{
    std::int16_t cursor_x = 0;
    bool left_down = false;
    std::uint8_t launches = 0;

    bool operator==(const Tick &) const = default;
};

struct Replay
{
    std::string pack_id;
    int stage = 0;                // 0-based
    std::uint64_t stage_hash = 0; // stages::hash of the layout it was recorded on
    std::uint32_t seed = 0;       // random number generator state when the stage loaded
    int hit_seg = 0;              // the physics' persistent octant, carried over from earlier stages
    int time_ms = 0;              // stage time at the clear, to check the playback
    std::string name;             // player name
    int year = 0, month = 0, day = 0, hour = 0, minute = 0;
    std::vector<Tick> ticks;

    bool operator==(const Replay &) const = default;
};

std::string encode(const Replay &replay);
std::optional<Replay> decode(std::string_view bytes);

// <data dir>/replays/<pack id>/stageNN.rep: the replay of the stage's best time.
std::filesystem::path best_path(const std::filesystem::path &data_dir, std::string_view pack_id, int stage);

std::optional<Replay> read(const std::filesystem::path &path);
bool write(const std::filesystem::path &path, const Replay &replay);

}
