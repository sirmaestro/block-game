#pragma once

#include <array>
#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

#include "audio.hpp"
#include "gfx.hpp"
#include "save.hpp"
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

    Game(Gfx &gfx, Audio &audio, std::vector<stages::Stage> stage_data, std::filesystem::path save_dir);

    // One frame of the original main loop (FUN_00407fa0). Records the frame's sprites into gfx.
    void tick(int dt_ms);

    // Input, as routed by the original window procedure (FUN_00409030).
    void key_down();
    void left_button_down();
    void left_button_up();
    void right_button_down();
    void mouse_moved(double dx, double dy);

    // Writes block130.sys / block130.dat (the original saved only on exit).
    void save_data();

  private:
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
    void load_stage();
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
    void pause_window_actions(Win id, int try_again_row, int end_game_row, int cancel_row, Point p, bool active);

    // ---- collaborators -------------------------------------------------------------------------------
    Gfx &gfx_;
    Audio &audio_;
    std::vector<stages::Stage> stage_data_;
    std::filesystem::path save_dir_;
    save::Data data_;

    // ---- global state (original globals in comments) -----------------------------------------------
    State state_ = State::boot;     // DAT_00421308
    int phase_ = 0;                 // DAT_004baf20
    int phase_ms_ = 0;              // DAT_004baf24
    int flag_ = 0;                  // DAT_00428f70: intro slide state / clear-screen blink
    int mode_ = 1;                  // DAT_0049d284: 1 time trial, 2 free
    int stage_ = 0;                 // DAT_00425268
    std::array<int, 50> stage_ms_{}; // DAT_004251a0
    int total_ms_ = 0;              // DAT_0041d47c
    std::array<int, 50> stage_rank_this_run_{}; // DAT_004b8ef4
    int total_rank_this_run_ = 10;  // DAT_0049d298

    double mouse_x_ = 320.0, mouse_y_ = 240.0; // GetCursorPos
    bool left_down_ = false;        // DAT_004290d0
    bool click_pending_ = false;    // rebuild: menus act once per press
    Point saved_cursor_{};          // DAT_004a1620
    unsigned rand_seed_ = 1;        // CRT rand state

    std::array<Window, win_count> windows_{};
    int stage_sel_ = 0;             // DAT_004baf28
    int ranking_view_ = 1;          // DAT_0049d280: 1 stage times, 0 total

    // play
    std::array<Block, stages::columns * stages::rows> blocks_{};
    int remaining_ = 0;             // DAT_0041d478
    std::vector<Ball> balls_;       // DAT_00498448, max 500
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
