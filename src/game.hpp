#pragma once

#include <array>
#include <cstdint>
#include <filesystem>
#include <optional>
#include <string>
#include <vector>

#include "audio.hpp"
#include "gfx.hpp"
#include "replay.hpp"
#include "save.hpp"
#include "settings.hpp"
#include "stages.hpp"
#include "voxels.hpp"

// The game, rebuilt from block130.exe. Function and variable comments name the original routine or global
// (see re/NOTES.md); the logic, constants and quirks follow the original unless a comment says otherwise.
class Game
{
  public:
    static constexpr int screen_width = 640;
    static constexpr int screen_height = 480;
    static constexpr int ticks_per_second = 60;
    static constexpr const char *version_short = "Ver.1.50";
    static constexpr const char *version_long = "Version 1.50";

    // packs[0] must be the built-in stages.
    Game(Gfx &gfx, Audio &audio, settings::Settings &settings, std::vector<stages::Pack> packs,
         std::filesystem::path save_dir);

    // One frame of the original main loop (FUN_00407fa0). Records the frame's sprites into gfx.
    void tick(int dt_ms);

    // Input, as routed by the original window procedure (FUN_00409030).
    void key_down();
    void left_button_down();
    // Rebuild: Esc pauses in play, closes the top window or goes back a screen elsewhere, and returns true when
    // it should quit (on the title screen with nothing open).
    bool escape_key();

    // Rebuild: a key that has its own job (moving the cursor, clicking, launching) only does the "any key"
    // part outside the game: leaving the ending.
    void action_key_down();
    void left_button_up();
    void right_button_down();
    void mouse_moved(double dx, double dy);

    // Rebuild: the window lost focus, so pause like a key press would.
    void focus_lost();

    // Writes block.sav (the original saved only on exit).
    void save_data();

    // True while a replay is playing; real input is ignored then, except to stop it.
    bool replay_playing() const
    {
        return playback_.has_value();
    }

    // True once after the options windows changed a display or audio setting.
    bool take_settings_changed();

    // Where the paddle and cursor should be drawn now, relative to the last tick, for smooth motion.
    LiveOffsets live_offsets() const;

    // Frames per second actually shown, for the HUD.
    void set_display_fps(int fps)
    {
        display_fps_ = fps;
    }

  private:
    friend struct GameTest; // tests/tests.cpp

    // ---- types -------------------------------------------------------------------------------------
    enum class State
    {
        play = 0x1,
        intro = 0x2,
        clear = 0x4,
        game_over = 0x8,
        ending = 0x10,
        boot = 0x20,
        title = 0x40,
        name_entry = 0x80,
        ranking = 0x100,
    };

    enum Win
    {
        win_options,
        win_volume,
        win_pause,
        win_reset,
        win_broken,
        win_stage_select,
        win_mode_select,
        win_message,
        win_screen,   // rebuild
        win_controls, // rebuild
        win_count
    };

    // window record states
    static constexpr int closed = 1;
    static constexpr int opening = 2;
    static constexpr int closing = 4;

    struct Window
    {
        int x, y, w, h; // 8 px, 16 px, 8 px, 16 px units
        int state = closed;
        double half_w = 8.0;
        double half_h = 8.0;
    };

    struct Ball
    {
        double x, y, vx, vy;
        int r;
        std::uint32_t id; // rebuild: identifies the ball for smooth motion
    };

    // block states
    static constexpr int block_empty = 1;
    static constexpr int block_alive = 2;
    static constexpr int block_breaking = 4;
    static constexpr int block_spawning = 8;
    static constexpr int block_unknown_type = 9999;

    struct Block
    {
        int state = block_empty;
        int type = block_unknown_type;
        unsigned covered = 0; // sides covered by a neighbour or wall: 1 left, 2 top, 4 right, 8 bottom
        std::array<bool, 32> alive{};
        std::array<double, 32> fx{}, fy{}, fvx{}, fvy{};
    };

    // item states
    static constexpr int item_falling = 1;
    static constexpr int item_to_hud = 2;
    static constexpr int item_in_hud = 4;
    static constexpr int item_gone = 8;

    struct Item
    {
        double x, y, vx, vy;
        int type;
        int state;
    };

    struct Point
    {
        int x, y;
    };

    // ---- core (game.cpp) ---------------------------------------------------------------------------
    void run_tick(int dt_ms);
    void load_stage();
    bool launch_ball();
    const stages::Pack &pack() const
    {
        return packs_[pack_];
    }
    int stage_count() const
    {
        return static_cast<int>(pack().stages.size());
    }
    save::PackRecords &records()
    {
        return data_.records(pack().id);
    }
    bool free_mode_available() const;

    // ---- replays and splits (game.cpp) -------------------------------------------------------------
    int next_play_tick_ms();
    void record_or_replay_tick();
    void finish_recording(int rank);
    void start_playback(int stage);
    void end_playback();
    std::optional<int> split_delta(int stage) const;
    void reset_windows();
    int rand();
    Point cursor() const;
    void set_cursor(int x, int y);
    bool take_click();
    bool in_game_state() const;
    bool pause_windows_closed() const;
    void play(Sfx id, bool loop = false);
    void stop(Sfx id);
    void resume_bgm();

    // ---- simulation (physics.cpp) ------------------------------------------------------------------
    void physics_step();
    void update_paddle();
    bool ball_overlaps_block(int k, double x, double y, int r) const;
    bool ball_overlaps_any_block(double x, double y, int r) const;
    int hit_octant(int k, double x, double y, double vx, double vy, int r);
    void destroy_block(int k, double x, double y, double vx, double vy);
    void update_items_and_debris();

    // ---- rendering and screens (screens.cpp) -------------------------------------------------------
    void render_playfield();
    void draw_time_digits(int ms, int row, int m_y);
    void screen_boot(int dt_ms);
    void screen_title();
    void screen_intro();
    void screen_clear();
    void screen_game_over();
    void screen_ending();
    void screen_name_entry();
    void screen_ranking();
    void draw_stage_preview(int stage, int x, int y);
    void draw_stage_thumbnail(int stage, int x, int y);

    // mini block icon in the stage previews, by block type; -1 for none
    static constexpr int preview_icon(int type)
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

    // ---- pop-up windows (windows.cpp) --------------------------------------------------------------
    void window_frame(Win id);
    bool window_open_step(Win id);
    bool window_close_step(Win id);
    void window_reset(Win id);
    bool window_row_hit(Win id, int row, Point p) const;
    void window_text(Win id, int row, std::string_view s, int colour);
    void options_window();
    void volume_window();
    void pause_window();
    void reset_window();
    void broken_window();
    void stage_select_window();
    void mode_select_window();
    void message_window(std::string_view message);
    void screen_window();
    void controls_window();
    bool volume_slider(Win id, int row, double &value, Point p);
    void apply_volumes();
    void pause_window_actions(Win id, int try_again_row, int end_game_row, int cancel_row, Point p, bool active);
    void try_again(Win id);
    void end_game(Win id);
    void cancel_pause(Win id);
    bool close_top_title_window();

    // stage select grid (rebuild)
    static constexpr int select_per_page = 9;
    static constexpr int select_column_step = 120;
    static constexpr int thumbnail_width = 6 * stages::columns;  // 90
    static constexpr int thumbnail_height = 3 * stages::rows;    // 78

    // ---- collaborators -------------------------------------------------------------------------------
    Gfx &gfx_;
    Audio &audio_;
    std::vector<stages::Pack> packs_;
    std::size_t pack_ = 0;
    std::filesystem::path save_dir_;
    save::Data data_;
    settings::Settings &settings_;
    bool settings_changed_ = false;
    int display_fps_ = ticks_per_second;
    Point drawn_cursor_{};          // where the last tick drew the cursor
    int drawn_paddle_x_ = 256;      // where the last tick drew the paddle

    // ---- global state (original globals in comments) -----------------------------------------------
    State state_ = State::boot;     // DAT_00421308
    int phase_ = 0;                 // DAT_004baf20
    int phase_ms_ = 0;              // DAT_004baf24
    int flag_ = 0;                  // DAT_00428f70: intro slide state / clear-screen blink
    int mode_ = 1;                  // DAT_0049d284: 1 time trial, 2 free
    int stage_ = 0;                 // DAT_00425268
    std::array<int, stages::max_count> stage_ms_{}; // DAT_004251a0
    int total_ms_ = 0;              // DAT_0041d47c
    std::array<int, stages::max_count> stage_rank_this_run_{}; // DAT_004b8ef4
    int total_rank_this_run_ = 10;  // DAT_0049d298
    int play_ticks_ = 0;            // rebuild: physics ticks since the stage loaded

    // rebuild: replays and split times
    replay::Replay recording_;
    bool recording_active_ = false;
    int pending_launches_ = 0;      // balls launched since the last physics tick
    std::optional<replay::Replay> playback_;
    std::size_t playback_tick_ = 0;
    bool playback_matched_ = false; // the playback cleared the stage at the recorded time
    std::optional<int> ranking_return_stage_;
    std::array<int, stages::max_count> run_splits_{}; // total time at each stage clear in this run
    std::array<int, stages::max_count> run_pb_{};     // the best run's splits when this run started

    double mouse_x_ = 320.0, mouse_y_ = 240.0; // GetCursorPos
    bool left_down_ = false;        // DAT_004290d0
    bool click_pending_ = false;    // rebuild: menus act once per press
    Point saved_cursor_{};          // DAT_004a1620
    unsigned rand_seed_ = 1;        // CRT rand state

    std::array<Window, win_count> windows_{};
    int stage_sel_ = 0;             // DAT_004baf28
    int select_page_ = 0;           // rebuild: the stage select window's page
    int ranking_view_ = 1;          // DAT_0049d280: 1 stage times, 0 total

    // play
    std::array<Block, stages::columns * stages::rows> blocks_{};
    int remaining_ = 0;             // DAT_0041d478
    std::vector<Ball> balls_;       // DAT_00498448, max 500
    std::uint32_t next_ball_id_ = 0;
    int ball_radius_ = 8;           // DAT_0041ce58
    int stock_ = 10;                // DAT_004b8fc8
    bool infinite_ = false;         // DAT_0049f6a0
    int big_ms_ = 0;                // DAT_00498440
    int small_ms_ = 0;              // DAT_004baf2c
    int reverse_ms_ = 0;            // DAT_004b8ee8
    int mugen_ms_ = 0;              // DAT_004b8fcc
    double gravity_ = 0.017;        // DAT_00498438
    std::vector<Item> items_;       // DAT_00425270
    std::vector<int> dying_;        // DAT_0041ce60
    std::size_t spawn_rotor_ = 0;   // rebuild: round-robin start for ball-spawning blocks
    int paddle_units_ = 6;          // DAT_004a15ec
    int paddle_x_ = 256;            // DAT_0049d288
    double paddle_y_ = 440.0;       // DAT_0049d290
    double paddle_vy_ = 0.0;        // DAT_004290c8
    double paddle_tilt_ = 0.0;      // DAT_004290c0
    int hit_seg_ = 0;               // persistent octant local in FUN_004029f0

    // 3D text and screen animation
    VoxelText vox_;
    double cam_z_ = 0.0;            // DAT_0041ce48
    double angle_ = 0.0;            // DAT_004b8fd0 (degrees)
    double ang_vel_ = 0.0;          // DAT_004b8fc0
    double slide_x_ = 0.0;          // DAT_0041ce38
    double slide_v_ = 0.0;          // DAT_0049d270
    int end_scroll_ms_ = 0;         // DAT_004baf1c
    int end_scroll_px_ = 0;         // DAT_004b8ef0
    int end_top_line_ = 0;          // DAT_0049d268
    int end_word_ = 0;              // DAT_0049f6a8
};
