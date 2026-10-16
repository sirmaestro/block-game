#include "settings.hpp"

#include "save.hpp"

#include <algorithm>
#include <charconv>
#include <cmath>
#include <format>
#include <fstream>
#include <iterator>
#include <optional>
#include <string>
#include <string_view>
#include <system_error>

namespace settings
{

namespace
{

constexpr const char *file_name = "block.ini";

std::string_view trim(std::string_view s)
{
    while (!s.empty() && (s.front() == ' ' || s.front() == '\t'))
    {
        s.remove_prefix(1);
    }
    while (!s.empty() && (s.back() == ' ' || s.back() == '\t' || s.back() == '\r'))
    {
        s.remove_suffix(1);
    }
    return s;
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

constexpr std::string_view display_names[] = {"windowed", "borderless", "fullscreen"};
constexpr std::string_view scaling_names[] = {"pixel_perfect", "fit", "stretch"};
constexpr std::string_view filter_names[] = {"nearest", "sharp", "scanlines"};

template <class Enum, std::size_t N>
std::optional<Enum> from_name(std::string_view value, const std::string_view (&names)[N])
{
    for (std::size_t i = 0; i < N; ++i)
    {
        if (names[i] == value)
        {
            return static_cast<Enum>(i);
        }
    }
    return std::nullopt;
}

}

double mouse_multiplier(double slider)
{
    return std::exp2((slider - 64.0) / 32.0);
}

Settings load(const std::filesystem::path &dir)
{
    Settings s;
    std::ifstream file{dir / file_name};
    if (!file)
    {
        if (const auto legacy = save::load_legacy_options(dir))
        {
            s.master_volume = legacy->volume;
            s.show_broken_blocks = legacy->show_broken_blocks;
        }
        return s;
    }

    std::string line;
    while (std::getline(file, line))
    {
        const auto text = trim(line);
        const auto eq = text.find('=');
        if (text.empty() || text.front() == '#' || text.front() == '[' || eq == std::string_view::npos)
        {
            continue;
        }
        const auto key = trim(text.substr(0, eq));
        const auto value = trim(text.substr(eq + 1));
        const auto number = to_int(value);
        const auto slider = [&](double &target) {
            if (number)
            {
                target = std::clamp(*number, 0, 128);
            }
        };

        if (key == "display")
        {
            s.display = from_name<DisplayMode>(value, display_names).value_or(s.display);
        }
        else if (key == "scaling")
        {
            s.scaling = from_name<Scaling>(value, scaling_names).value_or(s.scaling);
        }
        else if (key == "filter")
        {
            s.filter = from_name<Filter>(value, filter_names).value_or(s.filter);
        }
        else if (key == "side_frame" && number)
        {
            s.side_frame = *number != 0;
        }
        else if (key == "vsync" && number)
        {
            s.vsync = *number != 0;
        }
        else if (key == "fps_limit" && number && std::ranges::find(fps_limits, *number) != std::end(fps_limits))
        {
            s.fps_limit = *number;
        }
        else if (key == "smooth_motion" && number)
        {
            s.smooth_motion = *number != 0;
        }
        else if (key == "window_width" && number)
        {
            s.window_width = std::clamp(*number, 640, 16384);
        }
        else if (key == "window_height" && number)
        {
            s.window_height = std::clamp(*number, 480, 16384);
        }
        else if (key == "window_x" && number)
        {
            s.window_x = *number;
            s.has_window_position = true;
        }
        else if (key == "window_y" && number)
        {
            s.window_y = *number;
        }
        else if (key == "monitor")
        {
            s.monitor = value;
        }
        else if (key == "master_volume")
        {
            slider(s.master_volume);
        }
        else if (key == "music_volume")
        {
            slider(s.music_volume);
        }
        else if (key == "sound_volume")
        {
            slider(s.sound_volume);
        }
        else if (key == "mouse_speed")
        {
            slider(s.mouse_speed);
        }
        else if (key == "pad_speed")
        {
            slider(s.pad_speed);
        }
        else if (key == "show_broken_blocks" && number)
        {
            s.show_broken_blocks = *number != 0;
        }
        else if (key == "stage_pack")
        {
            s.stage_pack = value;
        }
    }
    return s;
}

bool write(const std::filesystem::path &dir, const Settings &s)
{
    std::string text = std::format("# BLOCK settings. Records are in block.sav.\n"
                                   "[display]\n"
                                   "display={}\n"
                                   "scaling={}\n"
                                   "filter={}\n"
                                   "side_frame={}\n"
                                   "vsync={}\n"
                                   "fps_limit={}\n"
                                   "smooth_motion={}\n"
                                   "window_width={}\n"
                                   "window_height={}\n",
                                   display_names[static_cast<int>(s.display)], scaling_names[static_cast<int>(s.scaling)],
                                   filter_names[static_cast<int>(s.filter)], s.side_frame ? 1 : 0, s.vsync ? 1 : 0,
                                   s.fps_limit, s.smooth_motion ? 1 : 0, s.window_width, s.window_height);
    if (s.has_window_position)
    {
        text += std::format("window_x={}\nwindow_y={}\n", s.window_x, s.window_y);
    }
    if (!s.monitor.empty())
    {
        text += std::format("monitor={}\n", s.monitor);
    }
    text += std::format("\n"
                        "[audio]\n"
                        "master_volume={}\n"
                        "music_volume={}\n"
                        "sound_volume={}\n"
                        "\n"
                        "[input]\n"
                        "mouse_speed={}\n"
                        "pad_speed={}\n"
                        "\n"
                        "[game]\n"
                        "show_broken_blocks={}\n"
                        "stage_pack={}\n",
                        static_cast<int>(s.master_volume), static_cast<int>(s.music_volume),
                        static_cast<int>(s.sound_volume), static_cast<int>(s.mouse_speed),
                        static_cast<int>(s.pad_speed), s.show_broken_blocks ? 1 : 0, s.stage_pack);
    return save::write_file(dir / file_name, text);
}

}
