#pragma once

#include <array>
#include <filesystem>
#include <string>

// block130.sys / block130.dat, byte-compatible with the original game's save files.
namespace save
{

constexpr int stages = 50;
constexpr int ranks = 10;
constexpr int empty_time_ms = 5999999; // shows as 99m59s99
constexpr std::size_t max_name_length = 7;

struct RankEntry
{
    int time_ms = empty_time_ms;
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    std::string name = "NoEntry";
};

using RankTable = std::array<RankEntry, ranks>;

struct Data
{
    double volume = 64.0; // options slider, 0..128
    bool show_broken_blocks = true;
    bool free_mode_unlocked = false;
    std::string player_name;
    std::array<RankTable, stages> stage_ranking{};
    RankTable total_ranking{};
};

// Where the save files live: next to the executable if that is writable (like the original),
// otherwise the per-user preferences folder.
std::filesystem::path directory();

Data load(const std::filesystem::path &dir);
bool write(const std::filesystem::path &dir, const Data &data);

// Inserts a time below any equal times; returns the rank 0..9, or 10 if it did not place.
int insert(RankTable &table, int time_ms, const std::string &name);

}
