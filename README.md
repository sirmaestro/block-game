# BLOCK — source rebuild

A from-scratch C++23 / SDL3 rebuild of **BLOCK v1.30** (KENTA, 2000), a physics breakout game for
Windows 95/98/Me/2000. The original (`block130.exe`) needs exclusive 640x480 256-colour DirectDraw and does not
run properly on current Windows. This rebuild reproduces its game logic, constants and screens from the
decompiled binary, and runs in a scalable window.

## Download

Get `BLOCK-1.30-win64.zip` from the Releases page, unzip it anywhere and run `block.exe`. No installer and no
other downloads are needed.

## Building

Requires CMake 3.24+ and a C++23 compiler (tested with Visual Studio 2026 Build Tools). SDL3 is fetched
automatically.

```
cmake -S . -B build
cmake --build build --config Release
```

The result is a single `build/Release/block.exe`. The sprite sheet, stages and icon are compiled in; the
`wave/` folder of sound effects is copied next to it and is optional (the original shipped without sounds).

To make the release zip (`build/BLOCK-1.30-win64.zip`, containing `block.exe`, `wave/`, this readme and the
licence):

```
cmake --build build --config Release --target package
```

## Playing

| input | action |
|---|---|
| mouse | move the paddle |
| right button | launch a ball (up to 10 per stage) |
| left button (hold) | pull the paddle down; release to flick the ball |
| any other key | pause / stage select |
| Esc | quit (saves) |
| F11 or Alt+Enter | toggle full screen |

The mouse is captured while the window has focus, as the original owned the whole screen; Alt+Tab or Esc to leave.

Save files `block130.sys` / `block130.dat` use the original format, so existing saves can be dropped next to
`block.exe`. If that folder is not writable they go to `%APPDATA%\KENTA\BLOCK\`.

## Editing stages

`assets/stages.txt` holds all 50 stages as text (format described at the top of the file). Edit it and rebuild,
or put a modified `stages.txt` next to `block.exe` to override the built-in stages without rebuilding.

## Differences from the original

Deliberate changes, everything else follows the original including its quirks:

- Game logic runs at a fixed 60 ticks per second (the original scaled by the measured frame rate, which made
  e.g. the cyan block's ball fountain depend on the monitor refresh rate).
- Menu items act once per click; the original repeated them while the button was held.
- When the 500-ball cap is reached, the cyan blocks' ball fountains share the free slots in turn. The
  original always gave them to the earliest-broken blocks, so later fountains never fired (most visible on
  stages 16 and 40).
- `$` cannot be entered in names (it corrupts the save files in the original).
- Saves happen after each stage clear and setting change as well as on exit; corrupt save records are ignored.
- The HUD's `FPS` shows the logic rate.

## Repository layout

| path | contents |
|---|---|
| `src/` | the rebuild |
| `assets/` | sprite sheet, stage data and icon, converted from the original by `re/convert_assets.py` |
| `cmake/embed.cmake` | compiles `assets/` into the executable |
| `re/` | reverse-engineering notes (`NOTES.md`, `notes/`), Ghidra decompile (`game.c`) and tooling |
| `shim/` | an earlier experiment: a hook DLL that forces the original exe into windowed mode |
| `wave/` | sound effects and music, played from next to the exe |
| `original/` | the original `block130.exe` and its Japanese readme (`README.TXT` is Shift-JIS; `README.utf8.txt` is a UTF-8 copy) |
