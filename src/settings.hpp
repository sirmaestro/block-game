#pragma once

#include <filesystem>
#include <string>

// All settings, in block.ini. Records and progress are in block.sav (save.hpp).
namespace settings
{

enum class DisplayMode
{
    windowed,
    borderless,
    fullscreen, // exclusive, at the desktop resolution and refresh rate
};

enum class Scaling
{
    pixel_perfect, // largest whole-number multiple of 640x480
    fit,           // largest size that keeps 4:3
    stretch,       // fill the window
};

enum class Filter
{
    nearest,   // hard pixels; uneven pixel sizes at non-integer scales
    sharp,     // hard pixels with smoothed edges, even at non-integer scales
    scanlines, // hard pixels with dark lines between rows, like a CRT
};

inline constexpr int fps_limits[] = {0, 60, 120, 144, 165, 240}; // 0 = no limit

struct Settings
{
    DisplayMode display = DisplayMode::windowed;
    Scaling scaling = Scaling::pixel_perfect;
    Filter filter = Filter::sharp;
    bool side_frame = true;    // decorate the area around the 4:3 picture
    bool vsync = true;
    int fps_limit = 0;         // one of fps_limits
    bool smooth_motion = true; // interpolate between 60 Hz logic ticks
    int window_width = 1280;
    int window_height = 960;
    bool has_window_position = false;
    int window_x = 0;
    int window_y = 0;
    std::string monitor; // name of the display the window was last on

    double master_volume = 64.0; // 0..128, the original's volume slider and curve
    double music_volume = 128.0;
    double sound_volume = 128.0;

    double mouse_speed = 64.0; // 0..128 slider; 64 = 1x, each 32 doubles or halves
    double pad_speed = 64.0;   // keyboard and gamepad cursor speed, same scale

    bool show_broken_blocks = true; // the original's DISPLAY BROKEN BLOCKS option
    std::string stage_pack;         // id of the selected stage pack; empty for the built-in stages
};

// Reads block.ini. Without one, the volume and DISPLAY BROKEN BLOCKS options come from the original game's
// block130.sys if there is one.
Settings load(const std::filesystem::path &dir);
bool write(const std::filesystem::path &dir, const Settings &settings);

// Speed multiplier for a mouse or pad speed slider value, 0.25x .. 4x.
double mouse_multiplier(double slider);

}
