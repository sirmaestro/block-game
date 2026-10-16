#pragma once

#include <array>
#include <filesystem>
#include <functional>
#include <map>
#include <optional>
#include <string>
#include <string_view>

#include "stages.hpp"

// Progress and rankings, in block.sav. Settings are in block.ini (settings.hpp).
//
// block.sav replaced the original game's block130.sys / block130.dat in 1.50: those had no version, could not
// grow, and split the options between two programs. They are imported once if there is no block.sav yet and
// are never written.
namespace save
{

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

    bool operator==(const RankEntry &) const = default;
};

using RankTable = std::array<RankEntry, ranks>;

// Everything recorded for one stage pack.
struct PackRecords
{
    std::array<RankTable, stages::max_count> stage_ranking{};
    RankTable total_ranking{};
    // Total time when each stage was cleared in the best time-trial run (0 = no such run), for split times.
    std::array<int, stages::max_count> best_splits{};

    bool operator==(const PackRecords &) const = default;
};

struct Data
{
    bool free_mode_unlocked = false; // FREE MODE for the built-in stages; custom packs always have it
    std::string player_name;
    std::map<std::string, PackRecords, std::less<>> packs; // by stages::Pack::id

    PackRecords &records(std::string_view pack_id)
    {
        auto it = packs.find(pack_id);
        return it != packs.end() ? it->second : packs[std::string{pack_id}];
    }

    bool operator==(const Data &) const = default;
};

// Options the original game kept in block130.sys, for importing into block.ini.
struct LegacyOptions
{
    int volume = 64;
    bool show_broken_blocks = true;
};

// Where the save files live: next to the executable if that is writable (like the original), otherwise the
// per-user preferences folder.
std::filesystem::path directory();

// Reads block.sav, or imports block130.sys / block130.dat when there is no block.sav.
Data load(const std::filesystem::path &dir);
bool write(const std::filesystem::path &dir, const Data &data);

// Parses and formats block.sav text; exposed for tests.
Data parse(std::string_view text);
std::string format(const Data &data);

// Parses the original game's files (either may be empty).
Data parse_legacy(std::string_view sys, std::string_view dat);
std::optional<LegacyOptions> load_legacy_options(const std::filesystem::path &dir);

// Inserts a time below any equal times; returns the rank 0..9, or 10 if it did not place.
int insert(RankTable &table, int time_ms, const std::string &name);

// Writes a file through a temporary, so a crash never leaves half a file.
bool write_file(const std::filesystem::path &path, std::string_view contents);

}
