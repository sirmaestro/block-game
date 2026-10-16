// Tests for the rebuild, run by ctest (and CI on Windows, macOS and Linux).
//
// Besides the file formats, they play stages headless: a simple bot plays a stage while a replay records, the
// replay is played back, and it must clear the stage at the same millisecond. The replays in tests/data were
// recorded the same way and are played back on every platform, which checks that the physics give the same
// results everywhere. Run with --write-golden to record them again after a deliberate physics change.
#include <SDL3/SDL.h>

#include <bit>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <format>
#include <fstream>
#include <functional>
#include <iterator>
#include <memory>
#include <optional>
#include <utility>
#include <string>
#include <string_view>
#include <vector>

#include "assets.hpp"
#include "audio.hpp"
#include "dmath.hpp"
#include "game.hpp"
#include "gfx.hpp"
#include "replay.hpp"
#include "save.hpp"
#include "settings.hpp"
#include "stages.hpp"

namespace
{

int failures = 0;
int checks = 0;
bool write_golden = false;

#define CHECK(condition)                                                                                         \
    do                                                                                                           \
    {                                                                                                            \
        ++checks;                                                                                                \
        if (!(condition))                                                                                        \
        {                                                                                                        \
            ++failures;                                                                                          \
            std::printf("  FAILED %s:%d: %s\n", __FILE__, __LINE__, #condition);                                 \
        }                                                                                                        \
    } while (false)

std::filesystem::path temp_dir(std::string_view name)
{
    auto dir = std::filesystem::temp_directory_path() / std::format("block_tests_{}", name);
    std::filesystem::remove_all(dir);
    std::filesystem::create_directories(dir);
    return dir;
}

std::string read_text(const std::filesystem::path &path)
{
    std::ifstream file{path, std::ios::binary};
    return {std::istreambuf_iterator<char>{file}, {}};
}

void write_text(const std::filesystem::path &path, std::string_view text)
{
    std::ofstream file{path, std::ios::binary};
    file.write(text.data(), static_cast<std::streamsize>(text.size()));
}

stages::Pack builtin_pack()
{
    return *stages::parse(assets::as_text(assets::stages_txt()), std::string{stages::original_id}, "ORIGINAL");
}

// Units in the last place between two doubles.
std::int64_t ulps(double a, double b)
{
    const auto ia = std::bit_cast<std::int64_t>(a), ib = std::bit_cast<std::int64_t>(b);
    if ((ia < 0) != (ib < 0))
    {
        return a == b ? 0 : INT64_MAX;
    }
    return ia > ib ? ia - ib : ib - ia;
}

}

// ---- headless game ----------------------------------------------------------------------------------------

// Drives a Game without a window: a software renderer, no audio device, and direct access to its state.
struct GameTest
{
    SDL_Surface *surface = nullptr;
    SDL_Renderer *renderer = nullptr;
    Gfx gfx;
    Audio audio; // never opened: every sound is silent
    settings::Settings settings;
    std::unique_ptr<Game> game;

    explicit GameTest(const std::filesystem::path &save_dir)
    {
        surface = SDL_CreateSurface(Gfx::width, Gfx::height, SDL_PIXELFORMAT_ARGB8888);
        renderer = SDL_CreateSoftwareRenderer(surface);
        if (!renderer || !gfx.init(renderer, assets::sprites_bmp()))
        {
            std::printf("  could not create a software renderer: %s\n", SDL_GetError());
            std::exit(2);
        }
        game = std::make_unique<Game>(gfx, audio, settings, std::vector{builtin_pack()}, save_dir);
    }

    ~GameTest()
    {
        game.reset();
        gfx.shutdown();
        SDL_DestroyRenderer(renderer);
        SDL_DestroySurface(surface);
    }

    static void split_test();

    // Starts a stage as if chosen from the stage select window (free mode) or reached in a time trial.
    void start_stage(int stage, std::uint32_t seed, int mode = 2)
    {
        auto &g = *game;
        g.mode_ = mode;
        g.stage_ = stage;
        g.rand_seed_ = seed;
        g.load_stage();
        g.state_ = Game::State::intro;
        g.phase_ = 0;
    }

    void tick()
    {
        game->tick(16);
    }

    bool playing() const
    {
        return game->state_ == Game::State::play || game->state_ == Game::State::intro;
    }

    void start_playback(int stage)
    {
        game->start_playback(stage);
    }

    bool playback_matched() const
    {
        return game->playback_matched_;
    }

    bool cleared() const
    {
        return game->state_ == Game::State::clear;
    }

    int stage_ms() const
    {
        return game->stage_ms_[game->stage_];
    }

    // A simple player: follows the lowest ball that is falling, aims slightly off-centre so the paddle tilt
    // spreads the shots, and launches when there are no balls.
    void bot_input(int tick_number)
    {
        auto &g = *game;
        if (g.state_ != Game::State::play)
        {
            return;
        }
        const Game::Ball *target = nullptr;
        for (const auto &b : g.balls_)
        {
            if (b.vy > 0.0 && (!target || b.y > target->y))
            {
                target = &b;
            }
        }
        if (target)
        {
            const double aim = target->x + ((tick_number / 90) % 3 - 1) * 10.0;
            g.mouse_moved(aim - g.mouse_x_, 0.0);
        }
        if (g.balls_.empty() || (tick_number % 240 == 0 && g.balls_.size() < 3))
        {
            g.right_button_down();
        }
    }
};

// ---- tests --------------------------------------------------------------------------------------------------

void test_dmath()
{
    std::int64_t worst_sin = 0, worst_cos = 0, worst_acos = 0;
    for (int i = -200000; i <= 200000; ++i)
    {
        const double x = i * 0.0001234567;
        worst_sin = std::max(worst_sin, ulps(dmath::sin(x), std::sin(x)));
        worst_cos = std::max(worst_cos, ulps(dmath::cos(x), std::cos(x)));
    }
    for (int i = -100000; i <= 100000; ++i)
    {
        const double x = i / 100000.0;
        worst_acos = std::max(worst_acos, ulps(dmath::acos(x), std::acos(x)));
    }
    std::printf("  worst difference from the C library: sin %lld, cos %lld, acos %lld ulp\n",
                static_cast<long long>(worst_sin), static_cast<long long>(worst_cos),
                static_cast<long long>(worst_acos));
    CHECK(worst_sin <= 1);
    CHECK(worst_cos <= 1);
    CHECK(worst_acos <= 1);
    CHECK(dmath::sin(0.0) == 0.0);
    CHECK(dmath::cos(0.0) == 1.0);
    CHECK(dmath::acos(1.0) == 0.0);
    CHECK(std::isnan(dmath::acos(1.0000000000000002)));
}

void test_stages()
{
    const auto pack = builtin_pack();
    CHECK(pack.stages.size() == 50);

    const std::string row = "...............\n";
    std::string one = "# a comment\nname My Pack!\nstage 1\n";
    for (int r = 0; r < stages::rows; ++r)
    {
        one += r == 3 ? "..0123456789ab.\n" : row;
    }
    const auto custom = stages::parse(one, "mine", "mine");
    CHECK(custom.has_value());
    CHECK(custom && custom->name == "My Pack!");
    CHECK(custom && custom->stages.size() == 1);
    CHECK(custom && custom->stages[0][2 + 3 * stages::columns] == 0);
    CHECK(custom && custom->stages[0][13 + 3 * stages::columns] == 11);

    CHECK(!stages::parse("stage 1\n" + row, "x", "x").has_value());             // too few rows
    CHECK(!stages::parse("stage 1\n..z............\n", "x", "x").has_value()); // unknown block
    CHECK(!stages::parse("", "x", "x").has_value());                            // no stages
    std::string many;
    for (int s = 0; s < 51; ++s)
    {
        many += "stage\n";
        for (int r = 0; r < stages::rows; ++r)
        {
            many += row;
        }
    }
    CHECK(!stages::parse(many, "x", "x").has_value()); // more than 50

    CHECK(stages::make_id("My Pack (v2)") == "My_Pack__v2_");
    CHECK(stages::make_id("original") == "custom_original");
    CHECK(stages::hash(pack.stages[0]) != stages::hash(pack.stages[1]));

    const auto dir = temp_dir("packs");
    write_text(dir / "b.txt", one);
    write_text(dir / "a.txt", "stage\nbroken\n");
    write_text(dir / "notes.md", "ignored");
    std::vector<std::string> errors;
    const auto packs = stages::load_directory(dir, errors);
    CHECK(packs.size() == 1 && packs[0].id == "b");
    CHECK(errors.size() == 1 && errors[0].starts_with("a.txt"));
}

void test_save_format()
{
    save::Data data;
    data.player_name = " $=A b";
    data.free_mode_unlocked = true;
    auto &original = data.records(stages::original_id);
    original.stage_ranking[0][0] = {12345, 2026, 10, 16, 21, 5, "KENTA"};
    original.stage_ranking[49][9] = {5999998, 2001, 1, 2, 3, 4, "  "};
    original.total_ranking[0] = {1234567, 2026, 10, 16, 21, 40, "x y z"};
    original.best_splits[0] = 12345;
    original.best_splits[49] = 1234567;
    data.records("mine").stage_ranking[2][1] = {777, 2026, 1, 1, 0, 0, "ME"};

    const auto text = save::format(data);
    const auto back = save::parse(text);
    CHECK(back == data);

    // unknown keys and sections are skipped, bad lines ignored
    auto lenient = save::parse("version = 9\nfuture = 1\n[pack original]\nstage 1.1 = bad\nstage 99.1 = 1 2026-01-01 00:00 X\n"
                                     "stage 2.1 = 500 2026-01-01 00:00 OK\n[other]\nname = ignored\n");
    CHECK(lenient.records(stages::original_id).stage_ranking[1][0].time_ms == 500);
    CHECK(lenient.records(stages::original_id).stage_ranking[0][0] == save::RankEntry{});
    CHECK(lenient.player_name.empty());
}

void test_legacy_import()
{
    const auto dir = temp_dir("legacy");
    std::string sys = "100$0$1$OLDNAME$";
    sys.push_back('\0');
    std::string dat;
    for (int record = 0; record < 510; ++record)
    {
        dat += record == 0     ? "4321$2001$6$6$12$30$KENTA$"
               : record == 500 ? "999999$2001$6$7$1$2$TOTAL$"
                               : "5999999$0$0$0$0$0$NoEntry$";
    }
    dat.push_back('\0');
    write_text(dir / "block130.sys", sys);
    write_text(dir / "block130.dat", dat);

    const auto data = save::load(dir);
    CHECK(data.player_name == "OLDNAME");
    CHECK(data.free_mode_unlocked);
    auto copy = data;
    const auto &r = copy.records(stages::original_id);
    CHECK(r.stage_ranking[0][0] == (save::RankEntry{4321, 2001, 6, 6, 12, 30, "KENTA"}));
    CHECK(r.stage_ranking[0][1] == save::RankEntry{});
    CHECK(r.total_ranking[0].time_ms == 999999 && r.total_ranking[0].name == "TOTAL");

    // the options go to block.ini
    const auto s = settings::load(dir);
    CHECK(s.master_volume == 100.0);
    CHECK(!s.show_broken_blocks);

    // once block.sav exists it wins, and the old files are left alone
    CHECK(save::write(dir, data));
    write_text(dir / "block130.dat", "garbage");
    CHECK(save::load(dir) == data);
    CHECK(read_text(dir / "block130.sys") == sys);
}

void test_settings()
{
    const auto dir = temp_dir("settings");
    settings::Settings s;
    s.display = settings::DisplayMode::borderless;
    s.scaling = settings::Scaling::fit;
    s.filter = settings::Filter::scanlines;
    s.fps_limit = 144;
    s.has_window_position = true;
    s.window_x = -1200;
    s.window_y = 40;
    s.monitor = "DELL U2720Q";
    s.master_volume = 10;
    s.pad_speed = 96;
    s.show_broken_blocks = false;
    s.stage_pack = "mine";
    CHECK(settings::write(dir, s));
    const auto back = settings::load(dir);
    CHECK(back.display == s.display && back.scaling == s.scaling && back.filter == s.filter);
    CHECK(back.fps_limit == 144 && back.has_window_position && back.window_x == -1200 && back.window_y == 40);
    CHECK(back.monitor == s.monitor && back.master_volume == 10.0 && back.pad_speed == 96.0);
    CHECK(!back.show_broken_blocks && back.stage_pack == "mine");
}

void test_replay_format()
{
    replay::Replay r;
    r.pack_id = "original";
    r.stage = 49;
    r.stage_hash = 0xfedcba9876543210ull;
    r.seed = 0xffffffffu;
    r.hit_seg = 7;
    r.time_ms = 61234;
    r.name = "A B$";
    r.year = 2026;
    r.month = 10;
    r.day = 16;
    r.hour = 23;
    r.minute = 59;
    for (int i = 0; i < 1000; ++i)
    {
        r.ticks.push_back({static_cast<std::int16_t>((i * 37) % 640), i % 7 == 0, static_cast<std::uint8_t>(i % 50 == 0 ? 3 : 0)});
    }
    const auto bytes = replay::encode(r);
    CHECK(replay::decode(bytes) == r);
    CHECK(bytes.size() < 4000);
    CHECK(!replay::decode(bytes.substr(0, bytes.size() - 1)).has_value());
    CHECK(!replay::decode(bytes + "x").has_value());
    CHECK(!replay::decode("BLOCKREQ").has_value());
}

void test_sounds()
{
    // every built-in sound decodes to exactly the original's length, so looping music stays seamless
    const std::filesystem::path wave_dir = BLOCK_TEST_DATA "/../../original/wave";
    int compared = 0;
    for (const auto &entry : std::filesystem::directory_iterator{wave_dir})
    {
        if (entry.path().extension() != ".wav")
        {
            continue;
        }
        const auto name = entry.path().stem().string();
        SDL_AudioSpec spec{};
        Uint8 *buffer = nullptr;
        Uint32 length = 0;
        if (!SDL_LoadWAV(entry.path().string().c_str(), &spec, &buffer, &length))
        {
            continue;
        }
        SDL_free(buffer);
        const auto frames = length / (SDL_AUDIO_BYTESIZE(spec.format) * spec.channels);
        const auto decoded = Audio::decode_builtin(name);
        CHECK(decoded.has_value());
        if (decoded && decoded->size() != frames)
        {
            std::printf("  %s: %zu samples, original %u\n", name.c_str(), decoded->size(), frames);
        }
        CHECK(decoded && decoded->size() == frames);
        ++compared;
    }
    CHECK(compared == 18);
}

// Plays a stage with the bot, then plays the recorded replay back. Returns the replay if the bot cleared it.
std::optional<replay::Replay> bot_round_trip(int stage, std::uint32_t seed)
{
    const auto dir = temp_dir(std::format("bot{}", stage));
    std::optional<replay::Replay> result;
    {
        GameTest t{dir};
        t.start_stage(stage, seed);
        int n = 0;
        while (t.playing() && n < 60 * 60 * 6)
        {
            t.bot_input(n++);
            t.tick();
        }
        if (!t.cleared())
        {
            std::printf("  stage %d: the bot did not clear it in %d ticks\n", stage + 1, n);
            return std::nullopt;
        }
        const int time = t.stage_ms();
        t.tick(); // the clear screen records the time and saves the replay

        auto r = replay::read(replay::best_path(dir, stages::original_id, stage));
        CHECK(r.has_value());
        if (!r)
        {
            return std::nullopt;
        }
        CHECK(r->time_ms == time);
        std::printf("  stage %d: bot cleared it in %d ms, replay %zu bytes\n", stage + 1, time, replay::encode(*r).size());
        result = r;
    }
    return result;
}

// Plays a replay from a file in a fresh game; true if it cleared the stage at the recorded time.
bool plays_back(const replay::Replay &r)
{
    const auto dir = temp_dir("playback");
    CHECK(replay::write(replay::best_path(dir, r.pack_id, r.stage), r));
    GameTest t{dir};
    t.start_playback(r.stage);
    if (!t.game->replay_playing())
    {
        return false;
    }
    int n = 0;
    while (t.playing() && n++ < 60 * 60 * 110)
    {
        // real input is ignored while a replay plays
        t.game->mouse_moved(37.0, 0.0);
        t.tick();
    }
    if (!t.cleared())
    {
        std::printf("  replay of stage %d did not clear it\n", r.stage + 1);
        return false;
    }
    t.tick();
    const bool matched = t.playback_matched();
    if (!matched)
    {
        std::printf("  replay of stage %d cleared at %d ms, recorded %d ms\n", r.stage + 1, t.stage_ms(), r.time_ms);
    }
    return matched;
}

// a member of GameTest so it may look inside Game
void GameTest::split_test()
{
    const auto golden = replay::read(std::filesystem::path{BLOCK_TEST_DATA} / "stage01.rep");
    CHECK(golden.has_value());
    if (!golden)
    {
        return;
    }
    // a time trial's first stage, played with the reference replay's input, against a best run 1 s faster
    const auto dir = temp_dir("splits");
    GameTest t{dir};
    auto &g = *t.game;
    g.total_ms_ = 0;
    g.run_splits_.fill(0);
    g.run_pb_.fill(0);
    g.run_pb_[0] = golden->time_ms - 1000;
    t.start_stage(0, golden->seed, 1);
    std::size_t i = 0;
    while (t.playing())
    {
        if (g.state_ == Game::State::play && i < golden->ticks.size())
        {
            const auto &tick = golden->ticks[i++];
            g.mouse_moved(tick.cursor_x - g.mouse_x_, 0.0);
            g.left_down_ = tick.left_down;
            for (int n = 0; n < tick.launches; ++n)
            {
                g.right_button_down();
            }
        }
        t.tick();
    }
    t.tick();
    CHECK(t.cleared());
    CHECK(g.run_splits_[0] == golden->time_ms);
    CHECK(g.split_delta(0) == 1000);
    CHECK(!g.split_delta(1).has_value());
}

void test_replays()
{
    // stages with plain, ball-spawning, item and silver blocks
    constexpr int golden_stages[] = {0, 1, 2, 5};
    const std::filesystem::path data_dir = BLOCK_TEST_DATA;
    for (const int stage : golden_stages)
    {
        const auto path = data_dir / std::format("stage{:02}.rep", stage + 1);
        if (write_golden)
        {
            for (std::uint32_t seed = 1; seed < 20; ++seed)
            {
                if (auto r = bot_round_trip(stage, seed))
                {
                    CHECK(plays_back(*r));
                    std::filesystem::create_directories(data_dir);
                    CHECK(replay::write(path, *r));
                    break;
                }
            }
        }

        const auto golden = replay::read(path);
        CHECK(golden.has_value());
        if (golden)
        {
            CHECK(golden->stage_hash == stages::hash(builtin_pack().stages[stage]));
            const bool ok = plays_back(*golden);
            CHECK(ok);
            std::printf("  stage %d reference replay (%d ms): %s\n", stage + 1, golden->time_ms, ok ? "matched" : "DIFFERENT");
        }
    }

    // a replay of an edited stage is refused
    const auto golden = replay::read(data_dir / "stage01.rep");
    if (golden)
    {
        auto edited = *golden;
        edited.stage_hash ^= 1;
        CHECK(!plays_back(edited));

        // and the check notices a replay that does not reproduce: here, the paddle a few pixels off for a moment
        auto nudged = *golden;
        for (std::size_t i = nudged.ticks.size() / 3; i < nudged.ticks.size() / 3 + 30; ++i)
        {
            nudged.ticks[i].cursor_x = static_cast<std::int16_t>(nudged.ticks[i].cursor_x > 300 ? 100 : 400);
        }
        CHECK(!plays_back(nudged));
    }
}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i)
    {
        write_golden |= std::string_view{argv[i]} == "--write-golden";
    }
    SDL_SetLogPriorities(SDL_LOG_PRIORITY_WARN);

    const std::pair<const char *, std::function<void()>> tests[] = {
        {"dmath", test_dmath},     {"stages", test_stages},   {"save format", test_save_format},
        {"legacy import", test_legacy_import}, {"settings", test_settings}, {"replay format", test_replay_format},
        {"sounds", test_sounds},   {"replays", test_replays}, {"split times", GameTest::split_test},
    };
    for (const auto &[name, run] : tests)
    {
        std::printf("%s\n", name);
        const int before = failures;
        run();
        std::printf("  %s\n", failures == before ? "ok" : "FAILED");
    }
    std::printf("%d checks, %d failed\n", checks, failures);
    return failures == 0 ? 0 : 1;
}
