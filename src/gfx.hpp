#pragma once

#include <SDL3/SDL.h>

#include <cstdint>
#include <span>
#include <string_view>
#include <vector>

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

// Records sprite blits for one logic tick; the recorded frame is replayed on every display refresh.
class Gfx
{
  public:
    bool init(SDL_Renderer *renderer, std::span<const std::uint8_t> sprite_bmp);
    void shutdown();

    void begin_frame();
    void present() const;

    // Blits a sprite with its top-left at (x, y). Like the original, a sprite that is even partly
    // off the 640x480 screen is skipped entirely.
    void blit(int x, int y, Rect src);

    // Proportional bitmap font; colour 0 white, 1 blue, 2 red.
    void text(int x, int y, std::string_view s, int colour);
    static int text_width(std::string_view s);
    static int glyph_width(char c);

    // 15x32 digits, orange (colour 0) or blue (1); y is in 16 px rows.
    void digits(int x, int row, std::string_view s, int colour);

    void cursor(int x, int y)
    {
        blit(x, y, sprite::cursor);
    }

    // Font pixel classification for the voxel text: 0 glyph face, 1 glyph outline, -1 neither.
    int font_pixel_kind(int x, int y) const;

  private:
    struct DrawOp
    {
        Rect src;
        int x;
        int y;
    };

    SDL_Renderer *renderer_{};
    SDL_Texture *texture_{};
    SDL_Surface *surface_{};
    std::vector<DrawOp> ops_;
};
