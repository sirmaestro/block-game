#include "game.hpp"

#include <SDL3/SDL.h>

#include <algorithm>
#include <cmath>
#include <utility>

Game::Game(Gfx &gfx, Audio &audio, settings::Settings &settings, std::vector<stages::Stage> stage_data,
           std::filesystem::path save_dir)
    : gfx_(gfx), audio_(audio), stage_data_(std::move(stage_data)), save_dir_(std::move(save_dir)),
      data_(save::load(save_dir_)), settings_(settings)
{
    apply_volumes();
    rand_seed_ = static_cast<unsigned>(SDL_GetTicks());
    stage_rank_this_run_.fill(10);
    reset_windows();
    balls_.reserve(500);
}

void Game::save_data()
{
    if (!save::write(save_dir_, data_))
    {
        SDL_Log("could not save to %s", save_dir_.string().c_str());
    }
}

bool Game::take_settings_changed()
{
    const bool changed = settings_changed_;
    settings_changed_ = false;
    return changed;
}

void Game::apply_volumes()
{
    audio_.set_volumes(data_.volume, settings_.music_volume, settings_.sound_volume);
}

void Game::focus_lost()
{
    left_button_up();
    // the original kept running when it lost focus; pause instead, as a key press would
    if (in_game_state() && pause_windows_closed())
    {
        key_down();
    }
}

LiveOffsets Game::live_offsets() const
{
    LiveOffsets live;
    const Point now = cursor();
    live.cursor_dx = now.x - drawn_cursor_.x;
    live.cursor_dy = now.y - drawn_cursor_.y;
    if (state_ == State::play && pause_windows_closed())
    {
        // the paddle follows the mouse at the display rate, clamped as update_paddle() will clamp it
        const int lo = 8 * paddle_units_ + 16;
        const int hi = (62 - paddle_units_) * 8;
        live.paddle = true;
        live.paddle_dx = std::clamp(now.x, lo, std::max(lo, hi)) - drawn_paddle_x_;
    }
    return live;
}

// ---- helpers ------------------------------------------------------------------------------------------

int Game::rand()
{
    // MSVC CRT rand()
    rand_seed_ = rand_seed_ * 214013u + 2531011u;
    return static_cast<int>((rand_seed_ >> 16) & 0x7fff);
}

Game::Point Game::cursor() const
{
    return {static_cast<int>(mouse_x_), static_cast<int>(mouse_y_)};
}

void Game::set_cursor(int x, int y)
{
    mouse_x_ = std::clamp(x, 0, screen_width - 1);
    mouse_y_ = std::clamp(y, 0, screen_height - 1);
}

void Game::mouse_moved(double dx, double dy)
{
    // GetCursorPos in the original's exclusive full screen mode: clamped to the 640x480 screen
    mouse_x_ = std::clamp(mouse_x_ + dx, 0.0, screen_width - 1.0);
    mouse_y_ = std::clamp(mouse_y_ + dy, 0.0, screen_height - 1.0);
}

// The original's menus fired every frame while the button was held (so e.g. RESET YOUR DATA -> OK
// repeated); the rebuild acts once per press.
bool Game::take_click()
{
    const bool clicked = click_pending_;
    click_pending_ = false;
    return clicked;
}

bool Game::in_game_state() const
{
    return state_ == State::play || state_ == State::intro || state_ == State::clear || state_ == State::game_over;
}

bool Game::pause_windows_closed() const
{
    return windows_[win_pause].state == closed && windows_[win_stage_select].state == closed;
}

void Game::play(Sfx id, bool loop)
{
    audio_.play(id, loop);
}

void Game::stop(Sfx id)
{
    audio_.stop(id);
}

void Game::resume_bgm()
{
    play(mugen_ms_ > 0 ? Sfx::mugen : Sfx::bgm, true);
}

// FUN_0040b220 for every window
void Game::reset_windows()
{
    for (int id = 0; id < win_count; ++id)
    {
        window_reset(static_cast<Win>(id));
    }
}

// ---- frame tick (FUN_00407fa0) ------------------------------------------------------------------------

void Game::tick(int dt_ms)
{
    gfx_.begin_frame();
    run_tick(dt_ms);
    drawn_cursor_ = cursor();
}

void Game::run_tick(int dt_ms)
{

    switch (state_)
    {
        case State::boot:
            screen_boot(dt_ms);
            return;

        case State::title:
            screen_title();
            if (windows_[win_options].state != closed)
            {
                options_window();
            }
            if (windows_[win_volume].state != closed)
            {
                volume_window();
            }
            if (windows_[win_reset].state != closed)
            {
                reset_window();
            }
            if (windows_[win_broken].state != closed)
            {
                broken_window();
            }
            if (windows_[win_screen].state != closed)
            {
                screen_window();
            }
            if (windows_[win_mouse].state != closed)
            {
                mouse_window();
            }
            if (windows_[win_mode_select].state != closed)
            {
                mode_select_window();
            }
            if (windows_[win_message].state != closed)
            {
                message_window("You Must Clear All Stages First !!");
            }
            return;

        case State::name_entry:
            screen_name_entry();
            return;

        case State::ranking:
            screen_ranking();
            return;

        case State::ending:
            if (phase_ == 3)
            {
                phase_ms_ += dt_ms;
                if (phase_ms_ > 3000)
                {
                    phase_ = 4;
                    phase_ms_ = 0;
                }
            }
            else if (phase_ == 4)
            {
                phase_ms_ += dt_ms;
                if (phase_ms_ > 700)
                {
                    phase_ = 1;
                    end_word_ = (end_word_ + 1) % 14;
                    phase_ms_ = 0;
                }
            }
            end_scroll_ms_ += dt_ms;
            if (end_scroll_ms_ > 50)
            {
                end_scroll_ms_ = 0;
                if (++end_scroll_px_ > 15)
                {
                    end_scroll_px_ = 0;
                    if (++end_top_line_ > 67)
                    {
                        end_top_line_ = 0;
                    }
                }
            }
            screen_ending();
            return;

        case State::play:
            if (pause_windows_closed())
            {
                for (int *timer : {&big_ms_, &small_ms_, &reverse_ms_, &mugen_ms_})
                {
                    if (*timer > 0)
                    {
                        *timer -= dt_ms;
                    }
                }
                stage_ms_[stage_] += dt_ms;
                total_ms_ += dt_ms;
                physics_step();
                physics_step();
                update_items_and_debris();
                if (remaining_ == 0)
                {
                    state_ = State::clear;
                }
                else if (balls_.empty() && stock_ == 0 && !infinite_)
                {
                    state_ = State::game_over;
                }
            }
            render_playfield();
            break;

        case State::intro:
            if (pause_windows_closed())
            {
                if (phase_ == 2)
                {
                    phase_ms_ += dt_ms;
                    if (phase_ms_ > 700)
                    {
                        phase_ = 3;
                        phase_ms_ = 0;
                    }
                }
                else if (phase_ == 6)
                {
                    phase_ms_ += dt_ms;
                    if (phase_ms_ > 300)
                    {
                        phase_ = 7;
                        phase_ms_ = 0;
                    }
                }
            }
            render_playfield();
            screen_intro();
            break;

        case State::clear:
            phase_ms_ += dt_ms;
            if (phase_ms_ > 50)
            {
                phase_ms_ = 0;
                flag_ = flag_ != 1 ? 1 : 0;
            }
            render_playfield();
            screen_clear();
            break;

        case State::game_over:
            if (pause_windows_closed() && phase_ == 2)
            {
                phase_ms_ += dt_ms;
                if (phase_ms_ > 1000)
                {
                    phase_ = 3;
                    phase_ms_ = 0;
                }
            }
            render_playfield();
            screen_game_over();
            break;
    }

    if (windows_[win_pause].state != closed)
    {
        pause_window();
    }
    if (windows_[win_stage_select].state != closed)
    {
        stage_select_window();
    }
}

// ---- input (FUN_00409030) -----------------------------------------------------------------------------

void Game::key_down()
{
    if (in_game_state())
    {
        stop(Sfx::bgm);
        stop(Sfx::mugen);
        play(Sfx::open);
        if (mode_ == 1)
        {
            windows_[win_pause].state = opening;
        }
        else
        {
            windows_[win_stage_select].state = opening;
            stage_sel_ = stage_;
        }
        saved_cursor_ = cursor();
    }
    else if (state_ == State::ending)
    {
        stop(Sfx::ending);
        phase_ = 0;
        flag_ = 0;
        data_.free_mode_unlocked = true;
        state_ = State::ranking;
        save_data();
    }
}

void Game::left_button_down()
{
    if (pause_windows_closed() && phase_ != 0 && (state_ == State::clear || state_ == State::game_over))
    {
        bool load = true;
        if (state_ == State::clear)
        {
            phase_ = 0;
            if (++stage_ == stages::count)
            {
                if (mode_ == 1)
                {
                    state_ = State::ending;
                    load = false;
                }
                else
                {
                    stage_ = 0;
                }
            }
        }
        if (load)
        {
            phase_ = 0;
            state_ = State::intro;
            load_stage();
        }
    }
    left_down_ = true;
    click_pending_ = true;
}

void Game::left_button_up()
{
    left_down_ = false;
    click_pending_ = false;
}

void Game::right_button_down()
{
    if (balls_.size() < 500 && state_ == State::play && (infinite_ || stock_ > 0))
    {
        play(Sfx::ball);
        balls_.push_back({double(paddle_x_), paddle_y_ - 8.0 - ball_radius_, 0.8, -4.0, ball_radius_, next_ball_id_++});
        if (!infinite_)
        {
            --stock_;
        }
    }
}

// ---- stage load (FUN_004012d0) ------------------------------------------------------------------------

void Game::load_stage()
{
    balls_.clear();
    ball_radius_ = 8;
    stock_ = 10;
    big_ms_ = small_ms_ = reverse_ms_ = mugen_ms_ = 0;
    infinite_ = false;
    stage_ms_[stage_] = 0;
    remaining_ = 0;
    dying_.clear();
    items_.clear();
    paddle_units_ = 6;
    phase_ = 0;
    flag_ = 0;
    paddle_x_ = 256;
    paddle_y_ = 440.0;
    paddle_tilt_ = 0.0;
    paddle_vy_ = 0.0;
    gravity_ = 0.017;

    for (auto &block : blocks_)
    {
        block.state = block_empty;
        block.type = block_unknown_type;
        block.covered = 0;
    }

    const auto is_arrow = [](int type) { return type >= 12 && type <= 15; };
    const auto &layout = stage_data_[stage_];
    for (int row = 0; row < stages::rows; ++row)
    {
        for (int col = 0; col < stages::columns; ++col)
        {
            const int k = col + row * stages::columns;
            if (layout[k] == stages::empty)
            {
                continue;
            }
            auto &block = blocks_[k];
            block.type = layout[k];
            block.state = block_alive;
            ++remaining_;
            if (block.type == 5 || is_arrow(block.type))
            {
                --remaining_;
            }

            for (int f = 0; f < 32; ++f)
            {
                block.fx[f] = col * 32 + 18 + (f % 8) * 4;
                block.fy[f] = row * 16 + 18 + (f / 8) * 4;
                block.fvx[f] = 0.0;
                block.fvy[f] = 0.0;
                block.alive[f] = true;
            }

            if (is_arrow(block.type))
            {
                continue;
            }
            const auto solid = [&](int i) { return blocks_[i].state != block_empty && !is_arrow(blocks_[i].type); };
            if (col == 0)
            {
                block.covered |= 1;
            }
            else
            {
                if (solid(k - 1))
                {
                    block.covered |= 1;
                    blocks_[k - 1].covered |= 4;
                }
                if (col == stages::columns - 1)
                {
                    block.covered |= 4;
                }
            }
            if (row == 0)
            {
                block.covered |= 2;
            }
            else if (solid(k - stages::columns))
            {
                block.covered |= 2;
                blocks_[k - stages::columns].covered |= 8;
            }
        }
    }
}
