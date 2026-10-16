// Pop-up windows: the animated frame engine (FUN_0040a970, FUN_0040b060, FUN_0040b160, FUN_0040b220) and
// the eight windows. See re/notes/menus.md.
#include "game.hpp"

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <format>
#include <iterator>
#include <string>
#include <system_error>

namespace
{

constexpr double fps = Game::ticks_per_second;

struct Geometry
{
    int x, y, w, h;
};

constexpr Geometry geometry[] = {
    {20, 6, 40, 17},  // options (rebuild: taller, for the new entries)
    {36, 10, 34, 18}, // adjust volume (rebuild: music and sound sliders)
    {17, 9, 30, 12},  // pause (time trial)
    {36, 12, 36, 12}, // reset your data
    {36, 12, 42, 14}, // display broken blocks
    {2, 1, 60, 28},   // stage select (free mode pause; rebuild: a page of stage thumbnails over the playfield)
    {20, 9, 40, 13},  // mode select (rebuild: wider and taller, for the stage pack)
    {16, 11, 48, 8},  // message
    {18, 5, 44, 20},  // screen settings (rebuild)
    {34, 9, 38, 14},  // controls (rebuild)
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
                        windows_[win_broken].state == closed && windows_[win_screen].state == closed &&
                        windows_[win_controls].state == closed;
    const auto item = [&](int row, std::string_view s) {
        const bool hover = active && window_row_hit(win_options, row, p);
        window_text(win_options, row, s, hover ? 1 : 0);
        return hover && take_click();
    };
    const auto open = [&](Win id) {
        play(Sfx::open);
        windows_[id].state = opening;
    };

    window_text(win_options, 1, "OPTION", 2);
    if (item(4, "ADJUST VOLUME"))
    {
        open(win_volume);
    }
    if (item(6, "SCREEN SETTINGS"))
    {
        open(win_screen);
    }
    if (item(8, "CONTROLS"))
    {
        open(win_controls);
    }
    if (item(10, "RESET YOUR DATA"))
    {
        open(win_reset);
    }
    if (item(12, "DISPLAY BROKEN BLOCKS"))
    {
        open(win_broken);
    }
    if (item(15, "CLOSE"))
    {
        play(Sfx::close);
        win.state = closing;
    }
    gfx_.cursor(p.x, p.y);
}

// A 0..128 slider drawn like the original volume control; follows the mouse while the button is held on its
// row. Returns true when the value changed.
bool Game::volume_slider(Win id, int row, double &value, Point p)
{
    const auto &win = windows_[id];
    bool changed = false;
    if (window_row_hit(id, row, p) && left_down_)
    {
        const double v = std::clamp(double(p.x - (win.x * 8 + 64)), 0.0, 128.0);
        changed = v != value;
        value = v;
    }
    gfx_.blit(win.x * 8 + 72, (win.y + row) * 16, sprite::volume_track);
    gfx_.blit(win.x * 8 + 64 + static_cast<int>(value), (win.y + row) * 16, sprite::ball_normal);
    gfx_.text(win.x * 8 + 26, (win.y + row) * 16, "MIN", 0);
    gfx_.text((win.x + win.w) * 8 - 66, (win.y + row) * 16, "MAX", 0);
    return changed;
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
    window_text(win_volume, 1, "ADJUST VOLUME", 2);
    window_text(win_volume, 3, "MASTER", 0);
    window_text(win_volume, 6, "MUSIC", 0);
    window_text(win_volume, 9, "SOUND", 0);
    bool changed = volume_slider(win_volume, 4, settings_.master_volume, p);
    changed |= volume_slider(win_volume, 7, settings_.music_volume, p);
    changed |= volume_slider(win_volume, 10, settings_.sound_volume, p);
    if (changed)
    {
        apply_volumes();
    }

    const bool test = window_row_hit(win_volume, 13, p);
    const bool close = window_row_hit(win_volume, 16, p);
    window_text(win_volume, 13, "TEST", test ? 1 : 0);
    window_text(win_volume, 16, "CLOSE", close ? 1 : 0);
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
            settings_changed_ = true;
        }
    }
    gfx_.cursor(p.x, p.y);
}

void Game::screen_window()
{
    window_frame(win_screen);
    auto &win = windows_[win_screen];
    if (win.state == closing)
    {
        if (window_close_step(win_screen))
        {
            window_reset(win_screen);
        }
        return;
    }
    if (!window_open_step(win_screen))
    {
        return;
    }

    auto &s = settings_;
    constexpr std::string_view display_names[] = {"WINDOW", "BORDERLESS", "FULL SCREEN"};
    constexpr std::string_view scaling_names[] = {"PIXEL PERFECT", "FIT", "STRETCH"};
    constexpr std::string_view filter_names[] = {"NEAREST", "SHARP", "SCANLINES"};
    const auto on_off = [](bool on) { return on ? "ON" : "OFF"; };
    const auto next = [](auto value, int count) { return static_cast<decltype(value)>((int(value) + 1) % count); };

    const Point p = cursor();
    const auto item = [&](int row, const std::string &label) {
        const bool hover = window_row_hit(win_screen, row, p);
        window_text(win_screen, row, label, hover ? 1 : 0);
        return hover && take_click();
    };

    window_text(win_screen, 1, "SCREEN SETTINGS", 2);
    bool changed = false;
    if (item(3, std::format("DISPLAY : {}", display_names[int(s.display)])))
    {
        s.display = next(s.display, 3);
        changed = true;
    }
    if (item(5, std::format("SCALING : {}", scaling_names[int(s.scaling)])))
    {
        s.scaling = next(s.scaling, 3);
        changed = true;
    }
    if (item(7, std::format("FILTER : {}", filter_names[int(s.filter)])))
    {
        s.filter = next(s.filter, 3);
        changed = true;
    }
    if (item(9, std::format("SIDE FRAME : {}", on_off(s.side_frame))))
    {
        s.side_frame = !s.side_frame;
        changed = true;
    }
    if (item(11, std::format("VSYNC : {}", on_off(s.vsync))))
    {
        s.vsync = !s.vsync;
        changed = true;
    }
    const auto limit = s.fps_limit ? std::format("{}", s.fps_limit) : std::string{"NONE"};
    if (item(13, std::format("FPS LIMIT : {}", limit)))
    {
        const auto it = std::ranges::find(settings::fps_limits, s.fps_limit);
        const auto i = it == std::end(settings::fps_limits) ? 0 : it - std::begin(settings::fps_limits);
        s.fps_limit = settings::fps_limits[(i + 1) % std::size(settings::fps_limits)];
        changed = true;
    }
    if (item(15, std::format("SMOOTH MOTION : {}", on_off(s.smooth_motion))))
    {
        s.smooth_motion = !s.smooth_motion;
        changed = true;
    }
    if (changed)
    {
        play(Sfx::open);
        settings_changed_ = true;
    }
    if (item(18, "CLOSE"))
    {
        play(Sfx::close);
        win.state = closing;
    }
    gfx_.cursor(p.x, p.y);
}

void Game::controls_window()
{
    window_frame(win_controls);
    auto &win = windows_[win_controls];
    if (win.state == closing)
    {
        if (window_close_step(win_controls))
        {
            window_reset(win_controls);
        }
        return;
    }
    if (!window_open_step(win_controls))
    {
        return;
    }

    // shown as a multiplier, formatted from integers (floating-point std::format needs macOS 13.3)
    const auto multiplier = [](double slider) {
        const int hundredths = static_cast<int>(std::lround(settings::mouse_multiplier(slider) * 100.0));
        return std::format("x{}.{:02}", hundredths / 100, hundredths % 100);
    };

    const Point p = cursor();
    window_text(win_controls, 1, "CONTROLS", 2);
    window_text(win_controls, 3, "MOUSE SPEED  " + multiplier(settings_.mouse_speed), 0);
    volume_slider(win_controls, 4, settings_.mouse_speed, p);
    window_text(win_controls, 6, "KEY / PAD SPEED  " + multiplier(settings_.pad_speed), 0);
    volume_slider(win_controls, 7, settings_.pad_speed, p);
    window_text(win_controls, 9, "Arrows/Stick Move  Z/A Click", 0);
    window_text(win_controls, 10, "X/B Launch  Esc/Start Pause", 0);

    const bool close = window_row_hit(win_controls, 12, p);
    window_text(win_controls, 12, "CLOSE", close ? 1 : 0);
    if (close && take_click())
    {
        play(Sfx::close);
        win.state = closing;
        settings_changed_ = true;
    }
    gfx_.cursor(p.x, p.y);
}

// The time-trial pause window's items.
void Game::pause_window_actions(Win id, int try_again_row, int end_game_row, int cancel_row, Point p, bool active)
{
    const auto item = [&](int row, std::string_view s) {
        const bool hover = active && window_row_hit(id, row, p);
        window_text(id, row, s, hover ? 1 : 0);
        return hover && take_click();
    };

    if (item(try_again_row, "TRY AGAIN"))
    {
        try_again(id);
    }
    if (item(end_game_row, "END GAME"))
    {
        end_game(id);
    }
    if (item(cancel_row, "CANCEL"))
    {
        cancel_pause(id);
    }
}

void Game::try_again(Win id)
{
    play(Sfx::change);
    windows_[id].state = closing;
    load_stage();
    state_ = State::intro;
}

void Game::end_game(Win id)
{
    play(Sfx::change);
    windows_[id].state = closing;
    phase_ = 0;
    flag_ = 0;
    state_ = State::title;
}

void Game::cancel_pause(Win id)
{
    play(Sfx::close);
    if (state_ == State::play)
    {
        resume_bgm();
    }
    windows_[id].state = closing;
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

    // Rebuild: a page of nine stage thumbnails to click, in place of the original's one large preview with
    // PREVIOUS / NEXT / GOTO THIS STAGE.
    const Point p = cursor();
    const int pages = (stage_count() + select_per_page - 1) / select_per_page;
    select_page_ = std::clamp(select_page_, 0, pages - 1);

    const auto inside = [&](int x, int y, int w, int h) { return x <= p.x && p.x < x + w && y <= p.y && p.y < y + h; };
    // a label centred on cx; returns whether the cursor is on it
    const auto button = [&](int cx, int y, std::string_view s, int colour_if_idle) {
        const int w = Gfx::text_width(s);
        const bool hover = inside(cx - w / 2 - 8, y, w + 16, 16);
        gfx_.text(cx - w / 2, y, s, hover ? 1 : colour_if_idle);
        return hover;
    };

    const int cx = win.x * 8 + win.w * 4; // window centre
    const int left = cx - select_column_step, right = cx + select_column_step;
    gfx_.text(cx - Gfx::text_width("STAGE SELECT") / 2, (win.y + 1) * 16, "STAGE SELECT", 2);
    const bool again = button(left, 64, "TRY AGAIN", 0);
    const bool end = button(right, 64, "END GAME", 0);

    int picked = -1;
    for (int slot = 0; slot < select_per_page; ++slot)
    {
        const int stage = select_page_ * select_per_page + slot;
        if (stage >= stage_count())
        {
            break;
        }
        const int x = cx + (slot % 3 - 1) * select_column_step - thumbnail_width / 2;
        const int y = 92 + (slot / 3) * 104;
        const bool hover = inside(x - 4, y - 4, thumbnail_width + 8, thumbnail_height + 24);
        draw_stage_thumbnail(stage, x, y);
        const auto number = std::format("{}", stage + 1);
        gfx_.text(x + (thumbnail_width - Gfx::text_width(number)) / 2, y + thumbnail_height + 2, number,
                  hover ? 1 : stage == stage_ ? 2 : 0);
        if (hover)
        {
            picked = stage;
        }
    }

    const bool prev = pages > 1 && button(left, 408, "PREVIOUS", 0);
    const bool next = pages > 1 && button(right, 408, "NEXT", 0);
    const auto page = std::format("PAGE {}/{}", select_page_ + 1, pages);
    gfx_.text(cx - Gfx::text_width(page) / 2, 408, page, 2);
    const bool cancel = button(cx, 432, "CANCEL", 0);

    if ((again || end || picked >= 0 || prev || next || cancel) && take_click())
    {
        if (again)
        {
            try_again(win_stage_select);
        }
        else if (end)
        {
            end_game(win_stage_select);
        }
        else if (cancel)
        {
            cancel_pause(win_stage_select);
        }
        else if (prev || next)
        {
            play(Sfx::open);
            select_page_ = (select_page_ + (next ? 1 : pages - 1)) % pages;
        }
        else
        {
            stage_ = picked;
            play(Sfx::change);
            load_stage();
            win.state = closing;
            state_ = State::intro;
        }
    }
    gfx_.cursor(p.x, p.y);
}

// A small picture of a stage: each block as a 6x3 dot in its colour, on the preview background.
void Game::draw_stage_thumbnail(int stage, int x, int y)
{
    for (int ty = 0; ty < thumbnail_height; ty += 16)
    {
        for (int tx = 0; tx < thumbnail_width; tx += 16)
        {
            const Rect tile = sprite::preview_tile;
            gfx_.blit(x + tx, y + ty,
                      {tile.x, tile.y, std::min(16, thumbnail_width - tx), std::min(16, thumbnail_height - ty)});
        }
    }
    const auto &layout = pack().stages[stage];
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
                // the middle of the stage preview's mini block, which is its plain colour
                const Rect mini = sprite::mini_block(icon);
                gfx_.blit(x + 6 * col, y + 3 * row, {mini.x + 5, mini.y + 2, 6, 3});
            }
        }
    }
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
            // like the original, OK resets but leaves the window open; the rebuild keeps the settings in
            // block.ini and also deletes the replays, which belonged to the records
            play(Sfx::change);
            data_ = save::Data{};
            std::error_code ec;
            std::filesystem::remove_all(save_dir_ / "replays", ec);
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
            settings_changed_ = true;
        }
        else
        {
            play(Sfx::open);
            settings_.show_broken_blocks = yes;
        }
    }

    gfx_.blit(win.x * 8 + 120, (win.y + (settings_.show_broken_blocks ? 6 : 8)) * 16, sprite::ball_normal);
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
    // rebuild: choose the stage pack, when there are custom ones
    if (packs_.size() > 1 && item(3, "STAGES : " + pack().name))
    {
        play(Sfx::open);
        pack_ = (pack_ + 1) % packs_.size();
        settings_.stage_pack = pack_ == 0 ? std::string{} : pack().id;
        settings_changed_ = true;
    }
    const auto start = [&](int mode) {
        win.state = closing;
        play(Sfx::open);
        stop(Sfx::title);
        mode_ = mode;
        phase_ = 0;
        state_ = State::name_entry;
    };
    if (item(5, "TIME TRIAL MODE"))
    {
        start(1);
    }
    if (item(7, "FREE MODE"))
    {
        if (free_mode_available())
        {
            start(2);
        }
        else
        {
            play(Sfx::error);
            windows_[win_message].state = opening;
        }
    }
    if (item(10, "CANCEL"))
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
