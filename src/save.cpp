#include "save.hpp"

#include <SDL3/SDL.h>

#include <charconv>
#include <chrono>
#include <format>
#include <fstream>
#include <iterator>
#include <optional>
#include <string_view>
#include <vector>

namespace save
{

namespace
{

constexpr const char *sys_file = "block130.sys";
constexpr const char *dat_file = "block130.dat";

// Splits on '$'. The original writes a trailing NUL after the last field.
std::vector<std::string_view> fields(std::string_view text)
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

std::string clean_name(std::string_view s)
{
    std::string name;
    for (const char c : s)
    {
        if (name.size() == max_name_length)
        {
            break;
        }
        if (c >= 0x20 && c <= 0x7e && c != '$')
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

bool write_file(const std::filesystem::path &path, std::string_view contents)
{
    const auto temp = std::filesystem::path{path}.concat(".tmp");
    {
        std::ofstream file{temp, std::ios::binary | std::ios::trunc};
        if (!file || !file.write(contents.data(), static_cast<std::streamsize>(contents.size())))
        {
            return false;
        }
    }
    std::error_code ec;
    std::filesystem::rename(temp, path, ec);
    return !ec;
}

bool is_writable(const std::filesystem::path &dir)
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

}

std::filesystem::path directory()
{
    const std::filesystem::path base{SDL_GetBasePath()};
    if (std::filesystem::exists(base / sys_file) || std::filesystem::exists(base / dat_file) || is_writable(base))
    {
        return base;
    }
    char *pref = SDL_GetPrefPath("KENTA", "BLOCK");
    std::filesystem::path path = pref ? pref : base;
    SDL_free(pref);
    return path;
}

Data load(const std::filesystem::path &dir)
{
    Data data;

    if (const auto sys = read_file(dir / sys_file))
    {
        const auto f = fields(*sys);
        if (f.size() >= 1)
        {
            if (const auto v = to_int(f[0]); v && *v >= 0 && *v <= 128)
            {
                data.volume = *v;
            }
        }
        if (f.size() >= 2)
        {
            data.show_broken_blocks = to_int(f[1]).value_or(1) != 0;
        }
        if (f.size() >= 3)
        {
            data.free_mode_unlocked = to_int(f[2]).value_or(0) == 1;
        }
        if (f.size() >= 4)
        {
            data.player_name = clean_name(f[3]);
        }
    }

    if (const auto dat = read_file(dir / dat_file))
    {
        const auto f = fields(*dat);
        constexpr int per_record = 7;
        for (int record = 0; record < stages * ranks + ranks; ++record)
        {
            const auto first = static_cast<std::size_t>(record * per_record);
            if (first + per_record > f.size())
            {
                break; // short file: remaining records keep their defaults
            }

            RankEntry entry;
            const auto time = to_int(f[first]);
            if (!time || *time <= 0)
            {
                continue; // corrupt record: keep the default rather than an unbeatable time
            }
            entry.time_ms = *time;
            entry.year = to_int(f[first + 1]).value_or(0);
            entry.month = to_int(f[first + 2]).value_or(0);
            entry.day = to_int(f[first + 3]).value_or(0);
            entry.hour = to_int(f[first + 4]).value_or(0);
            entry.minute = to_int(f[first + 5]).value_or(0);
            entry.name = clean_name(f[first + 6]);

            if (record < stages * ranks)
            {
                data.stage_ranking[record / ranks][record % ranks] = std::move(entry);
            }
            else
            {
                data.total_ranking[record - stages * ranks] = std::move(entry);
            }
        }
    }

    return data;
}

bool write(const std::filesystem::path &dir, const Data &data)
{
    std::string sys = std::format("{}${}${}${}$", static_cast<int>(data.volume), data.show_broken_blocks ? 1 : 0,
                                  data.free_mode_unlocked ? 1 : 0, data.player_name);
    sys.push_back('\0');

    std::string dat;
    dat.reserve(14000);
    const auto append = [&dat](const RankEntry &e) {
        std::format_to(std::back_inserter(dat), "{}${}${}${}${}${}${}$", e.time_ms, e.year, e.month, e.day, e.hour,
                       e.minute, e.name);
    };
    for (const auto &table : data.stage_ranking)
    {
        for (const auto &entry : table)
        {
            append(entry);
        }
    }
    for (const auto &entry : data.total_ranking)
    {
        append(entry);
    }
    dat.push_back('\0');

    const bool sys_ok = write_file(dir / sys_file, sys);
    const bool dat_ok = write_file(dir / dat_file, dat);
    return sys_ok && dat_ok;
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

    const auto now = std::chrono::zoned_time{std::chrono::current_zone(), std::chrono::system_clock::now()}
                         .get_local_time();
    const auto days = std::chrono::floor<std::chrono::days>(now);
    const std::chrono::year_month_day ymd{days};
    const std::chrono::hh_mm_ss hms{now - days};

    table[rank] = {time_ms,
                   static_cast<int>(ymd.year()),
                   static_cast<int>(static_cast<unsigned>(ymd.month())),
                   static_cast<int>(static_cast<unsigned>(ymd.day())),
                   static_cast<int>(hms.hours().count()),
                   static_cast<int>(hms.minutes().count()),
                   name};
    return rank;
}

}
