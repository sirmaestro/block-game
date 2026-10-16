# BLOCK — source rebuild

A from-scratch C++23 / SDL3 rebuild of **BLOCK v1.30** (KENTA, 2000), a physics breakout game for
Windows 95/98/Me/2000. The original (`block130.exe`) needs exclusive 640x480 256-colour DirectDraw and does not
run properly on current Windows. This rebuild reproduces its game logic, constants and screens from the
decompiled binary.

**Version 1.40** adds smooth motion at any refresh rate (60 Hz, 144 Hz, variable refresh), borderless and
full-screen modes, scaling and widescreen options, separate music and sound volumes, mouse speed, and builds
for macOS and Linux. The game itself plays exactly as before.

<p align="center">
  <img src="docs/screenshots/gameplay.png" width="640" alt="Stage 16: blocks shattering into fragments as balls tear through them">
</p>

## Screenshots

<p align="center">
  <img src="docs/screenshots/title.png" width="49%" alt="Title screen with the rotating 3D dot logo">
  <img src="docs/screenshots/ready.png" width="49%" alt="Stage intro: 3D READY text over stage 16">
  <img src="docs/screenshots/fountain.png" width="49%" alt="Broken cyan blocks erupting into a fountain of balls">
  <img src="docs/screenshots/clear.png" width="49%" alt="Stage clear with a new record">
</p>

## Download

From the Releases page:

| system | file | to run |
|---|---|---|
| Windows 10/11 | `BLOCK-1.4-win64.zip` | unzip anywhere and run `block.exe` |
| macOS 13.3+ (Apple silicon and Intel) | `BLOCK-1.4-macos.zip` | unzip and open `BLOCK.app` (see below) |
| Linux x86-64 | `BLOCK-1.4-linux-x86_64.tar.gz` | extract and run `block` |

No installer and no other downloads are needed.

- **Windows:** the exe is not code-signed, so SmartScreen may warn on first run: *More info → Run anyway*.
- **macOS:** the app is not notarised, so the first time macOS refuses to open it. Open **System Settings →
  Privacy & Security** and click **Open Anyway** (or right-click the app → Open).
- **Linux:** built on Ubuntu 24.04, so it needs glibc 2.39 or newer. Sound and video libraries (ALSA,
  PulseAudio/PipeWire, X11/Wayland) are loaded at run time from the system.

## Building

Requires CMake 3.24+ and a C++23 compiler: Visual Studio 2022 or later on Windows, Xcode 16 on macOS, GCC 13
or Clang 17 on Linux. SDL3 is fetched automatically.

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

The result is `build/Release/block.exe` on Windows, `build/BLOCK.app` on macOS and `build/block` on Linux. The
sprite sheet, stages and icon are compiled in; the `wave/` sounds are copied next to the executable (inside the
app bundle on macOS) and are optional, as the original shipped without sounds.

On Linux, SDL needs the development packages for the systems it supports; on Debian/Ubuntu see the list in
[.github/workflows/build.yml](.github/workflows/build.yml). For a universal macOS build add
`-DCMAKE_OSX_ARCHITECTURES="arm64;x86_64"`.

To make the release package for the current platform (`build/BLOCK-1.4-<platform>.zip` or `.tar.gz`):

```
cmake --build build --config Release --target package
```

Pushing a `v*` tag to GitHub builds all three platforms and attaches the packages to a draft release
(see [.github/workflows/build.yml](.github/workflows/build.yml)).

## Playing

| input | action |
|---|---|
| mouse | move the paddle |
| right button | launch a ball (up to 10 per stage) |
| left button (hold) | pull the paddle down; release to flick the ball |
| any other key | pause / stage select |
| Esc | quit (saves) |
| F11 or Alt+Enter | switch between window and full screen |

The mouse is captured while the window has focus, as the original owned the whole screen; Alt+Tab or Esc to leave.
Switching away pauses the game.

Save files `block130.sys` / `block130.dat` use the original format, so existing saves can be dropped next to
`block.exe`. The rebuild's own settings go in `block.ini` alongside them. If that folder is not writable (and
always on macOS) they go to the per-user folder: `%APPDATA%\KENTA\BLOCK\`, `~/Library/Application
Support/KENTA/BLOCK/` or `~/.local/share/KENTA/BLOCK/`.

## Settings

**OPTIONS** on the title screen has the original's volume, data reset and broken-block settings, plus:

| setting | choices |
|---|---|
| ADJUST VOLUME | master (the original's), music and sound volumes |
| SCREEN SETTINGS → DISPLAY | window, borderless (full screen at desktop resolution), full screen (exclusive) |
| SCREEN SETTINGS → SCALING | pixel perfect (whole-number multiples), fit (largest 4:3), stretch |
| SCREEN SETTINGS → SIDE FRAME | fill the space around the 4:3 picture with the playfield's wall tiles, or leave it black |
| SCREEN SETTINGS → VSYNC | on, or off for the lowest latency |
| SCREEN SETTINGS → FPS LIMIT | none, 60, 120, 144, 165 or 240; with variable refresh (G-Sync/FreeSync), a limit a few fps under the monitor's maximum keeps it in range |
| SCREEN SETTINGS → SMOOTH MOTION | on: sprites move smoothly between the game's 60 Hz updates and the paddle follows the mouse at the display rate; off: classic 60 fps |
| MOUSE SPEED | 0.25x to 4x |

The game logic always runs at 60 updates per second, so physics and record times are the same at every refresh
rate and setting.

## Editing stages

`assets/stages.txt` holds all 50 stages as text (format described at the top of the file). Edit it and rebuild,
or put a modified `stages.txt` next to `block.exe` to override the built-in stages without rebuilding.

## Differences from the original

Deliberate changes, everything else follows the original including its quirks:

- Game logic runs at a fixed 60 ticks per second (the original scaled by the measured frame rate, which made
  e.g. the cyan block's ball fountain depend on the monitor refresh rate). Drawing runs at the display rate,
  placing moving sprites between ticks.
- Menu items act once per click; the original repeated them while the button was held.
- When the 500-ball cap is reached, the cyan blocks' ball fountains share the free slots in turn. The
  original always gave them to the earliest-broken blocks, so later fountains never fired (most visible on
  stages 16 and 40).
- `$` cannot be entered in names (it corrupts the save files in the original).
- Saves happen after each stage clear and setting change as well as on exit; corrupt save records are ignored.
- The game pauses when its window loses focus; the original kept running.
- The HUD's `FPS` shows the frames per second actually displayed.
- The version shown in the game is 1.40.

## Repository layout

| path | contents |
|---|---|
| `src/` | the rebuild |
| `assets/` | sprite sheet, stage data and icons, converted from the original by `re/convert_assets.py` |
| `cmake/embed.cmake` | compiles `assets/` into the executable |
| `.github/workflows/` | Windows, macOS and Linux builds; release packages on tags |
| `re/` | reverse-engineering notes (`NOTES.md`, `notes/`), Ghidra decompile (`game.c`) and tooling |
| `shim/` | an earlier experiment: a hook DLL that forces the original exe into windowed mode |
| `wave/` | sound effects and music, played from next to the exe |
| `docs/screenshots/` | the screenshots in this readme (native 640x480 frames) |
| `original/` | the original `block130.exe` and its Japanese readme (`README.TXT` is Shift-JIS; `README.utf8.txt` is a UTF-8 copy) |
