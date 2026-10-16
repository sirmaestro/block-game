// Rendering and full-screen states. See re/notes/rendering.md, menus.md and ranking_save_sound.md.
#include "game.hpp"

#include <cmath>
#include <format>
#include <optional>

namespace
{

constexpr double fps = Game::ticks_per_second;
constexpr double deg_to_rad = 0.017453292519944444;
constexpr double tilt_20 = 0.3490658503988889;
constexpr double tilt_30 = 0.5235987755983333;
constexpr double tilt_40 = 0.6981317007977778;
constexpr double spring_accel = 340.00000000000006;

std::string format_time(int ms)
{
    return std::format("{:02}m{:02}s{:02}", ms / 60000, (ms % 60000) / 1000, (ms % 1000) / 10);
}

// trunc(n * 1000 / d) for the voxel projections; nullopt where the original's result would be off-screen garbage
std::optional<int> project(double n, double d)
{
    if (d <= 0.0)
    {
        return std::nullopt;
    }
    const double v = n * 1000.0 / d;
    if (!(std::fabs(v) < 1e6))
    {
        return std::nullopt;
    }
    return static_cast<int>(v);
}

int centred(int width, std::string_view s)
{
    return (width - Gfx::text_width(s)) / 2;
}

// mini block icon in the stage previews, by block type
int preview_icon(int type)
{
    switch (type)
    {
        case 0: return 0;
        case 1: return 1;
        case 2: return 2;
        case 5: return 3;
        case 6: return 4;
        case 7: return 5;
        case 9: return 6;
        case 10: return 7;
        case 12: return 8;
        case 13: return 9;
        case 14: return 10;
        case 15: return 11;
        case 16: return 12;
        default: return -1;
    }
}

void tile_screen(Gfx &gfx, Rect tile)
{
    for (int y = 0; y < Game::screen_height; y += 16)
    {
        for (int x = 0; x < Game::screen_width; x += 16)
        {
            gfx.blit(x, y, tile);
        }
    }
}

}

void Game::draw_stage_preview(int stage, int x, int y)
{
    const auto &layout = stage_data_[stage];
    for (int row = 0; row < stages::rows; ++row)
    {
        for (int col = 0; col < stages::columns; ++col)
        {
            const auto cell = layout[col + row * stages::columns];
            if (cell == stages::empty)
            {
                continue;
            }
            if (const int icon = preview_icon(cell); icon >= 0)
            {
                gfx_.blit(x + 16 * col, y + 8 * row, sprite::mini_block(icon));
            }
        }
    }
}

// ---- playfield and HUD (FUN_00406c00) -------------------------------------------------------------------

void Game::draw_time_digits(int ms, int row, int m_y)
{
    gfx_.digits(512, row, std::format("{:02}", ms / 60000), 0);
    gfx_.text(538, m_y, "M", 1);
    gfx_.digits(556, row, std::format("{:02}", (ms % 60000) / 1000), 0);
    gfx_.text(582, m_y, "S", 1);
    gfx_.digits(597, row, std::format("{:02}", (ms % 1000) / 10), 0);
}

void Game::render_playfield()
{
    // walls
    for (int x = 0; x < 640; x += 16)
    {
        gfx_.blit(x, 0, sprite::wall);
    }
    for (int x = 496; x < 640; x += 16)
    {
        gfx_.blit(x, 464, sprite::wall);
    }
    for (int y = 16; y < 480; y += 16)
    {
        gfx_.blit(0, y, sprite::wall);
    }
    for (int y = 16; y < 464; y += 16)
    {
        gfx_.blit(496, y, sprite::wall);
        gfx_.blit(624, y, sprite::wall);
    }

    // HUD
    gfx_.text(512, 16, "STAGE", 2);
    gfx_.digits(597, 1, std::format("{:02}", stage_ + 1), 1);
    gfx_.text(512, 64, "TIME", 2);
    draw_time_digits(stage_ms_[stage_], 5, 96);
    const auto &best = data_.stage_ranking[stage_][0];
    gfx_.text(512, 112, best.name, 0);
    gfx_.text(522, 128, format_time(best.time_ms), 0);
    if (mode_ == 1)
    {
        gfx_.text(512, 160, "TOTAL TIME", 2);
        draw_time_digits(total_ms_, 11, 192);
        const auto &total_best = data_.total_ranking[0];
        gfx_.text(512, 208, total_best.name, 0);
        gfx_.text(522, 224, format_time(total_best.time_ms), 0);
    }
    gfx_.text(512, 256, "BALLS", 2);
    for (int i = 1; i <= 10 && i <= stock_; ++i)
    {
        gfx_.blit(529 + 16 * ((i - 1) % 5), 273 + 16 * ((i - 1) / 5), sprite::ball_normal);
    }
    const auto countdown = [&](int ms, int y) {
        const auto s = std::format("{}s", (ms + 999) / 1000);
        gfx_.text(622 - Gfx::text_width(s), y, s, 0);
    };
    if (mugen_ms_ > 0)
    {
        countdown(mugen_ms_, 288);
    }
    gfx_.text(512, 320, "ITEMS", 2);
    if (big_ms_ > 0)
    {
        countdown(big_ms_, 336);
    }
    else if (small_ms_ > 0)
    {
        countdown(small_ms_, 336);
    }
    if (reverse_ms_ > 0)
    {
        countdown(reverse_ms_, 368);
    }
    const auto fps_text = std::format("FPS : {}", display_fps_);
    gfx_.text((1136 - Gfx::text_width(fps_text)) / 2, 432, fps_text, 0);
    gfx_.text((1136 - Gfx::text_width(version_short)) / 2, 448, version_short, 0);

    // paddle
    drawn_paddle_x_ = paddle_x_;
    const int py = static_cast<int>(paddle_y_) - 8;
    const int w = paddle_units_;
    gfx_.blit(paddle_x_ - 8 * w, py, sprite::paddle_left, track::id(track::paddle, 0));
    for (int k = 0; k <= w - 3; ++k)
    {
        gfx_.blit(paddle_x_ + (2 + 2 * k - w) * 8, py, sprite::paddle_middle, track::id(track::paddle, 2 + k));
    }
    gfx_.blit(paddle_x_ + 8 * w - 16, py, sprite::paddle_right, track::id(track::paddle, 1));

    // blocks; red and cyan blocks show a ball through their see-through middle
    for (const auto &b : blocks_)
    {
        const int fx = static_cast<int>(b.fx[0]), fy = static_cast<int>(b.fy[0]);
        if (b.type == 9)
        {
            gfx_.blit(fx + 6, fy - 2, sprite::cyan_ball);
        }
        if (b.state == block_alive)
        {
            if (b.type == 6)
            {
                gfx_.blit(fx + 6, fy - 2, sprite::ball_normal);
            }
            gfx_.blit(fx - 2, fy - 2, sprite::block(b.type));
        }
    }

    for (const auto &item : items_)
    {
        if (item.state != item_gone)
        {
            gfx_.blit(static_cast<int>(item.x) - 16, static_cast<int>(item.y) - 8, sprite::item(item.type),
                      track::id(track::item, static_cast<std::uint32_t>(&item - items_.data())));
        }
    }

    if (data_.show_broken_blocks)
    {
        for (const int k : dying_)
        {
            const auto &b = blocks_[k];
            if (b.state != block_breaking)
            {
                continue;
            }
            for (int f = 0; f < 32; ++f)
            {
                if (b.alive[f])
                {
                    gfx_.blit(static_cast<int>(b.fx[f]) - 2, static_cast<int>(b.fy[f]) - 2, sprite::fragment(b.type, f),
                              track::id(track::fragment, static_cast<std::uint32_t>(k * 32 + f)));
                }
            }
        }
    }

    for (const auto &ball : balls_)
    {
        const Rect src = ball.r == 4 ? sprite::ball_small : ball.r == 16 ? sprite::ball_big : sprite::ball_normal;
        gfx_.blit(static_cast<int>(ball.x) - ball.r, static_cast<int>(ball.y) - ball.r, src, track::id(track::ball, ball.id));
    }
}

// ---- boot (state 0x20) ----------------------------------------------------------------------------------

void Game::screen_boot(int dt_ms)
{
    if (phase_ < 2)
    {
        ++phase_; // the original ran its one-time initialisation here
    }
    else
    {
        phase_ms_ += dt_ms;
        if (phase_ms_ > 1000)
        {
            state_ = State::title;
            phase_ = 0;
            phase_ms_ = 0;
        }
    }
    gfx_.text(centred(640, "Now Loading..."), 224, "Now Loading...", 0);
}

// ---- title (FUN_00405a60) -------------------------------------------------------------------------------

void Game::screen_title()
{
    if (phase_ == 0)
    {
        play(Sfx::title);
        vox_.clear();
        vox_.build(gfx_, "BLOCK");
        ang_vel_ = 0.5;
        cam_z_ = 5000.0;
        vox_.rects = {sprite::dot_blue, sprite::dot_pink};
        vox_.rotate_x(tilt_20);
        phase_ = 1;
    }
    else
    {
        cam_z_ -= 500.0 / fps;
        if (cam_z_ < 1500.0)
        {
            cam_z_ = 1500.0;
        }
        vox_.rotate_y(ang_vel_ * 200.0 / fps * deg_to_rad);
        for (const int i : vox_.depth_order())
        {
            const auto &v = vox_.voxels[i];
            const auto sx = project(v.x, cam_z_ + v.z);
            const auto sy = project(v.y, cam_z_ + v.z);
            if (sx && sy)
            {
                gfx_.blit(316 + *sx, 146 - *sy, vox_.rects[v.kind], vox_.id(i));
            }
        }
    }

    const Point p = cursor();
    const bool active = windows_[win_options].state == closed && windows_[win_mode_select].state == closed;
    const auto item = [&](int row, std::string_view label) {
        const bool hover = active && row * 16 < p.y && p.y < (row + 1) * 16;
        gfx_.text(centred(640, label), row * 16, label, hover ? 1 : 0);
        return hover;
    };

    gfx_.text(centred(640, version_long), 192, version_long, 0);
    const bool start = item(18, "GAME START");
    const bool ranking = item(20, "RANKING");
    const bool options = item(22, "OPTIONS");
    gfx_.text(centred(640, "Copyright(c) 1999-2000 KENTA(22)"), 400, "Copyright(c) 1999-2000 KENTA(22)", 0);
    gfx_.text(centred(640, "http://www.interq.or.jp/tohoku/kenta/"), 416, "http://www.interq.or.jp/tohoku/kenta/", 0);

    if ((start || ranking || options) && take_click())
    {
        play(Sfx::open);
        if (start)
        {
            windows_[win_mode_select].state = opening;
        }
        else if (ranking)
        {
            stop(Sfx::title);
            state_ = State::ranking;
            phase_ = 0;
        }
        else
        {
            windows_[win_options].state = opening;
        }
    }
    gfx_.cursor(p.x, p.y);
}

// ---- stage intro, READY / GO!! (FUN_00404af0) -----------------------------------------------------------

void Game::screen_intro()
{
    bool init = false;
    if (phase_ == 0)
    {
        slide_x_ = 640.0;
        slide_v_ = 0.0;
        vox_.clear();
        vox_.build(gfx_, "READY");
        phase_ = 1;
        init = true;
    }
    else if (phase_ == 4)
    {
        vox_.clear();
        vox_.build(gfx_, "GO!!");
        phase_ = 5;
        init = true;
    }
    if (init)
    {
        angle_ = 270.0;
        vox_.rects = {sprite::dot_pink, sprite::dot_black};
        ang_vel_ = -3.0;
        cam_z_ = 1500.0;
        vox_.rotate_x(4.712388980385);
    }

    if ((angle_ > 10.0 && (phase_ == 1 || phase_ == 5)) || (angle_ > -90.0 && phase_ == 3))
    {
        const double step = ang_vel_ * 200.0 / fps;
        angle_ += step;
        vox_.rotate_x(step * deg_to_rad);
    }
    else if (phase_ == 7)
    {
        if (windows_[win_stage_select].state == closed)
        {
            cam_z_ -= 3000.0 / fps;
            if (cam_z_ < 0.0)
            {
                phase_ = 0;
                flag_ = 0;
                state_ = State::play;
                play(Sfx::bgm, true);
                set_cursor(paddle_x_, static_cast<int>(paddle_y_));
            }
        }
    }
    else if (phase_ != 2 && phase_ != 6)
    {
        ++phase_;
    }

    // drawn in storage order: the original sorts here but does not use the result
    for (int i = 0; i < int(vox_.voxels.size()); ++i)
    {
        const auto &v = vox_.voxels[i];
        const auto sx = project(v.x, cam_z_ + v.z);
        const auto sy = project(v.y, cam_z_ + v.z);
        if (sx && sy)
        {
            gfx_.blit(252 + *sx, 236 - *sy, vox_.rects[v.kind], vox_.id(i));
        }
    }

    // "STAGE nn" springs in from the right, then bounces out to the left on GO
    const auto spring_step = [&](double crossing_factor_down) {
        if (slide_x_ <= 200.0)
        {
            slide_v_ += spring_accel / fps;
        }
        else
        {
            slide_v_ -= spring_accel / fps;
        }
        const double next = slide_v_ * 100.0 / fps + slide_x_;
        const bool was_right = 200.0 <= slide_x_;
        if (was_right && next <= 200.0)
        {
            slide_v_ *= crossing_factor_down;
        }
        return next;
    };
    if (flag_ == 0)
    {
        const bool was_left = slide_x_ <= 200.0;
        slide_x_ = spring_step(0.3);
        if (was_left && 200.0 <= slide_x_)
        {
            slide_x_ = 200.0;
            flag_ = 1;
        }
    }
    else if (phase_ == 7)
    {
        if (flag_ == 1)
        {
            slide_v_ = 20.0;
            flag_ = 2;
        }
        else if (-150.0 < slide_x_)
        {
            slide_x_ = spring_step(3.3);
        }
    }

    const int sx = static_cast<int>(slide_x_);
    if (stage_ != stages::count - 1)
    {
        gfx_.text(sx, 160, "STAGE", 0, track::id(track::text, 0));
        gfx_.digits(sx + 85, 9, std::format("{:02}", stage_ + 1), 0, track::id(track::text, 0x10));
    }
    else
    {
        gfx_.text(sx - 4, 160, "FINAL STAGE", 2, track::id(track::text, 0));
    }
}

// ---- stage clear (FUN_004050a0) -------------------------------------------------------------------------

void Game::screen_clear()
{
    const int time = stage_ms_[stage_];
    auto &table = data_.stage_ranking[stage_];

    if (phase_ == 0)
    {
        stop(Sfx::mugen);
        stop(Sfx::bgm);
        play(Sfx::clear);
        stage_rank_this_run_[stage_] = save::insert(table, time, data_.player_name);
        save_data(); // the original saved only on exit
        vox_.clear();
        vox_.build(gfx_, "CLEAR!!");
        angle_ = 0.0;
        ang_vel_ = 0.5;
        cam_z_ = 0.0;
        vox_.rects = {sprite::dot_blue, sprite::dot_orange};
        vox_.rotate_x(tilt_20);
        phase_ = 1;
        return;
    }

    cam_z_ += 2000.0 / fps;
    if (cam_z_ > 1500.0)
    {
        cam_z_ = 1500.0;
    }
    const double step = ang_vel_ * 200.0 / fps;
    angle_ += step;
    if (angle_ > 30.0)
    {
        ang_vel_ = -0.5;
    }
    else if (angle_ < -30.0)
    {
        ang_vel_ = 0.5;
    }
    vox_.rotate_y(step * deg_to_rad);
    for (const int i : vox_.depth_order())
    {
        const auto &v = vox_.voxels[i];
        const auto sx = project(v.x, cam_z_ + v.z);
        const auto sy = project(v.y, cam_z_ + v.z);
        if (sx && sy)
        {
            gfx_.blit(252 + *sx, 196 - *sy, vox_.rects[v.kind], vox_.id(i));
        }
    }

    gfx_.text(centred(512, "Click L Button to Next Stage !!"), 256, "Click L Button to Next Stage !!", 0);
    if (stage_rank_this_run_[stage_] == 0)
    {
        if (flag_ == 0)
        {
            gfx_.text(centred(512, "NEW RECORD !!"), 320, "NEW RECORD !!", 0);
        }
        const auto diff = "- " + format_time(table[1].time_ms - time);
        gfx_.text(centred(512, diff), 336, diff, 1);
    }
    else
    {
        const auto diff = "+ " + format_time(time - table[0].time_ms);
        gfx_.text(centred(512, diff), 336, diff, 0);
    }
}

// ---- game over (FUN_00405770) ---------------------------------------------------------------------------

void Game::screen_game_over()
{
    if (phase_ == 0)
    {
        stop(Sfx::mugen);
        stop(Sfx::bgm);
        play(Sfx::gameover);
        vox_.clear();
        vox_.build(gfx_, "Boo!!");
        angle_ = 0.0;
        ang_vel_ = 0.5;
        cam_z_ = 0.0;
        vox_.rects = {sprite::dot_black, sprite::dot_pink};
        vox_.rotate_x(tilt_40);
        phase_ = 1;
        return;
    }

    if (phase_ == 1)
    {
        cam_z_ += 2000.0 / fps;
        if (cam_z_ > 1500.0)
        {
            cam_z_ = 1500.0;
            phase_ = 2;
        }
    }
    else if (phase_ == 3 && angle_ < 10.0)
    {
        // the word droops
        const double step = ang_vel_ * 200.0 / fps;
        angle_ += step;
        vox_.rotate_z(step * deg_to_rad, 150.0);
    }

    for (const int i : vox_.depth_order())
    {
        const auto &v = vox_.voxels[i];
        const auto sx = project(v.x, cam_z_ + v.z);
        const auto sy = project(v.y, cam_z_ + v.z);
        if (sx && sy)
        {
            gfx_.blit(252 + *sx, 156 - *sy, vox_.rects[v.kind], vox_.id(i));
        }
    }
    gfx_.text(130, 256, "Click L Button to Retry !!", 0);
}

// ---- ending (FUN_00405f70) ------------------------------------------------------------------------------

void Game::screen_ending()
{
    struct Word
    {
        const char *text;
        int colour_offset;
    };
    const Word words[14] = {
        {"BLOCK", 1},       {version_short, 1},   {"PROGRAM", 1}, {"KENTA(22)", 0}, {"STAGE EDIT", 1},
        {"KENTA(22),", 0},  {"KENICHI", 0},    {"SPECIAL THANKS", 1}, {"oknit,", 0}, {"MORIZUKI,", 0},
        {"NORIO,", 0},      {"MOJI,", 0},      {"AND...", 0},  {nullptr, 0},
    };
    if (phase_ == 0)
    {
        stop(Sfx::ending);
        play(Sfx::ending, true);
        total_rank_this_run_ = save::insert(data_.total_ranking, total_ms_, data_.player_name);
        save_data();
        end_top_line_ = 0;
        end_scroll_px_ = 0;
        end_word_ = 0;
        vox_.rects = {sprite::dot_orange, sprite::dot_blue, sprite::dot_pink};
        phase_ = 1;
    }
    const auto &word = words[end_word_];
    if (phase_ == 1)
    {
        vox_.clear();
        vox_.build(gfx_, word.text ? word.text : data_.player_name.c_str());
        vox_.rotate_x(tilt_20);
        for (auto &v : vox_.voxels)
        {
            // burst velocity, radial in the x/y plane
            const double d2 = v.x * v.x + v.y * v.y;
            const double d = std::sqrt(d2);
            v.vx = 50.0 * v.x / d / std::pow(d2, 0.1);
            v.vy = 50.0 * v.y / d / std::pow(d2, 0.1);
        }
        vox_.rotate_y(-1.0471975511966667);
        slide_x_ = 1000.0;
        slide_v_ = 0.0;
        phase_ = 2;
    }
    if (phase_ == 2)
    {
        const bool was_left = slide_x_ <= 320.0;
        slide_v_ += (was_left ? spring_accel : -spring_accel) / fps;
        const double next = slide_x_ + slide_v_ * 100.0 / fps;
        if (320.0 <= slide_x_ && next <= 320.0)
        {
            slide_v_ *= 0.2;
        }
        slide_x_ = next;
        if (was_left && 320.0 <= next)
        {
            slide_x_ = 320.0;
            phase_ = 3;
        }
    }
    else if (phase_ == 4)
    {
        for (auto &v : vox_.voxels)
        {
            v.vy -= 119.00000000000001 / fps;
            v.x += v.vx * 100.0 / fps;
            v.y += v.vy * 100.0 / fps;
        }
    }

    gfx_.text(centred(640, "CONGRATURATIONS !!"), 32, "CONGRATURATIONS !!", 2);

    for (int i = 0; i < 15; ++i)
    {
        int line = end_top_line_ + i;
        if (line > 67)
        {
            line -= 68;
        }
        std::string s;
        int colour = 0;
        if (line == 14)
        {
            s = "RESULT";
            colour = 2;
        }
        else if (line >= 16 && line <= 65)
        {
            s = std::format("STAGE {:02}  :  {}", line - 15, format_time(stage_ms_[line - 16]));
        }
        else if (line == 67)
        {
            s = "TOTAL TIME  :  " + format_time(total_ms_);
            colour = 1;
        }
        gfx_.text(centred(640, s), 96 + 16 * i - end_scroll_px_, s, colour,
                  track::id(track::text, 0x1000 + static_cast<std::uint32_t>(line) * 64));
    }
    for (int x = 0; x < 640; x += 16)
    {
        gfx_.blit(x, 80, sprite::mask_bar);
        gfx_.blit(x, 320, sprite::mask_bar);
    }
    gfx_.text(centred(640, "Hit Any Key to RANKING !"), 368, "Hit Any Key to RANKING !", 0);
    gfx_.text(centred(640, "THANK YOU FOR PLAYING."), 416, "THANK YOU FOR PLAYING.", 1);

    for (const int i : vox_.depth_order())
    {
        const auto &v = vox_.voxels[i];
        const double d = v.z + 2000.0;
        const auto sy = project(v.y, d);
        if (d <= 0.0 || !sy || !std::isfinite(v.x))
        {
            continue;
        }
        const double sx = v.x * 1000.0 / d + slide_x_;
        if (std::fabs(sx) > 1e6)
        {
            continue;
        }
        gfx_.blit(static_cast<int>(sx) - 4, 196 - *sy, vox_.rects[word.colour_offset + v.kind], vox_.id(i));
    }
}

// ---- name entry (FUN_0040b3f0) --------------------------------------------------------------------------

void Game::screen_name_entry()
{
    auto &name = data_.player_name;
    if (phase_ == 0)
    {
        play(Sfx::nameentry, true);
        angle_ = 0.0;
        ang_vel_ = 0.5;
        vox_.rects = {sprite::dot_orange, sprite::dot_black};
        phase_ = 1;
    }

    tile_screen(gfx_, sprite::name_entry_tile);
    const Point p = cursor();

    for (int r = 0; r < 3; ++r)
    {
        for (int c = 0; c < 32; ++c)
        {
            const char ch = static_cast<char>(0x20 * (r + 1) + c);
            // '$' separates fields in the save files, so unlike the original it cannot be entered
            if (ch == ' ' || ch == 0x7f || ch == '$')
            {
                continue;
            }
            const std::string_view s{&ch, 1};
            const bool hover = 32 + 18 * c <= p.x && p.x < 50 + 18 * c && 288 + 16 * r <= p.y && p.y < 304 + 16 * r;
            if (hover && take_click())
            {
                if (name.size() < save::max_name_length)
                {
                    name.push_back(ch);
                    play(Sfx::open);
                    phase_ = 1;
                }
                else
                {
                    play(Sfx::error);
                }
            }
            gfx_.text((36 * c + 82 - Gfx::text_width(s)) / 2, 288 + 16 * r, s, hover ? 1 : 0);
        }
    }

    const auto button = [&](int row, std::string_view label) {
        const bool hover = row * 16 < p.y && p.y < row * 16 + 16;
        gfx_.text(centred(640, label), row * 16, label, hover ? 1 : 0);
        return hover && take_click();
    };
    if (button(22, "SPACE"))
    {
        if (name.size() < save::max_name_length)
        {
            name.push_back(' ');
            play(Sfx::open);
            phase_ = 1;
        }
        else
        {
            play(Sfx::error);
        }
    }
    if (button(24, "BACK SPACE"))
    {
        if (!name.empty())
        {
            name.pop_back();
            play(Sfx::open);
            phase_ = 1;
        }
        else
        {
            play(Sfx::error);
        }
    }
    if (button(27, "OK"))
    {
        stop(Sfx::nameentry);
        play(Sfx::change);
        stage_ = 0;
        stage_rank_this_run_.fill(10);
        total_ms_ = 0;
        total_rank_this_run_ = 10;
        load_stage();
        state_ = State::intro;
        save_data();
        return;
    }

    // the name as swinging 3D dots
    if (phase_ == 1)
    {
        vox_.clear();
        vox_.build(gfx_, name);
        vox_.rotate_x(tilt_20);
        vox_.rotate_y(angle_ * deg_to_rad);
        phase_ = 2;
    }
    if (angle_ > 30.0)
    {
        ang_vel_ = -0.5;
    }
    else if (angle_ < -30.0)
    {
        ang_vel_ = 0.5;
    }
    const double step = ang_vel_ * 200.0 / fps;
    angle_ += step;
    vox_.rotate_y(step * deg_to_rad);
    for (const int i : vox_.depth_order())
    {
        const auto &v = vox_.voxels[i];
        const auto sx = project(v.x, v.z + 1800.0);
        const auto sy = project(v.y, v.z + 1800.0);
        if (sx && sy)
        {
            gfx_.blit(316 + *sx, 172 - *sy, vox_.rects[v.kind], vox_.id(i));
        }
    }

    gfx_.text(centred(640, "NAME ENTRY"), 16, "NAME ENTRY", 2);
    constexpr std::string_view prompt = "Enter Your Name (MAX 7 Characters) and Click 'OK' !!";
    gfx_.text(centred(640, prompt), 48, prompt, 0);
    gfx_.cursor(p.x, p.y);
}

// ---- ranking (FUN_0040bb90) -----------------------------------------------------------------------------

void Game::screen_ranking()
{
    tile_screen(gfx_, sprite::name_entry_tile);

    if (phase_ == 0)
    {
        ranking_view_ = 1;
        stage_sel_ = 0;
        vox_.clear();
        ang_vel_ = -0.2;
        play(Sfx::ranking, true);
        cam_z_ = 1500.0;
        vox_.rects = {sprite::dot_pink, sprite::dot_blue};

        // "RANKING" as a ring of letters
        constexpr std::string_view letters = "RANKING";
        double ring_angle = 0.0;
        for (std::size_t k = 0; k < letters.size(); ++k)
        {
            const std::size_t first = vox_.voxels.size();
            vox_.build(gfx_, letters.substr(k, 1));
            const double sx = std::sin(tilt_30), cx = std::cos(tilt_30);
            const double sy = std::sin(ring_angle * deg_to_rad), cy = std::cos(ring_angle * deg_to_rad);
            for (std::size_t i = first; i < vox_.voxels.size(); ++i)
            {
                auto &v = vox_.voxels[i];
                const double y = v.y;
                v.y = y * cx - v.z * sx;
                v.z = y * sx + v.z * cx - 220.0;
                const double x = v.x;
                v.x = x * cy - sy * v.z;
                v.z = cy * v.z + x * sy;
                v.y -= 300.0;
            }
            if (k + 1 < letters.size())
            {
                ring_angle += (Gfx::text_width(letters.substr(k + 1, 1)) + Gfx::text_width(letters.substr(k, 1))) * 1.2;
            }
        }
        phase_ = 1;
    }

    vox_.rotate_y(ang_vel_ * 200.0 / fps * deg_to_rad);
    for (const int i : vox_.depth_order())
    {
        const auto &v = vox_.voxels[i];
        const auto sx = project(v.x, v.z + 1500.0);
        const auto sy = project(v.y, v.z + 1500.0);
        if (sx && sy)
        {
            gfx_.blit(444 + *sx, -136 - *sy, vox_.rects[v.kind], vox_.id(i));
        }
    }

    const save::RankTable *table = &data_.total_ranking;
    int highlight = total_rank_this_run_;
    if (ranking_view_ == 1)
    {
        for (int y = 16; y <= 208; y += 16)
        {
            for (int x = 16; x <= 240; x += 16)
            {
                gfx_.blit(x, y, sprite::preview_tile);
            }
        }
        draw_stage_preview(stage_sel_, 16, 16);
        table = &data_.stage_ranking[stage_sel_];
        highlight = stage_rank_this_run_[stage_sel_];
    }

    gfx_.text(80, 240, "RANK", 1);
    gfx_.text(144, 240, "TIME", 1);
    gfx_.text(272, 240, "NAME", 1);
    gfx_.text(384, 240, "DATE", 1);
    for (int i = 0; i < save::ranks; ++i)
    {
        const auto &e = (*table)[i];
        const int colour = i == highlight ? 2 : 0;
        const int y = 256 + 16 * i;
        gfx_.text(90, y, std::format("{:02}", i + 1), colour);
        gfx_.text(144, y, format_time(e.time_ms), colour);
        gfx_.text(272, y, e.name, colour);
        gfx_.text(384, y, std::format("{:04}/{:02}/{:02} {:02}:{:02}", e.year, e.month, e.day, e.hour, e.minute), colour);
    }

    const Point p = cursor();
    const auto hit = [&](int row, int x0, int x1) { return row * 16 < p.y && p.y < row * 16 + 16 && x0 < p.x && p.x < x1; };
    const auto label = [&](int cx, int y, std::string_view s, int colour) { gfx_.text((2 * cx - Gfx::text_width(s)) / 2, y, s, colour); };

    const bool total_hover = hit(10, 256, 640);
    const bool stage_hover = hit(12, 256, 640);
    label(448, 160, "TOTAL TIME", total_hover ? 1 : ranking_view_ == 0 ? 2 : 0);
    label(448, 192, "STAGE TIME", stage_hover ? 1 : ranking_view_ == 1 ? 2 : 0);
    bool prev_hover = false, next_hover = false;
    if (ranking_view_ == 1)
    {
        prev_hover = hit(10, 16, 256);
        next_hover = hit(12, 16, 256);
        label(136, 160, "PREVIOUS", prev_hover ? 1 : 0);
        label(136, 176, std::format("{}", stage_sel_ + 1), 2);
        label(136, 192, "NEXT", next_hover ? 1 : 0);
    }
    const bool exit_hover = hit(28, -1, 641);
    label(320, 448, "EXIT", exit_hover ? 1 : 0);

    if ((total_hover || stage_hover || prev_hover || next_hover || exit_hover) && take_click())
    {
        if (total_hover)
        {
            ranking_view_ = 0;
            play(Sfx::open);
        }
        else if (stage_hover)
        {
            ranking_view_ = 1;
            play(Sfx::open);
        }
        else if (prev_hover)
        {
            stage_sel_ = stage_sel_ == 0 ? stages::count - 1 : stage_sel_ - 1;
            play(Sfx::open);
        }
        else if (next_hover)
        {
            stage_sel_ = stage_sel_ == stages::count - 1 ? 0 : stage_sel_ + 1;
            play(Sfx::open);
        }
        else
        {
            play(Sfx::change);
            stage_sel_ = 0;
            ranking_view_ = 0;
            phase_ = 0;
            state_ = State::title;
            stop(Sfx::ranking);
        }
    }
    gfx_.cursor(p.x, p.y);
}
