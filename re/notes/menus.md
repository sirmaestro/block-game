# Title screen, menus, pop-up windows, input routing

Scope: `FUN_00405a60` (title), the eight pop-up windows (`FUN_0040a5c0`, `FUN_0040a120`, `FUN_004099e0`,
`FUN_00407b60`, `FUN_00409570`, `FUN_004085d0`, `FUN_00409d90`, `FUN_00409310`), the window engine
(`FUN_0040a970`, `FUN_0040b060`, `FUN_0040b160`, `FUN_0040b220`), the WndProc `FUN_00409030`, plus the title
logo helpers `FUN_004046a0`, `FUN_00404940`, `FUN_00404a10`.

Conventions: "px" = 640x480 screen pixels. "src" = rectangle in the `BITMAP` sprite sheet (`DAT_004baf3c`),
written (left,top)-(right,bottom), exclusive right/bottom (Win32 RECT). Every BltFast in this code is
**rejected entirely** (not clipped) if any part of it would fall outside 0..640 x 0..480
(`x>=0 && x+w<=640 && y>=0 && y+h<=480`). All blits use colour key (flags 0x11).
`trunc()` = MSVC `__ftol` (`0x41028c`), i.e. truncation toward zero. `/` on ints is C division (toward zero).

Text: `FUN_004026c0(x, y, str, colour)`; colour 0 = normal, 1 = highlighted (mouse hover), 2 = heading.
(Colour selects a 48-px-tall bank of the font in the sprite sheet: srcY = colour*0x30 + {0,16,32} for the
three glyph ranges `!`..`?`, `@`..`_`, `` ` ``..`~`.) Width `FUN_004028e0(str) = 1 + Σ(advance(c) - 1)`,
advances from `FUN_00402910` (default 13).

Mouse cursor: every menu screen draws the cursor sprite src (0x70,0x90)-(0x80,0xa0) (16x16) with its top-left
at `GetCursorPos()` (hotspot = top-left). Not drawn at all when x>624 or y>464 (whole-blit rejection).
The title draws it, and each open window draws it again on top (so it is always on top). In windows the cursor
is only drawn once the window is fully open.

---------------------------------------------------------------------------------------------------------

## 1. Window record (8 records, base `0x4b8d28`, stride 0x38)

`WindowRec g_windows[8]` at `0x4b8d28 + id*0x38`:

| off | type | global for id 0 | meaning |
|---|---|---|---|
| +0x00 | int | `DAT_004b8d28` | x, in 8-px units (left edge of the hit area = x*8) |
| +0x04 | int | `DAT_004b8d2c` | y, in 16-px units (top = y*16) |
| +0x08 | int | `DAT_004b8d30` | w, in 8-px units (width = w*8 px) |
| +0x0c | int | `DAT_004b8d34` | h, in 16-px units (height = h*16 px) |
| +0x10 | int | `DAT_004b8d38` | state: **1 = closed/idle, 2 = open/opening, 4 = closing** |
| +0x14 | int | `DAT_004b8d3c` | unused (never referenced) — padding |
| +0x18 | double | `DAT_004b8d40` | current half-width `hw` (px), rest value 8.0 |
| +0x20 | double | `DAT_004b8d48` | current half-height `hh` (px), rest value 8.0 |
| +0x28 | double | `DAT_004b8d50` | last width step (scratch "velocity") |
| +0x30 | double | `DAT_004b8d58` | last height step (scratch "velocity") |

State flags: id0 `0x4b8d38`, id1 `0x4b8d70`, id2 `0x4b8da8`, id3 `0x4b8de0`, id4 `0x4b8e18`, id5 `0x4b8e50`,
id6 `0x4b8e88`, id7 `0x4b8ec0`.

### Geometry table (`FUN_0040b220` Window_Reset, called for all 8 from `FUN_00401040` at boot)

| id | x | y | w | h | hit area px (x0..x1, y0..y1) | frame px when fully open | centre |
|---|---|---|---|---|---|---|---|
| 0 Options | 20 | 8 | 40 | 14 | 160..480, 128..352 | 168..472, 136..344 | (320,240) |
| 1 Adjust volume | 36 | 12 | 34 | 14 | 288..560, 192..416 | 296..552, 200..408 | (424,304) |
| 2 Pause (time trial) | 17 | 9 | 30 | 12 | 136..376, 144..336 | 144..368, 152..328 | (256,240) |
| 3 Reset data | 36 | 12 | 36 | 12 | 288..576, 192..384 | 296..568, 200..376 | (432,288) |
| 4 Display broken blocks | 36 | 12 | 42 | 14 | 288..624, 192..416 | 296..616, 200..408 | (456,304) |
| 5 Stage select (free-mode pause) | 12 | 1 | 40 | 27 | 96..416, 16..448 | 104..408, 24..440 | (256,232) |
| 6 Mode select | 25 | 9 | 30 | 12 | 200..440, 144..336 | 208..432, 152..328 | (320,240) |
| 7 Message | 16 | 11 | 48 | 8 | 128..512, 176..304 | 136..504, 184..296 | (320,240) |

Reset also sets state=1, hw=hh=8.0, both velocities 0.

### Open animation — `FUN_0040b060(id)` (Window_AnimateOpen), returns 1 when fully open

Constants: `_DAT_004193d0` = 0.2, `_DAT_00419270` = 100.0, `_DAT_0049d278` = FPS estimate (≥ 30).
```
tw = w*4 - 8                         // target half-width
vx = (tw - hw) * 0.2;  hw += vx*100/fps
if (hw > tw - 1) {                   // width done -> snap, then do height
    hw = tw
    th = h*8 - 8
    vy = (th - hh) * 0.2;  hh += vy*100/fps
    if (hh > th - 1) { hh = th; return 1 }
}
return 0
```
So: width grows first (from a 16x16 box at the centre), then height. Per-frame it closes 20/fps of the remaining
gap (at 60 fps: 1/3 of the gap per frame, ≈ 12 frames ≈ 0.2 s per axis for a 300-px window; at the 30-fps floor:
2/3 per frame). Snap threshold 1 px.

### Close animation — `FUN_0040b160(id)` (Window_AnimateClose), returns 1 when fully closed

Constants: `_DAT_00419318` = 8.0, `_DAT_004193f8` = 9.0.
```
vy = (8 - hh) * 0.2;  hh += vy*100/fps
if (hh < 9) {                        // height done first, then width
    hh = 8
    vx = (8 - hw) * 0.2;  hw += vx*100/fps
    if (hw < 9) { hw = 8; return 1 }
}
return 0
```
Order is reversed relative to opening: height collapses first, then width. When it returns 1 the window handler
calls `FUN_0040b220(id)` (state → 1, geometry re-initialised).

Reopening while closing (state 4 → 2) continues from the current hw/hh (no reset).

### Frame drawing — `FUN_0040a970(id)` (Window_DrawFrame)

Called first thing by every window handler every frame (the frame tick only calls a handler when its state ≠ 1,
so closed windows are not drawn). Uses the current animated size:
```
cx = x*8 + w*4      cy = y*16 + h*8
HW = trunc(hw)      HH = trunc(hh)
L = cx - HW   R = cx + HW - 8   T = cy - HH   B = cy + HH - 8
nx = (HW - 8) / 8   px = ((HW - 8)*2) % 16      // # of 16-px inner columns (0..nx), last one px wide
ny = (HH - 8) / 8   py = ((HH - 8)*2) % 16
```
Sprites (all from the sheet, 8-px border, 16-px tiles):

| piece | src | dest |
|---|---|---|
| top-left corner 8x8 | (0x50,0x90)-(0x58,0x98) | (L,T) |
| top-right corner | (0x68,0x90)-(0x70,0x98) | (R,T) |
| bottom-left corner | (0x50,0xa8)-(0x58,0xb0) | (L,B) |
| bottom-right corner | (0x68,0xa8)-(0x70,0xb0) | (R,B) |
| top edge 16x8 | (0x58,0x90)-(0x68,0x98) | (L+8+16i, T), i=0..nx; i==nx uses width px |
| bottom edge 16x8 | (0x58,0xa8)-(0x68,0xb0) | (L+8+16i, B), same |
| left edge 8x16 | (0x50,0x98)-(0x58,0xa8) | (L, T+8+16j), j=0..ny; j==ny uses height py |
| right edge 8x16 | (0x68,0x98)-(0x70,0xa8) | (R, T+8+16j), same |
| fill 16x16 | (0x58,0x98)-(0x68,0xa8) | (L+8+16i, T+8+16j), last column width px, last row height py |

Interior span = 2*(HW-8) = 16*nx + px, so the tiling exactly fills. When px/py is 0 the last tile is a zero-size
rect (a no-op blit). At rest size (hw=hh=8) only the four corners are visible (16x16 box).

### Common window-handler pattern (all 8 handlers)

```
DrawFrame(id)
if (state == 2):
    [pause windows only: stop sound 5 and 18 every frame]
    if AnimateOpen(id):                      // contents only once fully open
        p = GetCursorPos()
        if <gating: other windows closed>:
            for each item k:
                if x*8 < p.x < (x+w)*8 && (y+row_k)*16 < p.y < (y+row_k+1)*16:   // strict on all sides
                    hover[k] = 1                                                  // draws in colour 1
                    if g_lButtonDown (DAT_004290d0): do action k
        draw heading/items: text x = (w*8 + x*16 - TextWidth(s)) / 2 (centred in window), text y = (y+row)*16
        draw cursor sprite at p
elif (state == 4):
    if AnimateClose(id): Reset(id) [pause windows: SetCursorPos(savedCursor)]
```
Important behaviour for a faithful port:
- Hit rows span the full window width including the 8-px margin outside the drawn frame; the 16-px row is
  exclusive on both edges (effective 15 px).
- Click detection is **level-triggered**: `DAT_004290d0` is set on WM_LBUTTONDOWN and cleared on WM_LBUTTONUP;
  an action fires every frame while the button is held over the item, unless the action clears the flag
  (only PREVIOUS/NEXT in window 5 and all items of window 2 do) or closes/gates the window.
- Nothing (text, hover, cursor) is drawn during the open/close animation — just the frame.
- Sounds are always "stop then play" (`FUN_0040df10(id)` then `FUN_0040de80(id,0)`): 12 open.wav = open a
  window / select a toggle; 13 close.wav = close/cancel; 14 change.wav = actions that change game state;
  10 error.wav = refusal / test sound.

---------------------------------------------------------------------------------------------------------

## 2. Frame-tick dispatch (from `FUN_00407fa0`)

State 0x40 (title): `FUN_00405a60()` then, in this order (later = drawn on top), each only if its state ≠ 1:
win0 `FUN_0040a5c0`, win1 `FUN_0040a120`, win3 `FUN_00407b60`, win4 `FUN_00409570`, win6 `FUN_00409d90`,
win7 `FUN_00409310("You Must Clear All Stages First !!")`.

States 1/2/4/8 (in game): after the state's own update/render, win2 `FUN_004099e0` if state≠1, then win5
`FUN_004085d0` if state≠1. The gameplay updates (timers, physics, READY/GO sub-timers, game-over timer) only
run while `DAT_004b8da8 == 1 && DAT_004b8e50 == 1`, i.e. **the game stays frozen until the pause window has
fully finished closing** (state 4 counts as paused).

States 0x80 / 0x100 / 0x10 / 0x20 never call any window handler.

Consequence (faithful quirk): windows left in state 4 when the game state changes keep their size and finish
their close animation the next time a state that dispatches them is entered:
- Mode select (win6) is set to 4 and the state jumps straight to 0x80 (name entry). On the next return to the
  title the window is seen closing, and the title menu is gated (needs win6 == 1) until it has closed.
- Pause END GAME (win2/win5 → 4, state → 0x40): the close animation plays at the start of the *next* game
  (frozen READY/GO until done), and then `SetCursorPos(savedCursor)` fires.

---------------------------------------------------------------------------------------------------------

## 3. Title screen — `FUN_00405a60` (state 0x40)

### Init (when `DAT_004baf20 == 0`)
- Stop + play sound 1 (title.wav) **non-looping**.
- `DAT_004b8eec = 0`, `FUN_004046a0("BLOCK")` builds the 3-D dot logo (below).
- Spin rate `_DAT_004b8fc0 = 0.5`; camera distance `_DAT_0041ce48 = 5000.0`.
- Dot sprites: `DAT_004a15f0` rect[0] = src (0x28,0x90)-(0x30,0x98), rect[1] = src (0x20,0x90)-(0x28,0x98) (8x8 each).
- Tilt every point about the X axis by `_DAT_004193a8` = 0.34907 rad (20°):
  `y' = y*cos − z*sin;  z' = y*sin + z*cos` (z is 0 initially, so y' = y cos20°, z' = y sin20°).
- `DAT_004baf20 = 1`. The logo is **not drawn** on the init frame.

### Logo construction — `FUN_004046a0(text)` (Logo3D_BuildFromText)
Loads `BITMAP` as a DIB, reads glyph pixels from the font (colour bank 0). Glyph source cell: x = (c−base)*18,
y = 0 for `!`..`?` (base 0x21), 16 for `@`..`_` (base 0x40), 32 for `` ` ``.. (base 0x60). Spaces are skipped.
```
total = Σ (advance(c) + 1)            // "BLOCK": all advance 13 -> total 70
off   = -((total - 1) / 2)            // -34
for each char c:  a = advance(c)
    for row r = 0..15 (source y = cellY + r), worldY = 48 - 8r   (48, 40, ..., -72)
        for col = 0..a+1:
            pix = GetPixel(cellX + col, cellY + r)
            0xFCFCFC -> point(x=(col+off)*8, y=worldY, z=0, sprite 0)
            0x040404 -> point(..., sprite 1)
    off += a + 1
```
Max 2000 points (returns 0 when reached). Point record (0x30 bytes, `0x4a1628 + i*0x30`): +0 x, +8 y, +0x10 z
(doubles), +0x18/+0x20 not touched here, +0x28 int sprite index.

### Per frame (when `DAT_004baf20 != 0`)
```
dist -= 500/fps;  if (dist < 1500) dist = 1500            // _DAT_004193c0=500, _DAT_00419398=1500 -> zoom-in over 7 s
a = (0.5 * 200 / fps) degrees -> rad                      // _DAT_00419230=200, _DAT_00419300=pi/180 -> 100°/s about Y
for each point: x' = x cos a − z sin a;  z' = x sin a + z cos a      (accumulated in place)
order = 0..n-1; merge-sort order by z descending (FUN_00404940/FUN_00404a10; far first = painter's)
for each point in order:
    zc = dist + z
    sx = 316 − trunc(x * −1000 / zc)        // = 316 + trunc(1000x/zc)   (_DAT_00419358 = −1000)
    sy = 146 − trunc(y *  1000 / zc)
    BltFast 8x8 rect[sprite] at (sx, sy)
```
Merge tie-break: when left.z <= right.z the right element is taken first (not stable for equal z).
Initial `_DAT_0041ce48` value in the file is irrelevant; it is set to 5000 on init.

### Menu (fixed text, `FUN_004026c0`, x centred: `(640 − TextWidth)/2`)

| y | string | colour |
|---|---|---|
| 192 (0xc0) | `Version 1.30` | 0 |
| 288 (0x120) | `GAME START` | hover |
| 320 (0x140) | `RANKING` | hover |
| 352 (0x160) | `OPTIONS` | hover |
| 400 (0x190) | `Copyright(c) 1999-2000 KENTA(22)` | 0 |
| 416 (0x1a0) | `http://www.interq.or.jp/tohoku/kenta/` | 0 |

then the cursor sprite. Hit test (only while win0 == 1 **and** win6 == 1): **y only, any x**:
`row*16 < y < (row+1)*16` with rows 0x12, 0x14, 0x16.

| item | action |
|---|---|
| GAME START | sound 12; win6 (mode select) = 2 |
| RANKING | stop sound 1; sound 12; `DAT_00421308 = 0x100` (ranking), `DAT_004baf20 = 0` |
| OPTIONS | sound 12; win0 = 2 |

---------------------------------------------------------------------------------------------------------

## 4. The windows

Item rows are in 16-px units relative to the window's y. "col" = text colour. Hit = full window width.

### Window 0 — OPTION (`FUN_0040a5c0`, flag `DAT_004b8d38`), opened from title OPTIONS
Items active only if win1, win3, win4 are all closed (== 1).

| row | text | col | action on click |
|---|---|---|---|
| 1 | `OPTION` | 2 | — |
| 4 | `ADJUST VOLUME` | hover | sound 12; win1 = 2 |
| 6 | `RESET YOUR DATA` | hover | sound 12; win3 = 2 |
| 8 | `DISPLAY BROKEN BLOCKS` | hover | sound 12; win4 = 2 |
| 11 | `CLOSE` | hover | sound 13; win0 = 4 |

### Window 1 — ADJUST VOLUME (`FUN_0040a120`, flag `DAT_004b8d70`), from Options
No gating. Hit rows: TEST 8, CLOSE 11, slider 4.

Drawing order: track, knob, heading, MIN, MAX, TEST, CLOSE, cursor.
- Track: src (0x70,0xa0)-(0xf0,0xb0) (128x16) at (x*8+72, (y+4)*16) = (360, 256).
- Knob: src (0x10,0x90)-(0x20,0xa0) (16x16) at (x*8+64+trunc(vol), (y+4)*16) → 352..480 (knob centre on 360..488).
- `ADJUST VOLUME` row 1 col 2 centred.
- `MIN` at (x*8+26, (y+4)*16) = (314, 256) col 0; `MAX` at ((x+w)*8−66, (y+4)*16) = (494, 256) col 0.
- `TEST` row 8 hover; `CLOSE` row 11 hover.

Actions:
- TEST: stop+play sound 10 (error.wav) as a test sound (level-triggered: restarts every frame while held).
- CLOSE: sound 13; win1 = 4.
- Slider row (row 4, anywhere across x 288..560): `vol = mouse.x − (x*8 + 64)` = mouse.x − 352; if vol > 128 → 128
  (`_DAT_004193f0`); else if vol < 0 → 0. Continuous while dragging. Step = 1 px; range 0..128.
  `vol` is the double `_DAT_004290b8` (saved; default 64.0 on data reset).
  Master volume (hundredths of dB): `FUN_0040e440( trunc( (1 − pow(vol/128, 0.1)) * −10000 ) )`
  (`_DAT_00419218` = 1/128, `_DAT_00419210` = 0.1, `FUN_004102c0` = CRT `_CIpow`, `_DAT_00419200` = −10000).
  → vol 128 = 0 dB, 64 ≈ −670, 0 = −10000 (silent). Same formula used at boot (`FUN_00401040`) and on reset.
  No sound plays on slider movement.
- Note: the hover flag for the slider (local_30[2]) is uninitialised in the binary but never drawn — harmless.

### Window 2 — PAUSE (`FUN_004099e0`, flag `DAT_004b8da8`), time-trial pause
Opened by WndProc (key press in game, mode 1). While state == 2, stops sounds 5 (bgm) and 18 (mugen) every frame.
Items active only if win0, win5, win7 are closed (always true in game). Every action also clears `DAT_004290d0`.

| row | text | col | action |
|---|---|---|---|
| 1 | `PAUSE` | 2 | — |
| 4 | `TRY AGAIN` | hover | sound 14; win2 = 4; `FUN_004012d0()` (reload current stage `DAT_00425268`; resets balls=10, stage time, `DAT_004baf20`=0); state = 2 (READY/GO) |
| 6 | `END GAME` | hover | sound 14; win2 = 4; `DAT_004baf20 = 0`; `DAT_00428f70 = 0`; state = 0x40 (title) |
| 9 | `CANCEL` | hover | sound 13; if state == 1 → play sound 18 looped if `DAT_004b8fcc > 0` else sound 5 looped; win2 = 4 |

When the close animation completes: `Reset(2)` and `SetCursorPos(DAT_004a1620, DAT_004a1624)` (restores the
cursor/paddle position saved when the pause was opened).

### Window 3 — RESET YOUR DATA (`FUN_00407b60`, flag `DAT_004b8de0`), from Options
No gating. Hit rows: OK 6, CANCEL 9.

| row | text | col |
|---|---|---|
| 1 | `RESET YOUR DATA` | 2 |
| 3 | `Really?` | 0 |
| 6 | `OK` | hover |
| 9 | `CANCEL` | hover |

- OK: sound 14, then resets in memory (written to disk only on exit via `FUN_0040cbd0`):
  - `DAT_004b8fd8 = 1` (display broken blocks ON)
  - player name `DAT_00428f68` = copy of `DAT_004baf44` (a never-written bss string → empty name)
  - volume `_DAT_004290b8 = 64.0` and master volume re-applied with the formula above
  - `DAT_0041ce54 = 0` (all-stages-cleared / free mode unlock flag)
  - per-stage rankings: 50 stages × 10 entries at `0x41d488` (entry 0x20 bytes, stage stride 0x140):
    time = 5999999 ms, five ints = 0, name = `NoEntry`
  - overall ranking: 10 entries at `0x428f78`: same values
  - `DAT_004b8ef4[0..49] = 10`, `DAT_0049d298 = 10` (index of "new record" entry to highlight in the
    ranking screen; 10 = none — see ranking notes)
  - **The window is not closed** by OK, and the flag is not cleared, so the reset + sound 14 repeat every frame
    while the button is held. Only CANCEL closes.
- CANCEL: sound 13; win3 = 4.
- Ranking entry layout (probable): +0 int time ms, +4..+0x14 five ints (likely year, month, day, hour, minute
  — matches the `%4.4d/%2.2d/%2.2d %2.2d:%2.2d` DATE format), +0x18 char name[8].

### Window 4 — DISPLAY BROKEN BLOCKS (`FUN_00409570`, flag `DAT_004b8e18`), from Options
No gating. Hit rows: YES 6, NO 8, CLOSE 11.

| row | text | col |
|---|---|---|
| 1 | `DISPLAY BROKEN BLOCKS` | 2 |
| 3 | `For Better Performance,` | 0 |
| 4 | `Select 'NO'.` | 0 |
| 6 | `YES` | hover |
| 8 | `NO` | hover |
| 11 | `CLOSE` | hover |

- Marker (current choice): src (0x10,0x90)-(0x20,0xa0) 16x16 at (x*8+120, (y+6)*16) = (408, 288) if
  `DAT_004b8fd8 != 0`, else (408, 320) (row 8).
- YES: sound 12; `DAT_004b8fd8 = 1`. NO: sound 12; `DAT_004b8fd8 = 0`. Neither closes (sound repeats while held).
- CLOSE: sound 13; win4 = 4.
- `DAT_004b8fd8` gates drawing of the block-fragment break animation (read in `FUN_00401900` and render code).

### Window 5 — STAGE SELECT (`FUN_004085d0`, flag `DAT_004b8e50`), free-mode pause
Opened by WndProc (key press in game, mode ≠ 1); on open `DAT_004baf28 = DAT_00425268` (current stage).
While state == 2 stops sounds 5 and 18 every frame. **No gating.** Hit rows 3, 5, 16, 18, 21, 24.

| row | text | col | action |
|---|---|---|---|
| 1 | `STAGE SELECT` | 2 | — |
| 3 | `TRY AGAIN` | hover | sound 14; win5 = 4; `FUN_004012d0()`; state = 2 (retries the *current* stage, not the selected one) |
| 5 | `END GAME` | hover | sound 14; win5 = 4; `DAT_004baf20 = 0`; `DAT_00428f70 = 0`; state = 0x40 |
| 7..19 | stage preview | — | — |
| 16 | `PREVIOUS` | hover | sound 12; `DAT_004baf28--`, < 0 → 49; clears `DAT_004290d0` (one step per click) |
| 17 | `%d` of `DAT_004baf28+1` (1..50) | 2 | — |
| 18 | `NEXT` | hover | sound 12; `DAT_004baf28++`, > 49 → 0; clears `DAT_004290d0` |
| 21 | `GOTO THIS STAGE` | hover | `DAT_00425268 = DAT_004baf28`; sound 14; `FUN_004012d0()`; win5 = 4; state = 2 |
| 24 | `CANCEL` | hover | sound 13; if state == 1 resume bgm (18 if `DAT_004b8fcc > 0` else 5, looped); win5 = 4 |

On close completion: `Reset(5)` and `SetCursorPos(savedCursor)`.

Stage preview (drawn after the action loop, before the texts):
- Background: 15 × 13 tiles of src (0xb0,0x90)-(0xc0,0xa0) (16x16) at x = x*8+40+16i (i = 0..14) = 136..360,
  y = (y+7+j)*16 (j = 0..12) = 128..320 → a 240x208 area at (136,128).
- Blocks: the `DATA` bitmap is re-loaded with `LoadImageA(…, "DATA", IMAGE_BITMAP, 0,0, LR_CREATEDIBSECTION)`
  **every frame** and read with GetPixel at (sel%10*16+1+c, sel/10*27+1+r), c = 0..14, r = 0..25. Each non-white
  pixel draws a 16x8 mini block src ((k+15)*16, 0xa8)-((k+16)*16, 0xb0) at (x*8+40+16c, y*16+112+8r) = (136+16c, 128+8r):

  | COLORREF | k | (gameplay type from NOTES) |
  |---|---|---|
  | 0x008080 | 0 | 0 |
  | 0x00ffff | 1 | 1 |
  | 0xff0000 | 2 | 2 |
  | 0x808080 | 3 | 5 |
  | 0x0000ff | 4 | 6 |
  | 0xff00ff | 5 | 7 |
  | 0xffff00 | 6 | 9 |
  | 0x000000 | 7 | 10 |
  | 0x000080 | 8 | 12 |
  | 0x800000 | 9 | 13 |
  | 0x008000 | 10 | 14 |
  | 0x00ff00 | 11 | 15 |
  | 0xc0c0c0 | 12 | 16 |
  | anything else (white) | — | nothing drawn |

### Window 6 — MODE SELECT (`FUN_00409d90`, flag `DAT_004b8e88`), from title GAME START
Items active only if win7 is closed. Hit rows 4, 6, 9.

| row | text | col | action |
|---|---|---|---|
| 1 | `MODE SELECT` | 2 | — |
| 4 | `TIME TRIAL MODE` | hover | win6 = 4; sound 12; stop sound 1; `DAT_0049d284 = 1`; `DAT_004baf20 = 0`; state = 0x80 (name entry) |
| 6 | `FREE MODE` | hover | if `DAT_0041ce54 == 1`: same as above with `DAT_0049d284 = 2`. Else: sound 10 (error); win7 = 2 (message) — win6 stays open |
| 9 | `CANCEL` | hover | sound 13; win6 = 4 |

### Window 7 — MESSAGE (`FUN_00409310(msg)`, flag `DAT_004b8ec0`)
Only ever called with `"You Must Clear All Stages First !!"`. No gating. Hit row 5.

| row | text | col | action |
|---|---|---|---|
| 1 | `MESSAGE` | 2 | — |
| 3 | msg | 0 | — |
| 5 | `OK` | hover | sound 13; win7 = 4 |

### Free mode unlock
`DAT_0041ce54` becomes 1 only in the WndProc: a non-Esc key press during the ending (state 0x10, which is
reached when stage 50 is cleared in time trial). Reset-data sets it back to 0. It is persisted (save/load code).

---------------------------------------------------------------------------------------------------------

## 5. Input mapping — WndProc `FUN_00409030`

All messages are finally passed to `DefWindowProcA` (including handled ones). No WM_MOUSEMOVE handling — the
cursor is always polled with GetCursorPos.

| message | condition | effect |
|---|---|---|
| WM_KEYDOWN (0x100), VK_ESCAPE | any state | `DestroyWindow` → WM_DESTROY |
| WM_KEYDOWN, other key | state ∈ {1,2,4,8} (`state & 0xf != 0`) | stop sounds 5, 18, 12; play 12. Mode 1 (time trial): win2 = 2; else win5 = 2 and `DAT_004baf28 = DAT_00425268`. Both: `GetCursorPos(&DAT_004a1620)` |
| WM_KEYDOWN, other key | state == 0x10 (ending) | stop sound 15; `DAT_004baf20 = 0`; `DAT_00428f70 = 0`; `DAT_0041ce54 = 1` (unlock free mode); state = 0x100 (ranking) |
| WM_KEYDOWN, other key | states 0x20, 0x40, 0x80, 0x100 | nothing |
| WM_CLOSE (0x10) | | `DestroyWindow` |
| WM_DESTROY (2) | | `FUN_0040cbd0()` (save data), `FUN_0040e440(DAT_0041ce40)` (restore original master volume), `FUN_004023e0()` (release DirectDraw), `FUN_0040da80()` (sound shutdown), `ShowCursor(1)`, `PostQuitMessage(0)` |
| WM_ACTIVATEAPP (0x1c) | wParam ≠ 0 && `DAT_004baf30` ≠ 0 | `FUN_004025a0()`: restore lost surfaces (sprite sheet reloaded) |
| WM_LBUTTONDOWN (0x201) | win2 == 1 && win5 == 1 && `DAT_004baf20` ≠ 0 && state == 4 (stage clear) | `DAT_004baf20 = 0`; stage++. If stage == 50: time trial → state 0x10 (ending, no stage load); free → stage = 0 then continue. Otherwise `DAT_004baf20 = 0`, state = 2, `FUN_004012d0()` |
| WM_LBUTTONDOWN | same windows/phase condition, state == 8 (game over) | `DAT_004baf20 = 0`; state = 2; `FUN_004012d0()` (retry same stage) |
| WM_LBUTTONDOWN | always (after the above) | `DAT_004290d0 = 1` (L button held; used by all menus and the paddle) |
| WM_LBUTTONUP (0x202) | | `DAT_004290d0 = 0` |
| WM_RBUTTONDOWN (0x204) | state == 1 && balls < 500 && (`DAT_0049f6a0 == 1` \|\| stock > 0) | sound 2; spawn ball at (paddleX, paddleY − 8 − size) with vx 0.8, vy −4.0, size `DAT_0041ce58`; stock-- unless infinite |

Notes / quirks:
- Pause can be opened in READY/GO (2), stage clear (4) and game over (8) too, not only while playing.
- Key auto-repeat (or pressing again while paused) re-runs the open path: replays sound 12, re-saves the cursor
  position (overwriting the original paddle position with the current cursor), and in free mode resets the
  stage-select cursor to the current stage. If the window was closing (4) it reopens from its current size.
- Note: right-button launch is not blocked by the pause window in state 1 (the WndProc does not check
  win2/win5). It decrements stock even while paused; the physics is frozen until unpause. (Faithful-port quirk.)
- The game-over / stage-clear advance needs `DAT_004baf20 ≠ 0`, i.e. whatever phase the clear/game-over screen
  sets (see the stage/gameover notes).
- In the title / windows, the click acts on the frame after WM_LBUTTONDOWN and keeps acting while held.

---------------------------------------------------------------------------------------------------------

## 6. Function names

| address | proposed name | summary |
|---|---|---|
| `FUN_00405a60` | `Title_Update` | Title tick: init/title.wav, rotating 3-D "BLOCK" dot logo, menu text + hit test, cursor |
| `FUN_004046a0` | `Logo3D_BuildFromText` | Turn a string's font-glyph pixels into ≤2000 3-D points (x step 8, y step 8) |
| `FUN_00404940` | `Logo3D_SortByDepth` | Recursive merge sort of `DAT_004b8fdc` indices by z descending |
| `FUN_00404a10` | `Logo3D_Merge` | Merge step of the above (temp buffers `0x421318`, `0x4222bc`, `0x423260`) |
| `FUN_0040a5c0` | `Win0_Options` | OPTION window |
| `FUN_0040a120` | `Win1_AdjustVolume` | ADJUST VOLUME window with slider, TEST, CLOSE |
| `FUN_004099e0` | `Win2_PauseTimeTrial` | PAUSE window (TRY AGAIN / END GAME / CANCEL) |
| `FUN_00407b60` | `Win3_ResetData` | RESET YOUR DATA confirm window, resets save data |
| `FUN_00409570` | `Win4_BrokenBlocks` | DISPLAY BROKEN BLOCKS YES/NO toggle window |
| `FUN_004085d0` | `Win5_StageSelectPause` | Free-mode pause: stage select with mini preview |
| `FUN_00409d90` | `Win6_ModeSelect` | MODE SELECT window (TIME TRIAL / FREE / CANCEL) |
| `FUN_00409310` | `Win7_MessageBox` | MESSAGE window showing a string with OK |
| `FUN_0040a970` | `Window_DrawFrame` | Draw a window's 9-slice frame at its current animated size |
| `FUN_0040b060` | `Window_AnimateOpen` | Grow width then height; 1 when fully open |
| `FUN_0040b160` | `Window_AnimateClose` | Shrink height then width; 1 when fully closed |
| `FUN_0040b220` | `Window_Reset` | state=1, sizes 8.0, load per-id geometry |
| `FUN_00409030` | `WndProc` | Input routing (see §5) |
| `FUN_004025a0` | `DD_RestoreSurfaces` | Restore lost primary/sprite surfaces, reload BITMAP |
| `FUN_004026c0` | `Text_Draw` | Bitmap-font text, colour bank 0/1/2 |
| `FUN_004028e0` | `Text_Width` | 1 + Σ(advance−1) |
| `FUN_00402910` | `Font_GlyphAdvance` | Per-char advance (default 13) |
| `FUN_004102c0` | CRT `_CIpow` | pow(ST1, ST0) |
| `FUN_0041028c` | CRT `__ftol` | truncate to int |

## 7. Globals

| address | name | meaning |
|---|---|---|
| `0x4b8d28` | `g_windows[8]` | window records (§1) |
| `0x4a1620` / `0x4a1624` | `g_pauseSavedCursor` (POINT) | cursor saved when a pause window opens; restored on close |
| `0x4baf28` | `g_stageSelCursor` | stage selected in win5 (0..49); also used by the ranking screen's stage browser |
| `0x4b8fd8` | `g_displayBrokenBlocks` | 1 = draw block fragment animation |
| `0x41ce54` | `g_allStagesCleared` | free mode unlocked (set by key on ending) |
| `0x4290b8` | `g_volumeSlider` (double) | 0..128, default 64 |
| `0x41ce40` | `g_origMasterVolume` | master volume at startup (`FUN_0040e460`), restored on exit |
| `0x4290d0` | `g_lButtonDown` | L button held (menus + paddle) — NOTES calls it "paddle pressed" |
| `0x41ce48` | `g_logoDist` (double) | logo camera distance 5000 → 1500 |
| `0x4b8fc0` | `g_logoSpin` (double) | spin rate (0.5 → 100°/s); also used by other screens |
| `0x4b8eec` | `g_logoPointCount` | number of logo points |
| `0x4a1628` | `g_logoPoints[2000]` | 0x30-byte points: x,y,z double, +0x28 sprite idx |
| `0x4a15f0` | `g_logoSpriteRects[2]` | RECTs for the two dot sprites (re-used by name entry) |
| `0x4b8fdc` | `g_logoDrawOrder[]` | sorted indices |
| `0x4b8fcc` | (item timer) | when > 0 the bgm is sound 18 (mugen.wav) instead of 5 |
| `0x428f70` | `g_blink` | toggled every 50 ms on stage clear; cleared by END GAME / ending key |
| `0x428f68` | `g_playerName` char[8] | entered in name entry; cleared by reset |
| `0x4baf44` | `g_emptyString` | never written bss → "" |
| `0x428f78` | `g_rankOverall[10]` | 0x20-byte entries (time 5999999 = empty) |
| `0x41d488` | `g_rankStage[50][10]` | 0x20-byte entries |
| `0x4b8ef4` | `g_newRecordIdxStage[50]` | 10 = none (meaning inferred) |
| `0x49d298` | `g_newRecordIdxOverall` | 10 = none (meaning inferred) |
| `0x4baf30` | (DirectDraw ready flag?) | gates surface restore on WM_ACTIVATEAPP — not verified |

Doubles: `0x4193d0`=0.2, `0x419270`=100, `0x419318`=8, `0x4193f8`=9, `0x4193f0`=128, `0x419238`=0,
`0x419218`=0.0078125, `0x419210`=0.1, `0x419208`=1, `0x419200`=−10000, `0x4193c0`=500, `0x419398`=1500,
`0x419230`=200, `0x419300`=π/180, `0x4193a8`=0.349066 (20°), `0x419358`=−1000, `0x419360`=1000.

## 8. Corrections to NOTES.md

- State **0x80 is NAME ENTRY** (`FUN_0040b3f0`: "NAME ENTRY", nameentry.wav (17), → state 2) and **0x100 is
  RANKING** (`FUN_0040bb90`: ranking.wav (16), "TOTAL TIME"/"STAGE TIME", EXIT → 0x40). NOTES has them as
  "ranking?" / "name entry?" — swapped. Mode select → 0x80; title RANKING and ending key → 0x100.
- Window flags: 1 = closed, **2 = open/opening, 4 = closing** (not just "1 = closed/idle").
- `FUN_0040b160` is the close-animation step (returns 1 when done), not a "query"; `FUN_0040b220` resets.
- WM_KEYDOWN: a non-Esc key opens the pause window in states 1, 2, 4 and 8 (not only playing); in time trial it
  is win2 (PAUSE), in free mode win5 (STAGE SELECT). In the ending it also sets the free-mode unlock flag.
- `DAT_004290d0` is the generic "left button held" flag used by every menu, not only the paddle.
- Sound 18 (mugen.wav) is an alternative looping BGM used while `DAT_004b8fcc > 0`.

## 9. Ambiguities

- The exact meaning of `DAT_004b8ef4[]` / `DAT_0049d298` (value 10 on reset) is inferred from the ranking
  display code only; confirm in the ranking/name-entry analysis.
- The five ints in ranking entries are assumed to be the date/time fields.
- `DAT_004baf30`'s exact semantics not traced.
- `.data` initial values at `0x41ce40..0x41ce58` read as zero in the file (they are set at runtime), so the
  boot-time volume before loading save data is whatever the loader sets (`FUN_00401040` / save code).
- Whether the RESET-OK window staying open (and repeating while held) is intended can't be told; it is what
  the binary does.
