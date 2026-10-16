#pragma once

#include <filesystem>

// Rebuild-only settings, kept in block.ini so block130.sys stays compatible with the original game.
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

inline constexpr int fps_limits[] = {0, 60, 120, 144, 165, 240}; // 0 = no limit

struct Settings
{
    DisplayMode display = DisplayMode::windowed;
    Scaling scaling = Scaling::pixel_perfect;
    bool side_frame = true;    // decorate the area around the 4:3 picture
    bool vsync = true;
    int fps_limit = 0;         // one of fps_limits
    bool smooth_motion = true; // interpolate between 60 Hz logic ticks
    int window_width = 1280;
    int window_height = 960;
    double music_volume = 128.0; // 0..128, same curve as the original master volume
    double sound_volume = 128.0;
    double mouse_speed = 64.0;   // 0..128 slider; 64 = 1x, each 32 doubles or halves
};

Settings load(const std::filesystem::path &dir);
bool write(const std::filesystem::path &dir, const Settings &settings);

// Mouse speed multiplier for a slider value, 0.25x .. 4x.
double mouse_multiplier(double slider);

}
