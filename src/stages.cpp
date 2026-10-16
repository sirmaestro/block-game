#include "stages.hpp"

#include <format>

namespace stages
{

std::expected<std::vector<Stage>, std::string> parse(std::string_view text)
{
    constexpr std::string_view type_chars = "0123456789abcdefg";

    std::vector<Stage> result;
    int row = rows;
    int line_number = 0;

    while (!text.empty())
    {
        const auto end = text.find('\n');
        auto line = text.substr(0, end);
        text = end == std::string_view::npos ? std::string_view{} : text.substr(end + 1);
        ++line_number;

        if (!line.empty() && line.back() == '\r')
        {
            line.remove_suffix(1);
        }
        if (line.empty() || line.front() == '#')
        {
            continue;
        }

        if (line.starts_with("stage"))
        {
            if (row != rows)
            {
                return std::unexpected(std::format("line {}: stage {} has only {} rows", line_number, result.size(), row));
            }
            result.emplace_back().fill(empty);
            row = 0;
            continue;
        }

        if (result.empty() || row >= rows)
        {
            return std::unexpected(std::format("line {}: row outside a stage", line_number));
        }
        if (line.size() != columns)
        {
            return std::unexpected(std::format("line {}: expected {} columns, got {}", line_number, columns, line.size()));
        }
        for (int column = 0; column < columns; ++column)
        {
            const char c = line[column];
            if (c == '.')
            {
                continue;
            }
            const auto type = type_chars.find(c);
            if (type == std::string_view::npos)
            {
                return std::unexpected(std::format("line {}: unknown block '{}'", line_number, c));
            }
            result.back()[column + row * columns] = static_cast<std::uint8_t>(type);
        }
        ++row;
    }

    if (row != rows)
    {
        return std::unexpected(std::format("stage {} is incomplete", result.size()));
    }
    if (result.size() != count)
    {
        return std::unexpected(std::format("expected {} stages, found {}", count, result.size()));
    }
    return result;
}

}
