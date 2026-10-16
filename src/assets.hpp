#pragma once

#include <cstdint>
#include <span>
#include <string_view>

// Game data compiled into the executable from assets/ (see cmake/embed.cmake).
namespace assets
{

// 640x272 8bpp sprite sheet; magenta (255,0,255) is transparent.
std::span<const std::uint8_t> sprites_bmp();

// Stage layouts as text; format described at the top of assets/stages.txt.
std::span<const std::uint8_t> stages_txt();

// 32x32 window icon (Windows uses the icon resource in the executable instead).
std::span<const std::uint8_t> icon_bmp();

// Built-in Ogg Vorbis sound by file stem (e.g. "bgm"); empty if there is none.
std::span<const std::uint8_t> sound(std::string_view name);

inline std::string_view as_text(std::span<const std::uint8_t> bytes)
{
    return {reinterpret_cast<const char *>(bytes.data()), bytes.size()};
}

}
