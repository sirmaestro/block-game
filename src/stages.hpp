#pragma once

#include <array>
#include <cstdint>
#include <expected>
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

namespace stages
{

constexpr int columns = 15;
constexpr int rows = 26;
constexpr int max_count = 50; // the original's 50 stages; a custom pack may have fewer
constexpr std::uint8_t empty = 0xff;
constexpr std::size_t max_name_length = 24;

// Block types per cell, row-major (index = column + row * columns); `empty` where there is no block.
using Stage = std::array<std::uint8_t, columns * rows>;

struct Pack
{
    std::string id;   // "original", or a custom pack's file name; keys its records and replays
    std::string name; // shown in MODE SELECT and the rankings
    std::vector<Stage> stages;
};

inline constexpr std::string_view original_id = "original";

// Parses the stage text format documented at the top of assets/stages.txt: an optional "name <text>" line,
// then 1 to 50 stages. `id` and the default name come from the caller.
std::expected<Pack, std::string> parse(std::string_view text, std::string id, std::string default_name);

// Loads every *.txt pack in `dir` (sorted by file name). Packs that fail to parse are reported in `errors`.
std::vector<Pack> load_directory(const std::filesystem::path &dir, std::vector<std::string> &errors);

// Turns a file name into a pack id that is safe in file names and the save file.
std::string make_id(std::string_view file_stem);

// FNV-1a of a stage's layout, so a replay can tell that its stage was edited.
std::uint64_t hash(const Stage &stage);

}
