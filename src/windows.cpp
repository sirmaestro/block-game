// Pop-up windows: the animated frame engine (FUN_0040a970, FUN_0040b060, FUN_0040b160, FUN_0040b220) and
// the eight windows. See re/notes/menus.md.
#include "game.hpp"

#include <algorithm>
#include <format>

namespace
{

constexpr double fps = Game::ticks_per_second;

struct Geometry
{
    int x, y, w, h;
};

constexpr Geometry geometry[] = {
    {20, 8, 40, 14},  // options
    {36, 12, 34, 14}, // adjust volume
    {17, 9, 30, 12},  // pause (time trial)
    {36, 12, 36, 12}, // reset your data
    {36, 12, 42, 14}, // display broken blocks
    {12, 1, 40, 27},  // stage select (free mode pause)
    {25, 9, 30, 12},  // mode select
    {16, 11, 48, 8},  // message
};

constexpr Rect frame_tl{80, 144, 8, 8};
constexpr Rect frame_tr{104, 144, 8, 8};
constexpr Rect frame_bl{80, 168, 8, 8};
constexpr Rect frame_br{104, 168, 8, 8};
constexpr Rect frame_top{88, 144, 16, 8};
constexpr Rect frame_bottom{88, 168, 16, 8};
constexpr Rect frame_left{80, 152, 8, 16};
constexpr Rect frame_right{104, 152, 8, 16};
constexpr Rect frame_fill{88, 152, 16, 16};

Rect trimmed(Rect r, int w, int h)
{
    return {r.x, r.y, w, h};
}

}

// ---- engine -------------------------------------------------------------------------------------------

void Game::window_reset(Win id)
{
    const auto &g = geometry[id];
    windows_[id] = {g.x, g.y, g.w, g.h, closed, 8.0, 8.0};
}

void Game::window_frame(Win id)
{
    const auto &win = windows_[id];
    const int cx = win.x * 8 + win.w * 4;
    const int cy = win.y * 16 + win.h * 8;
    const int hw = static_cast<int>(win.half_w);
    const int hh = static_cast<int>(win.half_h);
    const int l = cx - hw, r = cx + hw - 8, t = cy - hh, b = cy + hh - 8;
    const int nx = (hw - 8) / 8, last_w = ((hw - 8) * 2) % 16;
    const int ny = (hh - 8) / 8, last_h = ((hh - 8) * 2) % 16;

    gfx_.blit(l, t, frame_tl);
    gfx_.blit(r, t, frame_tr);
    gfx_.blit(l, b, frame_bl);
    gfx_.blit(r, b, frame_br);
    for (int i = 0; i <= nx; ++i)
    {
        const int w = i == nx ? last_w : 16;
        gfx_.blit(l + 8 + 16 * i, t, trimmed(frame_top, w, 8));
        gfx_.blit(l + 8 + 16 * i, b, trimmed(frame_bottom, w, 8));
    }
    for (int j = 0; j <= ny; ++j)
    {
        const int h = j == ny ? last_h : 16;
        gfx_.blit(l, t + 8 + 16 * j, trimmed(frame_left, 8, h));
        gfx_.blit(r, t + 8 + 16 * j, trimmed(frame_right, 8, h));
        for (int i = 0; i <= nx; ++i)
        {
            gfx_.blit(l + 8 + 16 * i, t + 8 + 16 * j, trimmed(frame_fill, i == nx ? last_w : 16, h));
        }
    }
}

// Width springs open first, then height. Returns true once fully open.
bool Game::window_open_step(Win id)
{
    auto &win = windows_[id];
    const double target_w = win.w * 4 - 8;
    win.half_w += (target_w - win.half_w) * 0.2 * 100.0 / fps;
    if (win.half_w > target_w - 1.0)
    {
        win.half_w = target_w;
        const double target_h = win.h * 8 - 8;
        win.half_h += (target_h - win.half_h) * 0.2 * 100.0 / fps;
        if (win.half_h > target_h - 1.0)
        {
            win.half_h = target_h;
            return true;
        }
    }
    return false;
}

// Height collapses first, then width. Returns true once fully closed.
bool Game::window_close_step(Win id)
{
    auto &win = windows_[id];
    win.half_h += (8.0 - win.half_h) * 0.2 * 100.0 / fps;
    if (win.half_h < 9.0)
    {
        win.half_h = 8.0;
        win.half_w += (8.0 - win.half_w) * 0.2 * 100.0 / fps;
        if (win.half_w < 9.0)
        {
            win.half_w = 8.0;
            return true;
        }
    }
    return false;
}

bool Game::window_row_hit(Win id, int row, Point p) const
{
    const auto &win = windows_[id];
    return win.x * 8 < p.x && p.x < (win.x + win.w) * 8 && (win.y + row) * 16 < p.y && p.y < (win.y + row + 1) * 16;
}

void Game::window_text(Win id, int row, std::string_view s, int colour)
{
    const auto &win = windows_[id];
    gfx_.text((win.w * 8 + win.x * 16 - Gfx::text_width(s)) / 2, (win.y + row) * 16, s, colour);
}

// ---- windows ------------------------------------------------------------------------------------------

void Game::options_window()
{
    window_frame(win_options);
    auto &win = windows_[win_options];
    if (win.state == closing)
    {
        if (window_close_step(win_options))
        {
            window_reset(win_options);
        }
        return;
    }
    if (!window_open_step(win_options))
    {
        return;
    }

    const Point p = cursor();
    const bool active = windows_[win_volume].state == closed && windows_[win_reset].state == closed &&
                        windows_[win_broken].state == closed;
    const auto item = [&](int row, std::string_view s) {
        const bool hover = active && window_row_hit(win_options, row, p);
        window_text(win_options, row, s, hover ? 1 : 0);
        return hover && take_click();
    };

    window_text(win_options, 1, "OPTION", 2);
    if (item(4, "ADJUST VOLUME"))
    {
        play(Sfx::open);
        windows_[win_volume].state = opening;
    }
    if (item(6, "RESET YOUR DATA"))
    {
        play(Sfx::open);
        windows_[win_reset].state = opening;
    }
    if (item(8, "DISPLAY BROKEN BLOCKS"))
    {
        play(Sfx::open);
        windows_[win_broken].state = opening;
    }
    if (item(11, "CLOSE"))
    {
        play(Sfx::close);
        win.state = closing;
    }
    gfx_.cursor(p.x, p.y);
}

void Game::volume_window()
{
    window_frame(win_volume);
    auto &win = windows_[win_volume];
    if (win.state == closing)
    {
        if (window_close_step(win_volume))
        {
            window_reset(win_volume);
        }
        return;
    }
    if (!window_open_step(win_volume))
    {
        return;
    }

    const Point p = cursor();
    // the slider follows the mouse while the button is held
    if (window_row_hit(win_volume, 4, p) && left_down_)
    {
        data_.volume = std::clamp(double(p.x - (win.x * 8 + 64)), 0.0, 128.0);
        audio_.set_master_volume(data_.volume);
    }
    const bool test = window_row_hit(win_volume, 8, p);
    const bool close = window_row_hit(win_volume, 11, p);

    gfx_.blit(win.x * 8 + 72, (win.y + 4) * 16, sprite::volume_track);
    gfx_.blit(win.x * 8 + 64 + static_cast<int>(data_.volume), (win.y + 4) * 16, sprite::ball_normal);
    window_text(win_volume, 1, "ADJUST VOLUME", 2);
    gfx_.text(win.x * 8 + 26, (win.y + 4) * 16, "MIN", 0);
    gfx_.text((win.x + win.w) * 8 - 66, (win.y + 4) * 16, "MAX", 0);
    window_text(win_volume, 8, "TEST", test ? 1 : 0);
    window_text(win_volume, 11, "CLOSE", close ? 1 : 0);

    if ((test || close) && take_click())
    {
        if (test)
        {
            play(Sfx::error);
        }
        else
        {
            play(Sfx::close);
            win.state = closing;
            save_data();
        }
    }
    gfx_.cursor(p.x, p.y);
}

// Shared by the time-trial pause window and the free-mode stage select window.
void Game::pause_window_actions(Win id, int try_again_row, int end_game_row, int cancel_row, Point p, bool active)
{
    auto &win = windows_[id];
    const auto item = [&](int row, std::string_view s) {
        const bool hover = active && window_row_hit(id, row, p);
        window_text(id, row, s, hover ? 1 : 0);
        return hover && take_click();
    };

    if (item(try_again_row, "TRY AGAIN"))
    {
        play(Sfx::change);
        win.state = closing;
        load_stage();
        state_ = State::intro;
    }
    if (item(end_game_row, "END GAME"))
    {
        play(Sfx::change);
        win.state = closing;
        phase_ = 0;
        flag_ = 0;
        state_ = State::title;
    }
    if (item(cancel_row, "CANCEL"))
    {
        play(Sfx::close);
        if (state_ == State::play)
        {
            resume_bgm();
        }
        win.state = closing;
    }
}

void Game::pause_window()
{
    window_frame(win_pause);
    auto &win = windows_[win_pause];
    if (win.state == closing)
    {
        if (window_close_step(win_pause))
        {
            window_reset(win_pause);
            set_cursor(saved_cursor_.x, saved_cursor_.y);
        }
        return;
    }
    stop(Sfx::bgm);
    stop(Sfx::mugen);
    if (!window_open_step(win_pause))
    {
        return;
    }

    const Point p = cursor();
    const bool active = windows_[win_options].state == closed && windows_[win_stage_select].state == closed &&
                        windows_[win_message].state == closed;
    window_text(win_pause, 1, "PAUSE", 2);
    pause_window_actions(win_pause, 4, 6, 9, p, active);
    gfx_.cursor(p.x, p.y);
}

void Game::stage_select_window()
{
    window_frame(win_stage_select);
    auto &win = windows_[win_stage_select];
    if (win.state == closing)
    {
        if (window_close_step(win_stage_select))
        {
            window_reset(win_stage_select);
            set_cursor(saved_cursor_.x, saved_cursor_.y);
        }
        return;
    }
    stop(Sfx::bgm);
    stop(Sfx::mugen);
    if (!window_open_step(win_stage_select))
    {
        return;
    }

    const Point p = cursor();
    const auto hover = [&](int row) { return window_row_hit(win_stage_select, row, p); };
    const bool prev = hover(16), next = hover(18), go = hover(21);

    // stage preview
    for (int j = 0; j < 13; ++j)
    {
        for (int i = 0; i < 15; ++i)
        {
            gfx_.blit(win.x * 8 + 40 + 16 * i, (win.y + 7 + j) * 16, sprite::preview_tile);
        }
    }
    draw_stage_preview(stage_sel_, win.x * 8 + 40, win.y * 16 + 112);

    window_text(win_stage_select, 1, "STAGE SELECT", 2);
    pause_window_actions(win_stage_select, 3, 5, 24, p, true);
    window_text(win_stage_select, 16, "PREVIOUS", prev ? 1 : 0);
    window_text(win_stage_select, 17, std::format("{}", stage_sel_ + 1), 2);
    window_text(win_stage_select, 18, "NEXT", next ? 1 : 0);
    window_text(win_stage_select, 21, "GOTO THIS STAGE", go ? 1 : 0);
    if ((prev || next || go) && take_click())
    {
        if (prev)
        {
            play(Sfx::open);
            stage_sel_ = stage_sel_ == 0 ? stages::count - 1 : stage_sel_ - 1;
        }
        else if (next)
        {
            play(Sfx::open);
            stage_sel_ = stage_sel_ == stages::count - 1 ? 0 : stage_sel_ + 1;
        }
        else
        {
            stage_ = stage_sel_;
            play(Sfx::change);
            load_stage();
            win.state = closing;
            state_ = State::intro;
        }
    }
    gfx_.cursor(p.x, p.y);
}

void Game::reset_window()
{
    window_frame(win_reset);
    auto &win = windows_[win_reset];
    if (win.state == closing)
    {
        if (window_close_step(win_reset))
        {
            window_reset(win_reset);
        }
        return;
    }
    if (!window_open_step(win_reset))
    {
        return;
    }

    const Point p = cursor();
    const bool ok = window_row_hit(win_reset, 6, p);
    const bool cancel = window_row_hit(win_reset, 9, p);
    window_text(win_reset, 1, "RESET YOUR DATA", 2);
    window_text(win_reset, 3, "Really?", 0);
    window_text(win_reset, 6, "OK", ok ? 1 : 0);
    window_text(win_reset, 9, "CANCEL", cancel ? 1 : 0);

    if ((ok || cancel) && take_click())
    {
        if (ok)
        {
            // like the original, OK resets but leaves the window open
            play(Sfx::change);
            data_ = save::Data{};
            audio_.set_master_volume(data_.volume);
            stage_rank_this_run_.fill(10);
            total_rank_this_run_ = 10;
            save_data();
        }
        else
        {
            play(Sfx::close);
            win.state = closing;
        }
    }
    gfx_.cursor(p.x, p.y);
}

void Game::broken_window()
{
    window_frame(win_broken);
    auto &win = windows_[win_broken];
    if (win.state == closing)
    {
        if (window_close_step(win_broken))
        {
            window_reset(win_broken);
        }
        return;
    }
    if (!window_open_step(win_broken))
    {
        return;
    }

    const Point p = cursor();
    const bool yes = window_row_hit(win_broken, 6, p);
    const bool no = window_row_hit(win_broken, 8, p);
    const bool close = window_row_hit(win_broken, 11, p);
    if ((yes || no || close) && take_click())
    {
        if (close)
        {
            play(Sfx::close);
            win.state = closing;
            save_data();
        }
        else
        {
            play(Sfx::open);
            data_.show_broken_blocks = yes;
        }
    }

    gfx_.blit(win.x * 8 + 120, (win.y + (data_.show_broken_blocks ? 6 : 8)) * 16, sprite::ball_normal);
    window_text(win_broken, 1, "DISPLAY BROKEN BLOCKS", 2);
    window_text(win_broken, 3, "For Better Performance,", 0);
    window_text(win_broken, 4, "Select 'NO'.", 0);
    window_text(win_broken, 6, "YES", yes ? 1 : 0);
    window_text(win_broken, 8, "NO", no ? 1 : 0);
    window_text(win_broken, 11, "CLOSE", close ? 1 : 0);
    gfx_.cursor(p.x, p.y);
}

void Game::mode_select_window()
{
    window_frame(win_mode_select);
    auto &win = windows_[win_mode_select];
    if (win.state == closing)
    {
        if (window_close_step(win_mode_select))
        {
            window_reset(win_mode_select);
        }
        return;
    }
    if (!window_open_step(win_mode_select))
    {
        return;
    }

    const Point p = cursor();
    const bool active = windows_[win_message].state == closed;
    const auto item = [&](int row, std::string_view s) {
        const bool hover = active && window_row_hit(win_mode_select, row, p);
        window_text(win_mode_select, row, s, hover ? 1 : 0);
        return hover && take_click();
    };

    window_text(win_mode_select, 1, "MODE SELECT", 2);
    const auto start = [&](int mode) {
        win.state = closing;
        play(Sfx::open);
        stop(Sfx::title);
        mode_ = mode;
        phase_ = 0;
        state_ = State::name_entry;
    };
    if (item(4, "TIME TRIAL MODE"))
    {
        start(1);
    }
    if (item(6, "FREE MODE"))
    {
        if (data_.free_mode_unlocked)
        {
            start(2);
        }
        else
        {
            play(Sfx::error);
            windows_[win_message].state = opening;
        }
    }
    if (item(9, "CANCEL"))
    {
        play(Sfx::close);
        win.state = closing;
    }
    gfx_.cursor(p.x, p.y);
}

void Game::message_window(std::string_view message)
{
    window_frame(win_message);
    auto &win = windows_[win_message];
    if (win.state == closing)
    {
        if (window_close_step(win_message))
        {
            window_reset(win_message);
        }
        return;
    }
    if (!window_open_step(win_message))
    {
        return;
    }

    const Point p = cursor();
    const bool ok = window_row_hit(win_message, 5, p);
    window_text(win_message, 1, "MESSAGE", 2);
    window_text(win_message, 3, message, 0);
    window_text(win_message, 5, "OK", ok ? 1 : 0);
    if (ok && take_click())
    {
        play(Sfx::close);
        win.state = closing;
    }
    gfx_.cursor(p.x, p.y);
}
