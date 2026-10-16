#include "replay.hpp"

#include <format>
#include <fstream>
#include <iterator>
#include <utility>

#include "save.hpp"

namespace replay
{

namespace
{

// File layout, all integers as LEB128 varints:
//   "BLOCKREP" format_version pack_id stage stage_hash seed hit_seg time_ms name year month day hour minute
//   tick_count, then per tick a flags byte (1 left button, 2 cursor moved, 4 launches) followed by the
//   zigzag cursor delta if it moved and the launch count if there were any.
constexpr std::string_view magic = "BLOCKREP";
constexpr std::uint64_t format_version = 1;
constexpr std::uint64_t max_ticks = 60ull * 60 * 100; // 100 minutes, the longest time the HUD can show

void put(std::string &out, std::uint64_t v)
{
    while (v >= 0x80)
    {
        out.push_back(static_cast<char>((v & 0x7f) | 0x80));
        v >>= 7;
    }
    out.push_back(static_cast<char>(v));
}

void put_string(std::string &out, std::string_view s)
{
    put(out, s.size());
    out += s;
}

std::uint64_t zigzag(std::int64_t v)
{
    return (static_cast<std::uint64_t>(v) << 1) ^ static_cast<std::uint64_t>(v >> 63);
}

std::int64_t unzigzag(std::uint64_t v)
{
    return static_cast<std::int64_t>(v >> 1) ^ -static_cast<std::int64_t>(v & 1);
}

class Reader
{
  public:
    explicit Reader(std::string_view bytes) : bytes_(bytes)
    {
    }

    std::optional<std::uint64_t> get()
    {
        std::uint64_t v = 0;
        for (int shift = 0; shift < 64; shift += 7)
        {
            if (bytes_.empty())
            {
                return std::nullopt;
            }
            const auto b = static_cast<std::uint8_t>(bytes_.front());
            bytes_.remove_prefix(1);
            v |= static_cast<std::uint64_t>(b & 0x7f) << shift;
            if (!(b & 0x80))
            {
                return v;
            }
        }
        return std::nullopt;
    }

    std::optional<std::string> get_string(std::size_t max_size)
    {
        const auto size = get();
        if (!size || *size > max_size || *size > bytes_.size())
        {
            return std::nullopt;
        }
        std::string s{bytes_.substr(0, *size)};
        bytes_.remove_prefix(*size);
        return s;
    }

    bool take(std::string_view expected)
    {
        if (!bytes_.starts_with(expected))
        {
            return false;
        }
        bytes_.remove_prefix(expected.size());
        return true;
    }

    bool done() const
    {
        return bytes_.empty();
    }

  private:
    std::string_view bytes_;
};

}

std::string encode(const Replay &r)
{
    std::string out{magic};
    put(out, format_version);
    put_string(out, r.pack_id);
    put(out, static_cast<std::uint64_t>(r.stage));
    put(out, r.stage_hash);
    put(out, r.seed);
    put(out, static_cast<std::uint64_t>(r.hit_seg));
    put(out, static_cast<std::uint64_t>(r.time_ms));
    put_string(out, r.name);
    for (const int v : {r.year, r.month, r.day, r.hour, r.minute})
    {
        put(out, static_cast<std::uint64_t>(v));
    }
    put(out, r.ticks.size());

    int x = 0;
    for (const auto &t : r.ticks)
    {
        const int dx = t.cursor_x - x;
        x = t.cursor_x;
        const std::uint8_t flags = (t.left_down ? 1 : 0) | (dx != 0 ? 2 : 0) | (t.launches ? 4 : 0);
        out.push_back(static_cast<char>(flags));
        if (dx != 0)
        {
            put(out, zigzag(dx));
        }
        if (t.launches)
        {
            put(out, t.launches);
        }
    }
    return out;
}

std::optional<Replay> decode(std::string_view bytes)
{
    Reader in{bytes};
    if (!in.take(magic) || in.get() != format_version)
    {
        return std::nullopt;
    }
    Replay r;
    auto pack_id = in.get_string(256);
    const auto stage = in.get();
    const auto stage_hash = in.get();
    const auto seed = in.get();
    const auto hit_seg = in.get();
    const auto time_ms = in.get();
    auto name = in.get_string(save::max_name_length);
    if (!pack_id || !stage || *stage >= 50 || !stage_hash || !seed || *seed > 0xffffffffu || !hit_seg ||
        *hit_seg > 7 || !time_ms || *time_ms > 0x7fffffffu || !name)
    {
        return std::nullopt;
    }
    r.pack_id = std::move(*pack_id);
    r.stage = static_cast<int>(*stage);
    r.stage_hash = *stage_hash;
    r.seed = static_cast<std::uint32_t>(*seed);
    r.hit_seg = static_cast<int>(*hit_seg);
    r.time_ms = static_cast<int>(*time_ms);
    r.name = std::move(*name);
    for (int *field : {&r.year, &r.month, &r.day, &r.hour, &r.minute})
    {
        const auto v = in.get();
        if (!v || *v > 9999)
        {
            return std::nullopt;
        }
        *field = static_cast<int>(*v);
    }

    const auto count = in.get();
    if (!count || *count > max_ticks)
    {
        return std::nullopt;
    }
    r.ticks.reserve(*count);
    int x = 0;
    for (std::uint64_t i = 0; i < *count; ++i)
    {
        const auto flags = in.get();
        if (!flags || *flags > 7)
        {
            return std::nullopt;
        }
        Tick t;
        t.left_down = *flags & 1;
        if (*flags & 2)
        {
            const auto dx = in.get();
            if (!dx)
            {
                return std::nullopt;
            }
            x += static_cast<int>(unzigzag(*dx));
            if (x < 0 || x > 639)
            {
                return std::nullopt;
            }
        }
        t.cursor_x = static_cast<std::int16_t>(x);
        if (*flags & 4)
        {
            const auto n = in.get();
            if (!n || *n == 0 || *n > 255)
            {
                return std::nullopt;
            }
            t.launches = static_cast<std::uint8_t>(*n);
        }
        r.ticks.push_back(t);
    }
    if (!in.done())
    {
        return std::nullopt;
    }
    return r;
}

std::filesystem::path best_path(const std::filesystem::path &data_dir, std::string_view pack_id, int stage)
{
    return data_dir / "replays" / std::string{pack_id} / std::format("stage{:02}.rep", stage + 1);
}

std::optional<Replay> read(const std::filesystem::path &path)
{
    std::ifstream file{path, std::ios::binary};
    if (!file)
    {
        return std::nullopt;
    }
    const std::string bytes{std::istreambuf_iterator<char>{file}, {}};
    return decode(bytes);
}

bool write(const std::filesystem::path &path, const Replay &replay)
{
    return save::write_file(path, encode(replay));
}

}
