#include "save.hpp"

#include <SDL3/SDL.h>

#include <algorithm>
#include <charconv>
#include <format>
#include <fstream>
#include <iterator>
#include <optional>
#include <string_view>
#include <system_error>
#include <utility>
#include <vector>

namespace save
{

namespace
{

constexpr const char *save_file = "block.sav";
constexpr const char *legacy_sys_file = "block130.sys";
constexpr const char *legacy_dat_file = "block130.dat";
constexpr int format_version = 1;
constexpr int legacy_stages = 50;

std::optional<int> to_int(std::string_view s)
{
    int value{};
    const auto [end, error] = std::from_chars(s.data(), s.data() + s.size(), value);
    if (error != std::errc{} || end != s.data() + s.size())
    {
        return std::nullopt;
    }
    return value;
}

std::string_view trim(std::string_view s)
{
    while (!s.empty() && (s.front() == ' ' || s.front() == '\t'))
    {
        s.remove_prefix(1);
    }
    while (!s.empty() && (s.back() == ' ' || s.back() == '\t'))
    {
        s.remove_suffix(1);
    }
    return s;
}

// Printable ASCII the font can draw, at most 7 characters.
std::string clean_name(std::string_view s)
{
    std::string name;
    for (const char c : s)
    {
        if (name.size() == max_name_length)
        {
            break;
        }
        if (c >= 0x20 && c <= 0x7e)
        {
            name.push_back(c);
        }
    }
    return name;
}

std::optional<std::string> read_file(const std::filesystem::path &path)
{
    std::ifstream file{path, std::ios::binary};
    if (!file)
    {
        return std::nullopt;
    }
    return std::string{std::istreambuf_iterator<char>{file}, {}};
}

[[maybe_unused]] bool is_writable(const std::filesystem::path &dir)
{
    const auto probe = dir / ".block_write_test";
    {
        std::ofstream file{probe};
        if (!file)
        {
            return false;
        }
    }
    std::error_code ec;
    std::filesystem::remove(probe, ec);
    return true;
}

// The original's '$'-separated fields; it wrote a trailing NUL after the last one.
std::vector<std::string_view> legacy_fields(std::string_view text)
{
    while (!text.empty() && (text.back() == '\0' || text.back() == '\n' || text.back() == '\r'))
    {
        text.remove_suffix(1);
    }
    std::vector<std::string_view> out;
    while (!text.empty())
    {
        const auto end = text.find('$');
        if (end == std::string_view::npos)
        {
            break; // unterminated trailing field: ignore it
        }
        out.push_back(text.substr(0, end));
        text.remove_prefix(end + 1);
    }
    return out;
}

// "<ms> <yyyy-mm-dd> <hh:mm> <name>"; the name is the rest of the line and may contain spaces.
std::optional<RankEntry> parse_entry(std::string_view value)
{
    const auto take = [&value]() {
        const auto space = value.find(' ');
        const auto token = value.substr(0, space);
        value = space == std::string_view::npos ? std::string_view{} : value.substr(space + 1);
        return token;
    };
    const auto time = to_int(take());
    const auto date = take();
    const auto clock = take();
    if (!time || *time <= 0 || *time > empty_time_ms || date.size() != 10 || clock.size() != 5)
    {
        return std::nullopt;
    }
    RankEntry e;
    e.time_ms = *time;
    e.year = to_int(date.substr(0, 4)).value_or(0);
    e.month = to_int(date.substr(5, 2)).value_or(0);
    e.day = to_int(date.substr(8, 2)).value_or(0);
    e.hour = to_int(clock.substr(0, 2)).value_or(0);
    e.minute = to_int(clock.substr(3, 2)).value_or(0);
    e.name = clean_name(value);
    return e;
}

std::string format_entry(const RankEntry &e)
{
    return std::format("{} {:04}-{:02}-{:02} {:02}:{:02} {}", e.time_ms, e.year, e.month, e.day, e.hour, e.minute,
                       e.name);
}

}

std::filesystem::path directory()
{
    const std::filesystem::path base{SDL_GetBasePath()};
#ifndef __APPLE__
    // portable, like the original; on macOS the base path is inside the app bundle, which must not be written
    if (std::filesystem::exists(base / save_file) || std::filesystem::exists(base / legacy_sys_file) ||
        std::filesystem::exists(base / legacy_dat_file) || is_writable(base))
    {
        return base;
    }
#endif
    char *pref = SDL_GetPrefPath("KENTA", "BLOCK");
    std::filesystem::path path = pref ? pref : base;
    SDL_free(pref);
    return path;
}

// ---- block.sav ------------------------------------------------------------------------------------------
//
//   # comment
//   version = 1
//   name = KENTA
//   free_mode = 1
//   [pack original]
//   stage 1.1 = 12345 2026-10-16 21:05 KENTA     stage 1, rank 1
//   total.1 = 1234567 2026-10-16 21:40 KENTA
//   splits = 12345 30001 ...                     total time at each stage clear in the best run
//
// Empty ranking slots are not written. Unknown keys are ignored, so later versions can add to the file.

Data parse(std::string_view text)
{
    Data data;
    PackRecords *pack = nullptr;

    while (!text.empty())
    {
        const auto end = text.find('\n');
        auto line = text.substr(0, end);
        text = end == std::string_view::npos ? std::string_view{} : text.substr(end + 1);
        if (!line.empty() && line.back() == '\r')
        {
            line.remove_suffix(1);
        }
        if (trim(line).empty() || trim(line).front() == '#')
        {
            continue;
        }
        if (line.starts_with("[pack ") && line.ends_with("]"))
        {
            const auto id = trim(line.substr(6, line.size() - 7));
            pack = id.empty() ? nullptr : &data.records(id);
            continue;
        }

        const auto eq = line.find('=');
        if (eq == std::string_view::npos)
        {
            continue;
        }
        const auto key = trim(line.substr(0, eq));
        auto value = line.substr(eq + 1);
        if (value.starts_with(' '))
        {
            value.remove_prefix(1); // only one space: a name may start or end with spaces
        }

        if (!pack)
        {
            if (key == "name")
            {
                data.player_name = clean_name(value);
            }
            else if (key == "free_mode")
            {
                data.free_mode_unlocked = to_int(trim(value)).value_or(0) == 1;
            }
            continue;
        }

        if (key.starts_with("stage ") || key.starts_with("total."))
        {
            RankEntry *slot = nullptr;
            if (key.starts_with("total."))
            {
                const auto rank = to_int(key.substr(6));
                if (rank && *rank >= 1 && *rank <= ranks)
                {
                    slot = &pack->total_ranking[*rank - 1];
                }
            }
            else
            {
                const auto where = key.substr(6);
                const auto dot = where.find('.');
                const auto stage = to_int(where.substr(0, dot));
                const auto rank = dot == std::string_view::npos ? std::nullopt : to_int(where.substr(dot + 1));
                if (stage && rank && *stage >= 1 && *stage <= stages::max_count && *rank >= 1 && *rank <= ranks)
                {
                    slot = &pack->stage_ranking[*stage - 1][*rank - 1];
                }
            }
            if (slot)
            {
                if (auto entry = parse_entry(value))
                {
                    *slot = std::move(*entry);
                }
            }
        }
        else if (key == "splits")
        {
            std::size_t i = 0;
            auto rest = trim(value);
            while (!rest.empty() && i < pack->best_splits.size())
            {
                const auto space = rest.find(' ');
                pack->best_splits[i++] = std::max(0, to_int(rest.substr(0, space)).value_or(0));
                rest = space == std::string_view::npos ? std::string_view{} : trim(rest.substr(space + 1));
            }
        }
    }
    return data;
}

std::string format(const Data &data)
{
    std::string out = std::format("# BLOCK records. Settings are in block.ini.\n"
                                  "version = {}\n"
                                  "name = {}\n"
                                  "free_mode = {}\n",
                                  format_version, data.player_name, data.free_mode_unlocked ? 1 : 0);
    const RankEntry empty{};
    for (const auto &[id, pack] : data.packs)
    {
        if (pack == PackRecords{})
        {
            continue;
        }
        std::format_to(std::back_inserter(out), "\n[pack {}]\n", id);
        for (int r = 0; r < ranks; ++r)
        {
            if (pack.total_ranking[r] != empty)
            {
                std::format_to(std::back_inserter(out), "total.{} = {}\n", r + 1, format_entry(pack.total_ranking[r]));
            }
        }
        if (std::ranges::any_of(pack.best_splits, [](int ms) { return ms > 0; }))
        {
            out += "splits =";
            for (const int ms : pack.best_splits)
            {
                std::format_to(std::back_inserter(out), " {}", ms);
            }
            out += '\n';
        }
        for (int s = 0; s < stages::max_count; ++s)
        {
            for (int r = 0; r < ranks; ++r)
            {
                if (pack.stage_ranking[s][r] != empty)
                {
                    std::format_to(std::back_inserter(out), "stage {}.{} = {}\n", s + 1, r + 1,
                                   format_entry(pack.stage_ranking[s][r]));
                }
            }
        }
    }
    return out;
}

// ---- the original game's files --------------------------------------------------------------------------
//
// block130.sys: volume$broken$free$name$\0
// block130.dat: 500 stage records then 10 total records, each ms$year$month$day$hour$minute$name$

Data parse_legacy(std::string_view sys, std::string_view dat)
{
    Data data;
    const auto s = legacy_fields(sys);
    if (s.size() >= 3)
    {
        data.free_mode_unlocked = to_int(s[2]).value_or(0) == 1;
    }
    if (s.size() >= 4)
    {
        data.player_name = clean_name(s[3]);
    }

    auto &pack = data.records(stages::original_id);
    const auto f = legacy_fields(dat);
    constexpr int per_record = 7;
    for (int record = 0; record < legacy_stages * ranks + ranks; ++record)
    {
        const auto first = static_cast<std::size_t>(record * per_record);
        if (first + per_record > f.size())
        {
            break; // short file: remaining records keep their defaults
        }
        const auto time = to_int(f[first]);
        if (!time || *time <= 0 || *time >= empty_time_ms)
        {
            continue; // empty or corrupt record
        }
        RankEntry entry;
        entry.time_ms = *time;
        entry.year = to_int(f[first + 1]).value_or(0);
        entry.month = to_int(f[first + 2]).value_or(0);
        entry.day = to_int(f[first + 3]).value_or(0);
        entry.hour = to_int(f[first + 4]).value_or(0);
        entry.minute = to_int(f[first + 5]).value_or(0);
        entry.name = clean_name(f[first + 6]);
        if (record < legacy_stages * ranks)
        {
            pack.stage_ranking[record / ranks][record % ranks] = std::move(entry);
        }
        else
        {
            pack.total_ranking[record - legacy_stages * ranks] = std::move(entry);
        }
    }
    return data;
}

std::optional<LegacyOptions> load_legacy_options(const std::filesystem::path &dir)
{
    const auto sys = read_file(dir / legacy_sys_file);
    if (!sys)
    {
        return std::nullopt;
    }
    LegacyOptions options;
    const auto f = legacy_fields(*sys);
    if (f.size() >= 1)
    {
        if (const auto v = to_int(f[0]); v && *v >= 0 && *v <= 128)
        {
            options.volume = *v;
        }
    }
    if (f.size() >= 2)
    {
        options.show_broken_blocks = to_int(f[1]).value_or(1) != 0;
    }
    return options;
}

// ---- files ----------------------------------------------------------------------------------------------

Data load(const std::filesystem::path &dir)
{
    if (const auto text = read_file(dir / save_file))
    {
        return parse(*text);
    }
    const auto sys = read_file(dir / legacy_sys_file);
    const auto dat = read_file(dir / legacy_dat_file);
    if (sys || dat)
    {
        SDL_Log("importing %s and %s", legacy_sys_file, legacy_dat_file);
        return parse_legacy(sys.value_or(""), dat.value_or(""));
    }
    return {};
}

bool write(const std::filesystem::path &dir, const Data &data)
{
    return write_file(dir / save_file, format(data));
}

bool write_file(const std::filesystem::path &path, std::string_view contents)
{
    std::error_code ec;
    std::filesystem::create_directories(path.parent_path(), ec);
    const auto temp = std::filesystem::path{path}.concat(".tmp");
    {
        std::ofstream file{temp, std::ios::binary | std::ios::trunc};
        if (!file || !file.write(contents.data(), static_cast<std::streamsize>(contents.size())))
        {
            return false;
        }
    }
    std::filesystem::rename(temp, path, ec);
    return !ec;
}

int insert(RankTable &table, int time_ms, const std::string &name)
{
    int rank = 0;
    while (rank < ranks && table[rank].time_ms <= time_ms)
    {
        ++rank;
    }
    if (rank == ranks)
    {
        return ranks;
    }
    for (int i = ranks - 1; i > rank; --i)
    {
        table[i] = table[i - 1];
    }

    // local date and time, as the original's GetLocalTime
    SDL_DateTime now{};
    SDL_Time ticks{};
    if (SDL_GetCurrentTime(&ticks))
    {
        SDL_TimeToDateTime(ticks, &now, true);
    }
    table[rank] = {time_ms, now.year, now.month, now.day, now.hour, now.minute, name};
    return rank;
}

}
