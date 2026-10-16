// BLOCK v1.30 (KENTA, 2000), rebuilt on SDL3.
//
// The original ran full screen at 640x480 in 256 colours through DirectDraw. This runs the same game logic
// at a fixed 60 ticks per second in a scalable window, with the original's art and stages compiled in.
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <filesystem>
#include <format>
#include <fstream>
#include <iterator>
#include <memory>
#include <string>

#include "assets.hpp"
#include "audio.hpp"
#include "game.hpp"
#include "gfx.hpp"
#include "save.hpp"
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
    std::unique_ptr<Game> game;
    Uint64 last_ns = 0;
    Uint64 accumulated_ns = 0;
    Uint64 tick_count = 0;
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

bool is_fullscreen_toggle(const SDL_KeyboardEvent &key)
{
    return key.key == SDLK_F11 || (key.key == SDLK_RETURN && (key.mod & SDL_KMOD_ALT));
}

}

SDL_AppResult SDL_AppInit(void **appstate, int, char **)
{
    SDL_SetAppMetadata("BLOCK", "1.30", "jp.kenta.block");
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        return fail("SDL_Init failed");
    }

    auto *app = new App{};
    *appstate = app;

    if (!SDL_CreateWindowAndRenderer("BLOCK", Game::screen_width * 2, Game::screen_height * 2, SDL_WINDOW_RESIZABLE,
                                     &app->window, &app->renderer))
    {
        return fail("could not create window");
    }
    SDL_SetWindowMinimumSize(app->window, Game::screen_width, Game::screen_height);
    SDL_SetRenderLogicalPresentation(app->renderer, Game::screen_width, Game::screen_height,
                                     SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);
    SDL_SetRenderVSync(app->renderer, 1);

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

    app->game = std::make_unique<Game>(app->gfx, app->audio, std::move(*stage_data), save::directory());
    capture_mouse(*app, true);
    app->last_ns = SDL_GetTicksNS();
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    auto &app = *static_cast<App *>(appstate);
    auto &game = *app.game;
    SDL_ConvertEventToRenderCoordinates(app.renderer, event);

    switch (event->type)
    {
        case SDL_EVENT_QUIT:
            game.save_data();
            return SDL_APP_SUCCESS;

        case SDL_EVENT_KEY_DOWN:
            if (event->key.key == SDLK_ESCAPE)
            {
                game.save_data();
                return SDL_APP_SUCCESS;
            }
            if (is_fullscreen_toggle(event->key))
            {
                const bool fullscreen = (SDL_GetWindowFlags(app.window) & SDL_WINDOW_FULLSCREEN) != 0;
                SDL_SetWindowFullscreen(app.window, !fullscreen);
            }
            else if (!event->key.repeat)
            {
                game.key_down();
            }
            break;

        case SDL_EVENT_MOUSE_MOTION:
            game.mouse_moved(event->motion.xrel, event->motion.yrel);
            break;

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
            game.left_button_up();
            break;

        default:
            break;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    auto &app = *static_cast<App *>(appstate);

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

    app.audio.update();
    app.gfx.present();
    SDL_RenderPresent(app.renderer);
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
