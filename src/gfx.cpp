#include "gfx.hpp"

#include <algorithm>
#include <cmath>
#include <cstdlib>

namespace
{

// Font rows: '!'..'?' at +0, '@'..'_' at +16, '`'..'~' at +32 within each 48 px colour band.
Rect glyph_cell(char c, int colour)
{
    const auto uc = static_cast<unsigned char>(c);
    const int base = uc < 0x40 ? 0x21 : uc < 0x60 ? 0x40 : 0x60;
    const int row = uc < 0x40 ? 0 : uc < 0x60 ? 16 : 32;
    return {(uc - base) * 18, colour * 48 + row, Gfx::glyph_width(c) + 2, 16};
}

bool on_screen(int x, int y, Rect src)
{
    return x >= 0 && x + src.w <= Gfx::width && y >= 0 && y + src.h <= Gfx::height;
}

// A tracked sprite that moved further than this in one tick was replaced or teleported: don't slide it.
constexpr int max_interpolated_step = 96;

}

bool Gfx::init(SDL_Renderer *renderer, std::span<const std::uint8_t> sprite_bmp)
{
    renderer_ = renderer;
    surface_ = SDL_LoadBMP_IO(SDL_IOFromConstMem(sprite_bmp.data(), sprite_bmp.size()), true);
    if (!surface_)
    {
        return false;
    }
    SDL_SetSurfaceColorKey(surface_, true, SDL_MapSurfaceRGB(surface_, 255, 0, 255));
    texture_ = SDL_CreateTextureFromSurface(renderer_, surface_);
    target_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, width, height);
    if (!texture_ || !target_)
    {
        return false;
    }
    SDL_SetTextureScaleMode(texture_, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureScaleMode(target_, SDL_SCALEMODE_NEAREST);
    ops_.reserve(16384);
    previous_.reserve(16384);
    return true;
}

void Gfx::shutdown()
{
    SDL_DestroyTexture(target_);
    SDL_DestroyTexture(texture_);
    SDL_DestroySurface(surface_);
    target_ = nullptr;
    texture_ = nullptr;
    surface_ = nullptr;
}

void Gfx::begin_frame()
{
    previous_.clear();
    for (const auto &op : ops_)
    {
        if (op.id != 0)
        {
            previous_[op.id] = {op.x, op.y};
        }
    }
    ops_.clear();
}

void Gfx::render(double alpha, const LiveOffsets &live)
{
    SDL_SetRenderTarget(renderer_, target_);
    // the original clears to palette index 255, (4,4,4)
    SDL_SetRenderDrawColor(renderer_, 4, 4, 4, 255);
    SDL_RenderClear(renderer_);

    for (const auto &op : ops_)
    {
        int x = op.x, y = op.y;
        const auto kind = op.id & track::kind_mask;

        if (kind == track::cursor)
        {
            x += live.cursor_dx;
            y += live.cursor_dy;
            if (!on_screen(x, y, op.src))
            {
                continue;
            }
        }
        else if (op.id != 0)
        {
            if (const auto it = previous_.find(op.id); it != previous_.end())
            {
                const auto [px, py] = it->second;
                if (std::abs(x - px) <= max_interpolated_step && std::abs(y - py) <= max_interpolated_step)
                {
                    x = static_cast<int>(std::lround(px + (x - px) * alpha));
                    y = static_cast<int>(std::lround(py + (y - py) * alpha));
                }
            }
            if (kind == track::paddle && live.paddle)
            {
                x = op.x + live.paddle_dx;
            }
        }

        const SDL_FRect src{float(op.src.x), float(op.src.y), float(op.src.w), float(op.src.h)};
        const SDL_FRect dst{float(x), float(y), float(op.src.w), float(op.src.h)};
        SDL_RenderTexture(renderer_, texture_, &src, &dst);
    }
    SDL_SetRenderTarget(renderer_, nullptr);
}

SDL_FRect Gfx::compose(settings::Scaling scaling, bool side_frame)
{
    int out_w = 0, out_h = 0;
    SDL_GetCurrentRenderOutputSize(renderer_, &out_w, &out_h);

    SDL_FRect dst{0, 0, float(out_w), float(out_h)};
    if (scaling != settings::Scaling::stretch)
    {
        double scale = std::min(double(out_w) / width, double(out_h) / height);
        if (scaling == settings::Scaling::pixel_perfect && scale >= 1.0)
        {
            scale = std::floor(scale);
        }
        dst.w = float(width * scale);
        dst.h = float(height * scale);
        dst.x = std::floor((out_w - dst.w) / 2);
        dst.y = std::floor((out_h - dst.h) / 2);
    }

    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);

    if (side_frame && (dst.w < out_w || dst.h < out_h))
    {
        // continue the playfield's wall tiles, dimmed, aligned to the picture's own 16 px grid
        const float tile_w = dst.w / width * 16, tile_h = dst.h / height * 16;
        const float start_x = dst.x - std::ceil(dst.x / tile_w) * tile_w;
        const float start_y = dst.y - std::ceil(dst.y / tile_h) * tile_h;
        const SDL_FRect src{float(sprite::wall.x), float(sprite::wall.y), 16, 16};
        SDL_SetTextureColorMod(texture_, 72, 72, 88);
        for (float y = start_y; y < out_h; y += tile_h)
        {
            for (float x = start_x; x < out_w; x += tile_w)
            {
                const bool inside = x >= dst.x && x + tile_w <= dst.x + dst.w + 0.5f && y >= dst.y &&
                                    y + tile_h <= dst.y + dst.h + 0.5f;
                if (!inside)
                {
                    const SDL_FRect tile{x, y, tile_w, tile_h};
                    SDL_RenderTexture(renderer_, texture_, &src, &tile);
                }
            }
        }
        SDL_SetTextureColorMod(texture_, 255, 255, 255);
    }

    SDL_RenderTexture(renderer_, target_, nullptr, &dst);
    return dst;
}

void Gfx::blit(int x, int y, Rect src, std::uint32_t id)
{
    if (src.w <= 0 || src.h <= 0 || !on_screen(x, y, src))
    {
        return;
    }
    ops_.push_back({src, x, y, id});
}

int Gfx::glyph_width(char c)
{
    switch (c)
    {
        case '!': case '\'': case ',': case '.': case ':': case ';': case 'I': case 'i': case 'l': case '|':
            return 5;
        case ' ': case '(': case ')': case '[': case ']': case '`': case '{': case '}':
            return 7;
        case '<': case '>': case 'j':
            return 8;
        case '/':
            return 9;
        case '"': case '+': case '-': case '=': case '_':
            return 10;
        case '^':
            return 12;
        case '#': case '&': case 'G': case '~':
            return 14;
        case '@':
            return 15;
        case 'M': case 'W': case 'm': case 'w':
            return 16;
        default:
            return 13;
    }
}

int Gfx::text_width(std::string_view s)
{
    int total = 1;
    for (const char c : s)
    {
        total += glyph_width(c) - 1;
    }
    return total;
}

void Gfx::text(int x, int y, std::string_view s, int colour, std::uint32_t id_base)
{
    std::uint32_t n = 0;
    for (const char c : s)
    {
        if (c >= 0x21 && c <= 0x7e)
        {
            blit(x, y, glyph_cell(c, colour), id_base ? id_base + n : 0);
        }
        x += glyph_width(c) - 1;
        ++n;
    }
}

void Gfx::digits(int x, int row, std::string_view s, int colour, std::uint32_t id_base)
{
    std::uint32_t n = 0;
    for (const char c : s)
    {
        if (c >= '0' && c <= '9')
        {
            blit(x, row * 16, {(c - '0') * 18, 208 + 32 * colour, 15, 32}, id_base ? id_base + n : 0);
        }
        x += 12;
        ++n;
    }
}

void Gfx::cursor(int x, int y)
{
    // recorded without the off-screen check so the live position can still be drawn
    ops_.push_back({sprite::cursor, x, y, track::id(track::cursor, 0)});
}

int Gfx::font_pixel_kind(int x, int y) const
{
    if (!surface_ || x < 0 || y < 0 || x >= surface_->w || y >= surface_->h)
    {
        return -1;
    }
    Uint8 r{}, g{}, b{};
    if (!SDL_ReadSurfacePixel(surface_, x, y, &r, &g, &b, nullptr))
    {
        return -1;
    }
    if (r == 0xfc && g == 0xfc && b == 0xfc)
    {
        return 0;
    }
    if (r == 0x04 && g == 0x04 && b == 0x04)
    {
        return 1;
    }
    return -1;
}
