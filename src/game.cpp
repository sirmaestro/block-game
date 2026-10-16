#include "game.hpp"

#include <SDL3/SDL.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <utility>

Game::Game(Gfx &gfx, Audio &audio, settings::Settings &settings, std::vector<stages::Pack> packs,
           std::filesystem::path save_dir)
    : gfx_(gfx), audio_(audio), packs_(std::move(packs)), save_dir_(std::move(save_dir)),
      data_(save::load(save_dir_)), settings_(settings)
{
    for (std::size_t i = 0; i < packs_.size(); ++i)
    {
        if (packs_[i].id == settings_.stage_pack)
        {
            pack_ = i;
        }
    }
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
    audio_.set_volumes(settings_.master_volume, settings_.music_volume, settings_.sound_volume);
}

bool Game::free_mode_available() const
{
    // custom stage packs can be played in any order from the start
    return data_.free_mode_unlocked || pack().id != stages::original_id;
}

void Game::focus_lost()
{
    if (playback_)
    {
        return; // a replay keeps playing in the background
    }
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
    if (state_ == State::play && pause_windows_closed() && !playback_)
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
    if (playback_)
    {
        return;
    }
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
            if (windows_[win_controls].state != closed)
            {
                controls_window();
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
                    // the original's 68 lines: headings, one per stage, a blank and the total
                    if (++end_top_line_ > stage_count() + 17)
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
                record_or_replay_tick();
                if (state_ != State::play)
                {
                    return; // the replay ran out
                }
                // Rebuild: the stage's own tick count sets the timers' 16/17 ms steps, so a replay sees the
                // same steps however the stage was paused.
                const int play_ms = next_play_tick_ms();
                for (int *timer : {&big_ms_, &small_ms_, &reverse_ms_, &mugen_ms_})
                {
                    if (*timer > 0)
                    {
                        *timer -= play_ms;
                    }
                }
                stage_ms_[stage_] += play_ms;
                total_ms_ += play_ms;
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
    if (playback_)
    {
        end_playback();
        return;
    }
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
            select_page_ = stage_ / select_per_page;
        }
        saved_cursor_ = cursor();
    }
    else
    {
        action_key_down();
    }
}

bool Game::escape_key()
{
    if (playback_)
    {
        end_playback();
        return false;
    }
    if (in_game_state())
    {
        // Esc toggles the pause / stage select window
        for (const Win id : {win_pause, win_stage_select})
        {
            const auto &win = windows_[id];
            if (win.state == opening && win.half_h == win.h * 8 - 8)
            {
                cancel_pause(id); // fully open: same as CANCEL
                return false;
            }
            if (win.state != closed)
            {
                return false; // still opening or closing
            }
        }
        key_down();
        return false;
    }
    switch (state_)
    {
        case State::title:
            return !close_top_title_window();
        case State::ending:
            action_key_down();
            return false;
        case State::ranking:
        case State::name_entry:
            // back to the title, as EXIT does
            stop(Sfx::ranking);
            stop(Sfx::nameentry);
            play(Sfx::change);
            phase_ = 0;
            flag_ = 0;
            stage_sel_ = 0;
            ranking_view_ = 0;
            state_ = State::title;
            return false;
        default:
            return false;
    }
}

// Closes the title screen's top-most open window, as its CLOSE / CANCEL would. False if none was open.
bool Game::close_top_title_window()
{
    // children before their parents
    constexpr Win order[] = {win_message, win_volume, win_screen, win_controls, win_reset, win_broken,
                             win_mode_select, win_options};
    for (const Win id : order)
    {
        auto &win = windows_[id];
        if (win.state == closed)
        {
            continue;
        }
        if (win.state == opening)
        {
            play(Sfx::close);
            win.state = closing;
            if (id == win_volume || id == win_screen || id == win_controls || id == win_broken)
            {
                settings_changed_ = true;
            }
        }
        return true; // a closing window counts too: wait for it
    }
    return false;
}

void Game::action_key_down()
{
    if (state_ == State::ending)
    {
        stop(Sfx::ending);
        phase_ = 0;
        flag_ = 0;
        if (pack().id == stages::original_id)
        {
            data_.free_mode_unlocked = true;
        }
        state_ = State::ranking;
        save_data();
    }
}

void Game::left_button_down()
{
    if (playback_)
    {
        end_playback();
        return;
    }
    if (pause_windows_closed() && phase_ != 0 && (state_ == State::clear || state_ == State::game_over))
    {
        bool load = true;
        if (state_ == State::clear)
        {
            phase_ = 0;
            if (++stage_ == stage_count())
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
    if (!playback_ && launch_ball() && recording_active_)
    {
        ++pending_launches_; // like the original, this works while paused too
    }
}

bool Game::launch_ball()
{
    if (balls_.size() < 500 && state_ == State::play && (infinite_ || stock_ > 0))
    {
        play(Sfx::ball);
        balls_.push_back({double(paddle_x_), paddle_y_ - 8.0 - ball_radius_, 0.8, -4.0, ball_radius_, next_ball_id_++});
        if (!infinite_)
        {
            --stock_;
        }
        return true;
    }
    return false;
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
    spawn_rotor_ = 0;
    play_ticks_ = 0;
    pending_launches_ = 0;

    // start recording a replay (not while watching one)
    recording_active_ = !playback_;
    recording_ = {};
    if (recording_active_)
    {
        recording_.pack_id = pack().id;
        recording_.stage = stage_;
        recording_.stage_hash = stages::hash(pack().stages[stage_]);
        recording_.seed = rand_seed_;
        recording_.hit_seg = hit_seg_;
        recording_.ticks.reserve(60 * 120);
    }

    for (auto &block : blocks_)
    {
        block.state = block_empty;
        block.type = block_unknown_type;
        block.covered = 0;
    }

    const auto is_arrow = [](int type) { return type >= 12 && type <= 15; };
    const auto &layout = pack().stages[stage_];
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

// ---- replays and split times ----------------------------------------------------------------------------

int Game::next_play_tick_ms()
{
    const auto ms = [](int tick) { return static_cast<int>(static_cast<long long>(tick) * 1000 / ticks_per_second); };
    ++play_ticks_;
    return ms(play_ticks_) - ms(play_ticks_ - 1);
}

// Called before each physics tick: feed the replay's input, or record the player's.
void Game::record_or_replay_tick()
{
    if (playback_)
    {
        if (playback_tick_ >= playback_->ticks.size())
        {
            SDL_Log("replay ran out of input on stage %d", stage_ + 1);
            end_playback();
            return;
        }
        const auto &t = playback_->ticks[playback_tick_++];
        mouse_x_ = t.cursor_x;
        left_down_ = t.left_down;
        for (int i = 0; i < t.launches; ++i)
        {
            launch_ball();
        }
        return;
    }
    if (!recording_active_)
    {
        return;
    }
    if (recording_.ticks.size() >= 60u * 60 * 100)
    {
        recording_active_ = false; // longer than the timer can show
        return;
    }
    recording_.ticks.push_back({static_cast<std::int16_t>(cursor().x), left_down_,
                                static_cast<std::uint8_t>(std::min(pending_launches_, 255))});
    pending_launches_ = 0;
}

// At a stage clear: keep the replay if the time is the stage's new best.
void Game::finish_recording(int rank)
{
    if (!recording_active_)
    {
        return;
    }
    recording_active_ = false;
    if (rank != 0)
    {
        return;
    }
    const auto &best = records().stage_ranking[stage_][0];
    recording_.time_ms = stage_ms_[stage_];
    recording_.name = best.name;
    recording_.year = best.year;
    recording_.month = best.month;
    recording_.day = best.day;
    recording_.hour = best.hour;
    recording_.minute = best.minute;
    const auto path = replay::best_path(save_dir_, pack().id, stage_);
    if (!replay::write(path, recording_))
    {
        SDL_Log("could not save replay %s", path.string().c_str());
    }
}

void Game::start_playback(int stage)
{
    auto r = replay::read(replay::best_path(save_dir_, pack().id, stage));
    if (!r || r->pack_id != pack().id || r->stage != stage || r->stage_hash != stages::hash(pack().stages[stage]))
    {
        play(Sfx::error); // missing, damaged, or recorded on a different version of the stage
        return;
    }
    stop(Sfx::ranking);
    play(Sfx::change);
    playback_ = std::move(*r);
    playback_tick_ = 0;
    playback_matched_ = false;
    stage_ = stage;
    load_stage();
    rand_seed_ = playback_->seed;
    hit_seg_ = playback_->hit_seg;
    left_down_ = false;
    click_pending_ = false;
    state_ = State::intro;
}

void Game::end_playback()
{
    for (const auto id : {Sfx::bgm, Sfx::mugen, Sfx::clear, Sfx::gameover})
    {
        stop(id);
    }
    playback_.reset();
    reset_windows();
    left_down_ = false;
    click_pending_ = false;
    ranking_return_stage_ = stage_;
    phase_ = 0;
    flag_ = 0;
    state_ = State::ranking;
}

// How far ahead (negative) or behind the best time-trial run this run was when it cleared `stage`.
std::optional<int> Game::split_delta(int stage) const
{
    if (mode_ != 1 || playback_ || stage < 0 || stage >= stage_count() || run_pb_[stage] <= 0 ||
        run_splits_[stage] <= 0)
    {
        return std::nullopt;
    }
    return run_splits_[stage] - run_pb_[stage];
}
