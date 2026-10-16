// BLOCK (KENTA, 2000), rebuilt on SDL3.
//
// The original ran full screen at 640x480 in 256 colours through DirectDraw. This runs the same game logic at a
// fixed 60 ticks per second and draws at whatever rate the display runs, moving sprites smoothly between ticks.
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <filesystem>
#include <format>
#include <fstream>
#include <iterator>
#include <memory>
#include <string>
#include <utility>

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

void save_settings(App &app)
{
    if (app.settings.display == settings::DisplayMode::windowed &&
        !(SDL_GetWindowFlags(app.window) & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED)))
    {
        SDL_GetWindowSize(app.window, &app.settings.window_width, &app.settings.window_height);
    }
    if (!settings::write(app.data_dir, app.settings))
    {
        SDL_Log("could not save settings to %s", app.data_dir.string().c_str());
    }
}

bool is_fullscreen_toggle(const SDL_KeyboardEvent &key)
{
    return key.key == SDLK_F11 || (key.key == SDLK_RETURN && (key.mod & SDL_KMOD_ALT));
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

}

SDL_AppResult SDL_AppInit(void **appstate, int, char **)
{
    SDL_SetAppMetadata("BLOCK", "1.40", "jp.kenta.block");
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        return fail("SDL_Init failed");
    }

    auto *app = new App{};
    *appstate = app;
    app->data_dir = save::directory();
    app->settings = settings::load(app->data_dir);

    if (!SDL_CreateWindowAndRenderer("BLOCK", app->settings.window_width, app->settings.window_height,
                                     SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY, &app->window,
                                     &app->renderer))
    {
        return fail("could not create window");
    }
    SDL_SetWindowMinimumSize(app->window, Gfx::width, Gfx::height);

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

    // a stages.txt next to the executable replaces the built-in stages, for level editing
    const std::filesystem::path base{SDL_GetBasePath()};
    std::string custom_stages;
    if (std::ifstream file{base / "stages.txt", std::ios::binary})
    {
        custom_stages.assign(std::istreambuf_iterator<char>{file}, {});
    }
    auto stage_data = stages::parse(custom_stages.empty() ? assets::as_text(assets::stages_txt()) : custom_stages);
    if (!stage_data)
    {
        SDL_SetError("%s", stage_data.error().c_str());
        return fail(custom_stages.empty() ? "bad built-in stage data" : "bad stages.txt");
    }

    app->audio.init(base / "wave"); // optional: the original shipped without sounds

    app->game = std::make_unique<Game>(app->gfx, app->audio, app->settings, std::move(*stage_data), app->data_dir);
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
            if (event->key.key == SDLK_ESCAPE)
            {
                game.save_data();
                save_settings(app);
                return SDL_APP_SUCCESS;
            }
            if (is_fullscreen_toggle(event->key))
            {
                app.settings.display = app.settings.display == settings::DisplayMode::windowed
                                           ? app.last_fullscreen
                                           : settings::DisplayMode::windowed;
                apply_settings(app);
                save_settings(app);
            }
            else if (!event->key.repeat)
            {
                game.key_down();
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
    app.accumulated_ns += now - app.last_ns;
    app.last_ns = now;
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
    app.picture = app.gfx.compose(app.settings.scaling, app.settings.side_frame);
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
        app->audio.shutdown();
        app->gfx.shutdown();
        delete app;
    }
}
