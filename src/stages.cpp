#include "stages.hpp"

#include <algorithm>
#include <format>
#include <fstream>
#include <iterator>
#include <system_error>
#include <utility>

namespace stages
{

std::expected<Pack, std::string> parse(std::string_view text, std::string id, std::string default_name)
{
    constexpr std::string_view type_chars = "0123456789abcdefg";

    Pack pack{std::move(id), std::move(default_name), {}};
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

        if (line.starts_with("name ") && pack.stages.empty())
        {
            std::string name;
            for (const char c : line.substr(5))
            {
                // the bitmap font has printable ASCII only
                if (c >= 0x20 && c <= 0x7e && name.size() < max_name_length)
                {
                    name.push_back(c);
                }
            }
            if (!name.empty())
            {
                pack.name = std::move(name);
            }
            continue;
        }

        if (line.starts_with("stage"))
        {
            if (row != rows)
            {
                return std::unexpected(
                    std::format("line {}: stage {} has only {} rows", line_number, pack.stages.size(), row));
            }
            if (pack.stages.size() == max_count)
            {
                return std::unexpected(std::format("line {}: more than {} stages", line_number, max_count));
            }
            pack.stages.emplace_back().fill(empty);
            row = 0;
            continue;
        }

        if (pack.stages.empty() || row >= rows)
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
            pack.stages.back()[column + row * columns] = static_cast<std::uint8_t>(type);
        }
        ++row;
    }

    if (pack.stages.empty())
    {
        return std::unexpected("no stages");
    }
    if (row != rows)
    {
        return std::unexpected(std::format("stage {} is incomplete", pack.stages.size()));
    }
    return pack;
}

std::vector<Pack> load_directory(const std::filesystem::path &dir, std::vector<std::string> &errors)
{
    std::vector<std::filesystem::path> files;
    std::error_code ec;
    for (const auto &entry : std::filesystem::directory_iterator{dir, ec})
    {
        if (entry.is_regular_file(ec) && entry.path().extension() == ".txt")
        {
            files.push_back(entry.path());
        }
    }
    std::ranges::sort(files);

    std::vector<Pack> packs;
    for (const auto &file : files)
    {
        std::ifstream in{file, std::ios::binary};
        const std::string text{std::istreambuf_iterator<char>{in}, {}};
        const auto stem = file.stem().string();
        auto pack = parse(text, make_id(stem), stem);
        if (pack)
        {
            packs.push_back(std::move(*pack));
        }
        else
        {
            errors.push_back(std::format("{}: {}", file.filename().string(), pack.error()));
        }
    }
    return packs;
}

std::string make_id(std::string_view file_stem)
{
    std::string id;
    for (const char c : file_stem)
    {
        const bool safe = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '-' ||
                          c == '_';
        id.push_back(safe ? c : '_');
    }
    if (id.empty() || id == original_id)
    {
        id = "custom_" + id; // never share the built-in stages' records
    }
    return id;
}

std::uint64_t hash(const Stage &stage)
{
    std::uint64_t h = 0xcbf29ce484222325ull;
    for (const auto cell : stage)
    {
        h = (h ^ cell) * 0x100000001b3ull;
    }
    return h;
}

}
