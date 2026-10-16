# BLOCK v1.30 reverse-engineering notes

Source binary: `original/block130.exe` (KENTA, 2000). MSVC 6, 32-bit, image base 0x400000.
Decompiled with Ghidra 12.1.4 headless (`ghidra/ExportDecomp.java`); game code only is in `game.c`
(0x401000–0x40f3f0). Everything from 0x40f3f0 up is the static MSVC CRT / iostream library.

Per-subsystem detail lives in `notes/`. This file is the shared glossary.

## Platform layer
- Window class/title `BLOCK`, style `WS_POPUP|WS_VISIBLE|WS_SYSMENU`, full-screen 640x480x8 DirectDraw.
- `FUN_00408f00` WinMain body: create window, sound init (`FUN_0040d880`), DirectDraw init (`FUN_00402290`),
  load sprite sheet `BITMAP` (`FUN_00402420`), `FUN_00401000` (reset to loading state), then
  PeekMessage loop calling `FUN_00407fa0` (frame tick) until it returns 0.
- `FUN_00409030` WndProc: input handling (see below).
- `DAT_004baf38` back buffer surface, `DAT_004baf3c` sprite-sheet surface, `DAT_004baf34` primary (Flip at vtbl+0x2c).
  BltFast is vtbl+0x1c, with flags 0x11 = DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT.
- Text: `FUN_004026c0(x, y, str, colour)` draws bitmap-font text; `FUN_004028e0(str)` returns its pixel width.

## Timing
- `FUN_00407fa0` measures `dt` ms with GetTickCount (`iVar4`), keeps a 2000-entry ring buffer of frame times
  (`DAT_0049f6ac`, index `DAT_0041ce50`) to compute an FPS estimate `DAT_0049d278` (min 30).
- In state 1 (playing) physics `FUN_004029f0` runs **twice** per frame, then `FUN_00401900`.

## Game state: `DAT_00421308`
| value | meaning | per-frame handler |
|---|---|---|
| 0x20 | boot / "Now Loading..." (calls `FUN_00401040` init, then waits 1000 ms) | inline |
| 0x40 | title / main menu + sub-windows | `FUN_00405a60` + window handlers |
| 2 | stage intro ("READY / GO") | `FUN_00406c00` render + `FUN_00404af0` |
| 1 | playing | physics x2, `FUN_00401900`, `FUN_00406c00` |
| 4 | stage clear | `FUN_004050a0` |
| 8 | game over | `FUN_00405770` |
| 0x10 | ending | `FUN_00405f70` |
| 0x80 | name entry | `FUN_0040b3f0` |
| 0x100 | ranking | `FUN_0040bb90` |
Sub-state/timer: `DAT_004baf20` (phase), `DAT_004baf24` (ms accumulator).
`DAT_004b8da8`, `DAT_004b8e50` (and siblings `DAT_004b8d38`, `DAT_004b8d70`, `DAT_004b8de0`, `DAT_004b8e18`,
`DAT_004b8e88`, `DAT_004b8ec0`): state field of the 8 pop-up window records (0x38 bytes each from 0x4b8d28);
1 = closed, 2 = open/opening, 4 = closing. `FUN_0040b160(n)` steps the close animation, `FUN_0040b220(n)` resets window n.
Full window system: `notes/menus.md`.

## Stage / blocks
- Current stage `DAT_00425268` (0..49). Per-stage elapsed ms `DAT_004251a0[stage]`. Total ms `DAT_0041d47c`.
- Mode: `DAT_0049d284 == 1` → TIME TRIAL (stage 50 cleared → ending), else FREE.
- Stage data: resource `DATA` (the rebuild uses the lossless text form `assets/stages.txt`
  produced by `convert_assets.py`), 161x136 4bpp. Stage s occupies
  x = (s%10)*16+1, y = (s/10)*27+1, 15 wide x 26 tall. White = empty.
- Block grid: 15 cols x 26 rows. Collision box of block (c,r): x 32c+16 .. 32c+48, y 16r+16 .. 16r+32.
  (32c+18 / 16r+18 is only the break-fragment origin.) Playfield walls x 16..496, ceiling y 16.
- Block record: 0x490 bytes (0x124 dwords), base `DAT_004290d8`, index i = c + r*15.
  - `+0x04` (`DAT_004290d8`) state: 1 = empty/destroyed, 2 = alive
  - `+0x08` (`DAT_004290dc`) type (see table), default 9999
  - `+0x0c` (`DAT_004290e0`) side-covered flags: 1 = left, 2 = top, 4 = right, 8 = bottom; a SET bit means that side
    is covered by a neighbour or wall (so it cannot be hit)
  - fragments: 32 per block (8x4 of 4x4 px) as parallel double arrays at x +0x90, y +0x190, vx +0x290, vy +0x390
- Remaining breakable count `DAT_0041d478` (0 → state 4 stage clear).

COLORREF (0x00BBGGRR) → block type, from `FUN_004012d0`:
| stage pixel | COLORREF | type | counts toward clear |
|---|---|---|---|
| olive | 0x008080 | 0 | yes |
| yellow | 0x00ffff | 1 | yes |
| blue | 0xff0000 | 2 | yes |
| grey | 0x808080 | 5 | no |
| red | 0x0000ff | 6 | yes |
| magenta | 0xff00ff | 7 | yes |
| cyan | 0xffff00 | 9 | yes |
| black | 0x000000 | 10 | yes |
| maroon | 0x000080 | 12 | no |
| navy | 0x800000 | 13 | no |
| dark green | 0x008000 | 14 | no |
| green | 0x00ff00 | 15 | no |
| silver | 0xc0c0c0 | 16 | yes |
Types 12–15 are pass-through arrow blocks (set vx/vy to ±2) and do not cover neighbours.
Per-type behaviour, items and all constants: `notes/physics.md`.

## Balls
- Count `DAT_00498444` (max 500). Record 0x28 bytes at `DAT_00498448`:
  `+0 x (double)`, `+8 y (double)`, `+0x10 vx (double, launch 0.8)`, `+0x18 vy (double, launch -4.0)`, `+0x20 radius/size (int, default 8 = DAT_0041ce58)`.
- Balls in stock `DAT_004b8fc8` (reset to 10 on every stage load). `DAT_0049f6a0` = infinite-balls item active.
- Motion: each physics step `pos += v * 100 / fps`, two steps per frame → 200·|v| px/s. Gravity `DAT_00498438`
  0.017 (−0.085 while reversed). Ball removed when y > 480 − r.

## Paddle / input
- Paddle x `DAT_0049d288` (starts 0x100), y `_DAT_0049d290` (double, starts 0x407b8000 = 440.0).
- WM_RBUTTONDOWN (0x204): launch ball from paddle (in state 1).
- WM_LBUTTONDOWN (0x201)/UP (0x202): `DAT_004290d0` = left button held (general flag, polled every frame:
  paddle pull-down in play, and menu actions — which therefore repeat while held). Click also advances out of
  stage clear / game over screens.
- WM_KEYDOWN: Esc → quit (WM_DESTROY saves data); other key → pause window (states 1, 2, 4, 8) / leave ending
  (which is also the only place free mode gets unlocked, `DAT_0041ce54`).

## Item timers (ms, count down in state 1)
`DAT_00498440` big ball (10 s), `DAT_004baf2c` small ball (10 s), `DAT_004b8ee8` reverse gravity (5 s),
`DAT_004b8fcc` infinite balls (20 s). Paddle half-width = 8 * `DAT_004a15ec` (default 6), no timer.

## Sound
EZSound wrapper (0x40d880–0x40f3a0) around DirectSound, loaded via LoadLibrary("dsound.dll").
`FUN_0040db50(id, path)` load wav, `FUN_0040e3b0(id, vol)` set per-sound volume (hundredths of dB),
`FUN_0040de80(id, loop)` play, `FUN_0040df10(id)` stop. Master volume `FUN_0040e440`.
Sound ids: 0 block, 1 title, 2 ball, 3 pad, 4 gameover, 5 bgm, 6 clear, 7 block2, 8 big, 9 small, 10 error,
11 item, 12 open, 13 close, 14 change, 15 ending, 16 ranking, 17 nameentry, 18 mugen, 19 reverse.

## Game flow (corrected)
Title → mode select → **name entry (0x80)** → stage intro (2) → play (1) → clear (4) → next stage intro …
Time trial: after stage 50 → ending (0x10) → any non-Esc key → ranking (0x100), unlocks free mode.
Free mode stage clears also record per-stage rankings. Details: `notes/ranking_save_sound.md`, `notes/menus.md`.

## Save files (plain text, `$`-separated)
- `block130.sys`: `vol$brokenBlocks$freeUnlocked$name$` + NUL. Default `64$1$0$$`. vol 0..128.
- `block130.dat`: 510 records `ms$Y$M$D$h$m$name$` — 50 stages x top-10, then overall top-10.
  Default record `5999999$0$0$0$0$0$NoEntry$`. Names max 7 chars; `$` is typeable in the original but corrupts
  the file — the rebuild must reject it. Loader does no validation.
- Master volume (DirectSound primary buffer, mB) = trunc(-10000 * (1 - (vol/128)^0.1)).
- Each sound has one buffer; play = stop+rewind+play, so retriggering restarts rather than overlaps.

## Rendering (summary; full atlas and screen layouts in `notes/rendering.md`)
- Palette = sprite sheet palette; transparent colour key is index 71 (magenta). Clear colour index 255 = (4,4,4).
- Block sprite drawn at (32c+16, 16r+16), same as its collision box.
- Any sprite even partly off-screen is skipped (no partial clipping) — keep this for fidelity.
- Font: 3 colours (white/blue/red), each a 48 px band of 3 rows of 16 px glyphs on an 18 px grid; source width =
  table width + 2, pen advance = width - 1. Big digits 15x32 (orange / blue).
- "3D display" = voxel text: each font pixel becomes an 8x8 ball sprite, rotated, depth-sorted, perspective-projected.

## Rebuild decisions
- Cyan (9) block fountain verified in `FUN_00401900`: a broken cyan block stays in state 8 and spawns one ball per
  frame (max 500 balls) until the stage ends; red (6) spawns once then becomes debris. Because this, and the
  fps-scaled physics, are tied to the frame rate, the rebuild runs game logic on a fixed 60 Hz tick
  (fps = 60 in every `100 / fps` formula) independent of display refresh.
- Menu actions repeating while the button is held (original quirk) — to be fixed in the rebuild unless the owner wants it kept.
- `$` is rejected in name entry (it is the save-file field separator).
- Spawner starvation (verified in disassembly 0x401fb9-0x40223c): spawners are walked in break order, one ball
  each per frame, so at the 500-ball cap only the earliest few get the freed slots. The rebuild hands the slots
  out round-robin (`spawn_rotor_` in physics.cpp) after the owner reported multiple fountains misbehaving.
- Rebuild source lives in `src/` (see `README.md`); comments there name the original routines and globals.
