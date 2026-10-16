#pragma once

#include <SDL3/SDL.h>

#include <cstdint>
#include <span>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "settings.hpp"

// Source rectangle in the sprite sheet (x, y, width, height).
struct Rect
{
    int x;
    int y;
    int w;
    int h;
};

namespace sprite
{
inline constexpr Rect wall{0, 144, 16, 16};
inline constexpr Rect ball_small{32, 144, 8, 8};
inline constexpr Rect ball_normal{16, 144, 16, 16};
inline constexpr Rect ball_big{48, 144, 32, 32};
inline constexpr Rect cursor{112, 144, 16, 16};
inline constexpr Rect name_entry_tile{128, 144, 16, 16};
inline constexpr Rect cyan_ball{144, 144, 16, 16};
inline constexpr Rect mask_bar{160, 144, 16, 18};
inline constexpr Rect preview_tile{176, 144, 16, 16};
inline constexpr Rect volume_track{112, 160, 128, 16};
inline constexpr Rect paddle_left{0, 160, 16, 16};
inline constexpr Rect paddle_middle{16, 160, 16, 16};
inline constexpr Rect paddle_right{32, 160, 16, 16};

// 8x8 dots used by the voxel text
inline constexpr Rect dot_pink{32, 144, 8, 8};
inline constexpr Rect dot_blue{40, 144, 8, 8};
inline constexpr Rect dot_orange{32, 152, 8, 8};
inline constexpr Rect dot_black{40, 152, 8, 8};

constexpr Rect block(int type)
{
    return {type * 32, 176, 32, 16};
}

constexpr Rect fragment(int type, int index)
{
    return {type * 32 + (index % 8) * 4, 176 + (index / 8) * 4, 4, 4};
}

constexpr Rect item(int type)
{
    return {type * 32, 192, 32, 16};
}

// 16x8 stage-preview block, indexed by preview colour (see stage_preview_icon)
constexpr Rect mini_block(int icon)
{
    return {240 + icon * 16, 168, 16, 8};
}
}

// Identifies a moving sprite across logic ticks so it can be drawn between its two positions.
// The top byte is the kind of object; 0 means "not tracked".
namespace track
{
inline constexpr std::uint32_t ball = 1u << 24;
inline constexpr std::uint32_t fragment = 2u << 24;
inline constexpr std::uint32_t item = 3u << 24;
inline constexpr std::uint32_t voxel = 4u << 24;
inline constexpr std::uint32_t paddle = 5u << 24; // drawn at the live mouse position while playing
inline constexpr std::uint32_t cursor = 6u << 24; // always drawn at the live mouse position
inline constexpr std::uint32_t text = 7u << 24;
inline constexpr std::uint32_t kind_mask = 0xffu << 24;

constexpr std::uint32_t id(std::uint32_t kind, std::uint32_t n)
{
    return kind | (n & 0xffffffu);
}
}

// Offsets, in game pixels, from where the last logic tick drew the paddle and cursor to where the mouse
// is now.
struct LiveOffsets
{
    bool paddle = false;
    int paddle_dx = 0;
    int cursor_dx = 0;
    int cursor_dy = 0;
};

// Records the sprite blits of each 60 Hz logic tick. Every display refresh draws the latest tick, with tracked
// sprites placed between their previous and current positions.
class Gfx
{
  public:
    static constexpr int width = 640;
    static constexpr int height = 480;

    bool init(SDL_Renderer *renderer, std::span<const std::uint8_t> sprite_bmp);
    void shutdown();

    void begin_frame();

    // Draws the game into its 640x480 picture. alpha is how far display time is between the previous and the
    // latest tick (0..1); pass 1 for no interpolation.
    void render(double alpha, const LiveOffsets &live);

    // Puts the picture in the window; returns where it went, in output pixels.
    SDL_FRect compose(settings::Scaling scaling, bool side_frame);

    // Blits a sprite with its top-left at (x, y). Like the original, a sprite that is even partly
    // off the 640x480 screen is skipped entirely.
    void blit(int x, int y, Rect src, std::uint32_t id = 0);

    // Proportional bitmap font; colour 0 white, 1 blue, 2 red. A non-zero id_base tracks each character.
    void text(int x, int y, std::string_view s, int colour, std::uint32_t id_base = 0);
    static int text_width(std::string_view s);
    static int glyph_width(char c);

    // 15x32 digits, orange (colour 0) or blue (1); y is in 16 px rows.
    void digits(int x, int row, std::string_view s, int colour, std::uint32_t id_base = 0);

    void cursor(int x, int y);

    // Font pixel classification for the voxel text: 0 glyph face, 1 glyph outline, -1 neither.
    int font_pixel_kind(int x, int y) const;

    SDL_Surface *sprite_surface() const
    {
        return surface_;
    }

  private:
    struct DrawOp
    {
        Rect src;
        int x;
        int y;
        std::uint32_t id;
    };

    struct Position
    {
        int x;
        int y;
    };

    SDL_Renderer *renderer_{};
    SDL_Texture *texture_{};
    SDL_Texture *target_{};
    SDL_Surface *surface_{};
    std::vector<DrawOp> ops_;
    std::unordered_map<std::uint32_t, Position> previous_;
};
