// BLOCK (KENTA, 2000), rebuilt on SDL3.
//
// The original ran full screen at 640x480 in 256 colours through DirectDraw. This runs the same game logic at a
// fixed 60 ticks per second and draws at whatever rate the display runs, moving sprites smoothly between ticks.
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <format>
#include <fstream>
#include <iterator>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "assets.hpp"
#include "audio.hpp"
#include "game.hpp"
#include "gfx.hpp"
#include "save.hpp"
#include "settings.hpp"
#include "stages.hpp"

namespace
{

constexpr Uint64 tick_ns = SDL_NS_PER_SECOND / Game::ticks_per_second;
constexpr int max_catch_up_ticks = 5;

// Keyboard and gamepad cursor speeds, in game pixels per second at 1x.
constexpr double key_start_speed = 360.0;
constexpr double key_max_speed = 960.0;
constexpr double key_acceleration = 1500.0; // per second, while a direction is held
constexpr double stick_max_speed = 960.0;
constexpr double stick_dead_zone = 0.15;
constexpr Sint16 trigger_threshold = 16000;

struct App
{
    SDL_Window *window{};
    SDL_Renderer *renderer{};
    Gfx gfx;
    Audio audio;
    settings::Settings settings;
    std::filesystem::path data_dir;
    std::unique_ptr<Game> game;

    Uint64 last_ns = 0;
    Uint64 accumulated_ns = 0;
    Uint64 tick_count = 0;
    Uint64 next_frame_ns = 0;
    Uint64 fps_window_start_ns = 0;
    int fps_frames = 0;

    settings::DisplayMode applied_display = settings::DisplayMode::windowed;
    settings::DisplayMode last_fullscreen = settings::DisplayMode::borderless;
    SDL_FRect picture{0, 0, Gfx::width, Gfx::height}; // where the 640x480 picture is, in output pixels

    std::vector<SDL_Gamepad *> gamepads;
    bool trigger_held = false;
    double key_held_seconds = 0.0;
};

SDL_AppResult fail(const char *what)
{
    const auto message = std::format("{}: {}", what, SDL_GetError());
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "BLOCK", message.c_str(), nullptr);
    return SDL_APP_FAILURE;
}

void capture_mouse(App &app, bool capture)
{
    // the original owned the whole screen and polled an unbounded cursor; relative mode recreates that
    SDL_SetWindowRelativeMouseMode(app.window, capture);
}

void apply_display_mode(App &app)
{
    using settings::DisplayMode;
    const auto mode = app.settings.display;
    if (mode == DisplayMode::windowed)
    {
        SDL_SetWindowFullscreen(app.window, false);
    }
    else
    {
        const SDL_DisplayMode *desktop = nullptr;
        if (mode == DisplayMode::fullscreen)
        {
            desktop = SDL_GetDesktopDisplayMode(SDL_GetDisplayForWindow(app.window));
        }
        // a null mode is SDL's borderless full screen at the desktop resolution
        SDL_SetWindowFullscreenMode(app.window, desktop);
        SDL_SetWindowFullscreen(app.window, true);
        app.last_fullscreen = mode;
    }
    SDL_SyncWindow(app.window);
    app.applied_display = mode;
}

void apply_settings(App &app)
{
    if (app.settings.display != app.applied_display)
    {
        apply_display_mode(app);
    }
    SDL_SetRenderVSync(app.renderer, app.settings.vsync ? 1 : 0);
}

// Puts the window back on the monitor, and at the place, it was last on.
void place_window(App &app)
{
    const auto &s = app.settings;
    int count = 0;
    SDL_DisplayID *displays = SDL_GetDisplays(&count);
    SDL_DisplayID target = 0;
    bool position_visible = false;
    for (int i = 0; i < count; ++i)
    {
        const char *name = SDL_GetDisplayName(displays[i]);
        if (!target && name && !s.monitor.empty() && s.monitor == name)
        {
            target = displays[i];
        }
        SDL_Rect bounds{};
        // the title bar's corner must be on a screen, or the window could not be dragged back
        if (s.has_window_position && SDL_GetDisplayUsableBounds(displays[i], &bounds) && s.window_x + 64 >= bounds.x &&
            s.window_x + 64 < bounds.x + bounds.w && s.window_y >= bounds.y && s.window_y + 16 < bounds.y + bounds.h)
        {
            position_visible = true;
        }
    }
    SDL_free(displays);

    if (position_visible)
    {
        SDL_SetWindowPosition(app.window, s.window_x, s.window_y);
    }
    else if (target)
    {
        SDL_SetWindowPosition(app.window, SDL_WINDOWPOS_CENTERED_DISPLAY(target), SDL_WINDOWPOS_CENTERED_DISPLAY(target));
    }
}

void save_settings(App &app)
{
    auto &s = app.settings;
    if (s.display == settings::DisplayMode::windowed &&
        !(SDL_GetWindowFlags(app.window) & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_MINIMIZED)))
    {
        SDL_GetWindowSize(app.window, &s.window_width, &s.window_height);
        s.has_window_position = SDL_GetWindowPosition(app.window, &s.window_x, &s.window_y);
    }
    if (const char *name = SDL_GetDisplayName(SDL_GetDisplayForWindow(app.window)))
    {
        s.monitor = name;
    }
    if (!settings::write(app.data_dir, s))
    {
        SDL_Log("could not save settings to %s", app.data_dir.string().c_str());
    }
}

bool is_fullscreen_toggle(const SDL_KeyboardEvent &key)
{
    return key.key == SDLK_F11 || (key.key == SDLK_RETURN && (key.mod & SDL_KMOD_ALT));
}

bool is_movement_key(SDL_Keycode key)
{
    switch (key)
    {
        case SDLK_LEFT: case SDLK_RIGHT: case SDLK_UP: case SDLK_DOWN:
        case SDLK_A: case SDLK_D: case SDLK_W: case SDLK_S:
        case SDLK_KP_4: case SDLK_KP_6: case SDLK_KP_8: case SDLK_KP_2:
            return true;
        default:
            return false;
    }
}

bool is_click_key(SDL_Keycode key)
{
    return key == SDLK_Z || key == SDLK_RETURN || key == SDLK_KP_ENTER;
}

bool is_launch_key(SDL_Keycode key)
{
    return key == SDLK_X || key == SDLK_SPACE;
}

// Converts relative mouse motion from window coordinates to game pixels.
double mouse_to_game(const App &app)
{
    int window_w = 0, pixels_w = 0, unused = 0;
    SDL_GetWindowSize(app.window, &window_w, &unused);
    SDL_GetWindowSizeInPixels(app.window, &pixels_w, &unused);
    const double pixel_ratio = window_w > 0 ? double(pixels_w) / window_w : 1.0;
    const double picture_scale = app.picture.w / Gfx::width;
    return pixel_ratio / picture_scale * settings::mouse_multiplier(app.settings.mouse_speed);
}

// -1..1 with a dead zone and a squared response, for fine control near the centre.
double stick(Sint16 raw)
{
    const double v = std::clamp(raw / 32767.0, -1.0, 1.0);
    const double magnitude = (std::fabs(v) - stick_dead_zone) / (1.0 - stick_dead_zone);
    return magnitude <= 0.0 ? 0.0 : std::copysign(magnitude * magnitude, v);
}

// Moves the cursor (and so the paddle) from held keys, the d-pad and the left stick.
void move_cursor_from_controls(App &app, double seconds)
{
    const bool *keys = SDL_GetKeyboardState(nullptr);
    double kx = 0.0, ky = 0.0;
    kx += keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_KP_6] ? 1.0 : 0.0;
    kx -= keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_KP_4] ? 1.0 : 0.0;
    ky += keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_KP_2] ? 1.0 : 0.0;
    ky -= keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_KP_8] ? 1.0 : 0.0;

    double sx = 0.0, sy = 0.0;
    for (SDL_Gamepad *pad : app.gamepads)
    {
        kx += SDL_GetGamepadButton(pad, SDL_GAMEPAD_BUTTON_DPAD_RIGHT) ? 1.0 : 0.0;
        kx -= SDL_GetGamepadButton(pad, SDL_GAMEPAD_BUTTON_DPAD_LEFT) ? 1.0 : 0.0;
        ky += SDL_GetGamepadButton(pad, SDL_GAMEPAD_BUTTON_DPAD_DOWN) ? 1.0 : 0.0;
        ky -= SDL_GetGamepadButton(pad, SDL_GAMEPAD_BUTTON_DPAD_UP) ? 1.0 : 0.0;
        sx += stick(SDL_GetGamepadAxis(pad, SDL_GAMEPAD_AXIS_LEFTX));
        sy += stick(SDL_GetGamepadAxis(pad, SDL_GAMEPAD_AXIS_LEFTY));
    }
    kx = std::clamp(kx, -1.0, 1.0);
    ky = std::clamp(ky, -1.0, 1.0);

    // digital directions start slow for small steps and speed up while held
    if (kx != 0.0 || ky != 0.0)
    {
        app.key_held_seconds += seconds;
    }
    else
    {
        app.key_held_seconds = 0.0;
    }
    const double key_speed = std::min(key_max_speed, key_start_speed + key_acceleration * app.key_held_seconds);
    const double scale = settings::mouse_multiplier(app.settings.pad_speed) * seconds;
    const double dx = (kx * key_speed + std::clamp(sx, -1.0, 1.0) * stick_max_speed) * scale;
    const double dy = (ky * key_speed + std::clamp(sy, -1.0, 1.0) * stick_max_speed) * scale;
    if (dx != 0.0 || dy != 0.0)
    {
        app.game->mouse_moved(dx, dy);
    }

    // the right trigger launches, like a button
    bool trigger = false;
    for (SDL_Gamepad *pad : app.gamepads)
    {
        trigger |= SDL_GetGamepadAxis(pad, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER) > trigger_threshold;
    }
    if (trigger && !app.trigger_held)
    {
        app.game->right_button_down();
    }
    app.trigger_held = trigger;
}

// The built-in stages first, then custom packs from stages/ next to the executable and in the save folder.
std::vector<stages::Pack> load_packs(const App &app, std::string &errors)
{
    std::vector<stages::Pack> packs;
    auto builtin = stages::parse(assets::as_text(assets::stages_txt()), std::string{stages::original_id}, "ORIGINAL");
    if (!builtin)
    {
        errors = "bad built-in stage data: " + builtin.error();
        return {};
    }
    packs.push_back(std::move(*builtin));

    std::vector<std::string> problems;
    const std::filesystem::path base{SDL_GetBasePath()};
    auto dirs = std::vector{base / "stages"};
    std::error_code ec;
    if (!std::filesystem::equivalent(base, app.data_dir, ec))
    {
        dirs.push_back(app.data_dir / "stages");
    }
    for (const auto &dir : dirs)
    {
        for (auto &pack : stages::load_directory(dir, problems))
        {
            if (std::ranges::none_of(packs, [&](const auto &p) { return p.id == pack.id; }))
            {
                packs.push_back(std::move(pack));
            }
        }
    }

    // 1.30 and 1.40 read a stages.txt next to the executable in place of the built-in stages
    if (std::ifstream file{base / "stages.txt", std::ios::binary})
    {
        const std::string text{std::istreambuf_iterator<char>{file}, {}};
        if (auto pack = stages::parse(text, "stages", "STAGES.TXT"))
        {
            packs.push_back(std::move(*pack));
        }
        else
        {
            problems.push_back("stages.txt: " + pack.error());
        }
    }

    for (const auto &problem : problems)
    {
        errors += problem + "\n";
    }
    return packs;
}

}

SDL_AppResult SDL_AppInit(void **appstate, int, char **)
{
    SDL_SetAppMetadata("BLOCK", "1.50", "jp.kenta.block");
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD))
    {
        return fail("SDL_Init failed");
    }

    auto *app = new App{};
    *appstate = app;
    app->data_dir = save::directory();
    app->settings = settings::load(app->data_dir);

    if (!SDL_CreateWindowAndRenderer("BLOCK", app->settings.window_width, app->settings.window_height,
                                     SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_HIDDEN,
                                     &app->window, &app->renderer))
    {
        return fail("could not create window");
    }
    SDL_SetWindowMinimumSize(app->window, Gfx::width, Gfx::height);
    place_window(*app);

#ifndef _WIN32
    // Windows takes the icon from the executable's resources
    const auto icon_data = assets::icon_bmp();
    if (SDL_Surface *icon = SDL_LoadBMP_IO(SDL_IOFromConstMem(icon_data.data(), icon_data.size()), true))
    {
        SDL_SetWindowIcon(app->window, icon);
        SDL_DestroySurface(icon);
    }
#endif

    if (!app->gfx.init(app->renderer, assets::sprites_bmp()))
    {
        return fail("could not load sprite sheet");
    }

    std::string pack_errors;
    auto packs = load_packs(*app, pack_errors);
    if (packs.empty())
    {
        SDL_SetError("%s", pack_errors.c_str());
        return fail("could not load the stages");
    }
    if (!pack_errors.empty())
    {
        // tell stage authors what is wrong, then carry on without those packs
        const auto message = "These stage files were skipped:\n\n" + pack_errors;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "BLOCK", message.c_str(), nullptr);
    }

    // built-in sounds; a wav or ogg in wave/ next to the executable replaces one
    app->audio.init(std::filesystem::path{SDL_GetBasePath()} / "wave");

    app->game = std::make_unique<Game>(app->gfx, app->audio, app->settings, std::move(packs), app->data_dir);
    SDL_ShowWindow(app->window);
    apply_display_mode(*app);
    apply_settings(*app);
    capture_mouse(*app, true);
    app->last_ns = app->next_frame_ns = app->fps_window_start_ns = SDL_GetTicksNS();
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    auto &app = *static_cast<App *>(appstate);
    auto &game = *app.game;

    switch (event->type)
    {
        case SDL_EVENT_QUIT:
            game.save_data();
            save_settings(app);
            return SDL_APP_SUCCESS;

        case SDL_EVENT_KEY_DOWN:
        {
            const auto key = event->key.key;
            if (key == SDLK_ESCAPE)
            {
                // pauses in play like any key; quits only from the title screen
                if (!event->key.repeat && game.escape_key())
                {
                    game.save_data();
                    save_settings(app);
                    return SDL_APP_SUCCESS;
                }
                break;
            }
            if (is_fullscreen_toggle(event->key))
            {
                app.settings.display = app.settings.display == settings::DisplayMode::windowed
                                           ? app.last_fullscreen
                                           : settings::DisplayMode::windowed;
                apply_settings(app);
                save_settings(app);
                break;
            }
            if (event->key.repeat || is_movement_key(key))
            {
                break; // movement keys are read every frame
            }
            if (is_click_key(key))
            {
                game.left_button_down();
                game.action_key_down();
            }
            else if (is_launch_key(key))
            {
                game.right_button_down();
                game.action_key_down();
            }
            else
            {
                game.key_down(); // like the original, any other key pauses (P is the one the help names)
            }
            break;
        }

        case SDL_EVENT_KEY_UP:
            if (is_click_key(event->key.key))
            {
                game.left_button_up();
            }
            break;

        case SDL_EVENT_MOUSE_MOTION:
        {
            const double scale = mouse_to_game(app);
            game.mouse_moved(event->motion.xrel * scale, event->motion.yrel * scale);
            break;
        }

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (event->button.button == SDL_BUTTON_LEFT)
            {
                game.left_button_down();
            }
            else if (event->button.button == SDL_BUTTON_RIGHT)
            {
                game.right_button_down();
            }
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            if (event->button.button == SDL_BUTTON_LEFT)
            {
                game.left_button_up();
            }
            break;

        case SDL_EVENT_GAMEPAD_ADDED:
            if (SDL_Gamepad *pad = SDL_OpenGamepad(event->gdevice.which))
            {
                app.gamepads.push_back(pad);
            }
            break;

        case SDL_EVENT_GAMEPAD_REMOVED:
            std::erase_if(app.gamepads, [&](SDL_Gamepad *pad) {
                if (SDL_GetGamepadID(pad) != event->gdevice.which)
                {
                    return false;
                }
                SDL_CloseGamepad(pad);
                return true;
            });
            break;

        case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
            switch (event->gbutton.button)
            {
                case SDL_GAMEPAD_BUTTON_SOUTH:
                    game.left_button_down();
                    game.action_key_down();
                    break;
                case SDL_GAMEPAD_BUTTON_EAST:
                case SDL_GAMEPAD_BUTTON_WEST:
                case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER:
                    game.right_button_down();
                    game.action_key_down();
                    break;
                case SDL_GAMEPAD_BUTTON_START:
                case SDL_GAMEPAD_BUTTON_BACK:
                    game.escape_key(); // like Esc, but a gamepad never quits the game
                    break;
                default:
                    break;
            }
            break;

        case SDL_EVENT_GAMEPAD_BUTTON_UP:
            if (event->gbutton.button == SDL_GAMEPAD_BUTTON_SOUTH)
            {
                game.left_button_up();
            }
            break;

        case SDL_EVENT_WINDOW_FOCUS_GAINED:
            capture_mouse(app, true);
            break;

        case SDL_EVENT_WINDOW_FOCUS_LOST:
            capture_mouse(app, false);
            game.focus_lost();
            break;

        default:
            break;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    auto &app = *static_cast<App *>(appstate);

    // fixed 60 Hz logic
    const Uint64 now = SDL_GetTicksNS();
    const Uint64 elapsed = now - app.last_ns;
    app.last_ns = now;
    if (SDL_GetWindowFlags(app.window) & SDL_WINDOW_INPUT_FOCUS)
    {
        move_cursor_from_controls(app, std::min(double(elapsed) / SDL_NS_PER_SECOND, 0.1));
    }
    app.accumulated_ns += elapsed;
    if (app.accumulated_ns > tick_ns * max_catch_up_ticks)
    {
        app.accumulated_ns = tick_ns * max_catch_up_ticks;
    }
    while (app.accumulated_ns >= tick_ns)
    {
        app.accumulated_ns -= tick_ns;
        // integer milliseconds per tick (16 or 17) summing to exactly 1000 per second, as the original's
        // GetTickCount-based timers expect
        const auto ms = [](Uint64 tick) { return static_cast<int>(tick * 1000 / Game::ticks_per_second); };
        ++app.tick_count;
        app.game->tick(ms(app.tick_count) - ms(app.tick_count - 1));
    }
    if (app.game->take_settings_changed())
    {
        apply_settings(app);
        save_settings(app);
    }

    // draw at the display rate, between the last two ticks
    const bool smooth = app.settings.smooth_motion;
    const double alpha = smooth ? double(app.accumulated_ns) / double(tick_ns) : 1.0;
    app.gfx.render(alpha, smooth ? app.game->live_offsets() : LiveOffsets{});
    app.picture = app.gfx.compose(app.settings.scaling, app.settings.filter, app.settings.side_frame);
    app.audio.update();
    SDL_RenderPresent(app.renderer);

    ++app.fps_frames;
    const Uint64 after = SDL_GetTicksNS();
    if (after - app.fps_window_start_ns >= SDL_NS_PER_SECOND)
    {
        app.game->set_display_fps(
            static_cast<int>(app.fps_frames * SDL_NS_PER_SECOND / (after - app.fps_window_start_ns)));
        app.fps_frames = 0;
        app.fps_window_start_ns = after;
    }

    // optional frame cap, e.g. a few fps under a variable-refresh display's maximum
    if (app.settings.fps_limit > 0)
    {
        const Uint64 frame_ns = SDL_NS_PER_SECOND / static_cast<Uint64>(app.settings.fps_limit);
        app.next_frame_ns += frame_ns;
        if (app.next_frame_ns > after)
        {
            SDL_DelayPrecise(app.next_frame_ns - after);
        }
        else if (after - app.next_frame_ns > frame_ns)
        {
            app.next_frame_ns = after; // fell behind: don't try to catch up
        }
    }
    else
    {
        app.next_frame_ns = after;
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult)
{
    auto *app = static_cast<App *>(appstate);
    if (app)
    {
        app->game.reset();
        for (SDL_Gamepad *pad : app->gamepads)
        {
            SDL_CloseGamepad(pad);
        }
        app->audio.shutdown();
        app->gfx.shutdown();
        delete app;
    }
}
