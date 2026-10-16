#pragma once

#include <array>
#include <cstdint>
#include <expected>
#include <string>
#include <string_view>
#include <vector>

namespace stages
{

constexpr int columns = 15;
constexpr int rows = 26;
constexpr int count = 50;
constexpr std::uint8_t empty = 0xff;

// Block types per cell, row-major (index = column + row * columns); `empty` where there is no block.
using Stage = std::array<std::uint8_t, columns * rows>;

// Parses the stage text format documented at the top of assets/stages.txt.
std::expected<std::vector<Stage>, std::string> parse(std::string_view text);

}
