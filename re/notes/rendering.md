# Rendering and in-game screens

Scope: `FUN_00402290`, `FUN_004023e0`, `FUN_00402420`, `FUN_004025a0`, `FUN_004025f0`, `FUN_004026c0`,
`FUN_004028e0`, `FUN_00402910`, `FUN_00406c00`, `FUN_00404af0`, `FUN_004050a0`, `FUN_00405770`,
`FUN_00405f70`, `FUN_00407b60`, plus helpers `FUN_004046a0`, `FUN_00404940`, `FUN_00404a10`,
`FUN_0040a970` (window frame), and the render-relevant parts of `FUN_00407fa0` (frame tick) and
`FUN_00409030` (WndProc).

All addresses are VAs. Constants `_DAT_004193xx` were read from the exe (8-byte little-endian doubles); the
value is given inline. "trunc()" means MSVC `_ftol` (`0x41028c`), i.e. truncation toward zero, never rounding.
Where Ghidra's C was broken (FUN_00406c00, the 3D text projection, the ending) the numbers below come from
the disassembly (capstone).

---------------------------------------------------------------------------------------------------------

## 1. DirectDraw setup

`FUN_00402290(hwnd, 640, 480, 640, 272)` (Ghidra shows only one param; the call site at 0x408f44 pushes 5):

| step | call | values |
|---|---|---|
| 1 | `DirectDrawCreate(NULL, &DAT_004baf30, NULL)` | fail -> return 0 -> MessageBox "Can't create DirectDraw Object" / "error" |
| 2 | `SetCooperativeLevel(hwnd, 0x11)` | DDSCL_EXCLUSIVE \| DDSCL_FULLSCREEN |
| 3 | `SetDisplayMode(640, 480, 8)` | 8-bit palettised |
| 4 | `CreateSurface` primary -> `DAT_004baf34` | dwFlags 0x21 (CAPS\|BACKBUFFERCOUNT), caps 0x218 (PRIMARYSURFACE\|FLIP\|COMPLEX), 1 back buffer |
| 5 | `GetAttachedSurface(caps=DDSCAPS_BACKBUFFER)` -> `DAT_004baf38` | back buffer, everything is drawn here |
| 6 | `CreatePalette(DDPCAPS_8BIT (4), DAT_0041ca38, &DAT_004baf40)` then `primary->SetPalette` | entries table is 256 PALETTEENTRY at 0x41ca38 (all zero at this point) |
| 7 | `CreateSurface` off-screen 640x272 -> `DAT_004baf3c` | flags 7 (CAPS\|HEIGHT\|WIDTH), caps 0x4040 OFFSCREENPLAIN\|VIDEOMEMORY; on failure retried with 0x840 OFFSCREENPLAIN\|SYSTEMMEMORY |

`FUN_00402420("BITMAP", 640, 272)` sprite-sheet load:
- `FindResource(RT_BITMAP "BITMAP")`, lock it, read the DIB colour table (biClrUsed, or 1<<biBitCount if 0),
  convert RGBQUAD (B,G,R,0) -> PALETTEENTRY (R,G,B,flags 0) into `DAT_0041ca38`, then
  `palette->SetEntries(0, 0, n, DAT_0041ca38)`. **So the hardware palette is exactly the sprite sheet's
  palette** (`assets/sprites.bmp`).
- `LoadImage(..., LR_CREATEDIBSECTION)`, `GetDC` on the sprite surface, `BitBlt` 640x272 SRCCOPY, `ReleaseDC`.
- `SetColorKey(DDCKEY_SRCBLT, {0x47, 0x47})`: **colour key = palette index 71 (0x47) = RGB (255,0,255) magenta**.
  Every BltFast uses flags 0x11 (SRCCOLORKEY|WAIT), so magenta is transparent everywhere.
- Palette notes: index 255 = (4,4,4) near-black, index 2 = (252,252,252) white, index 0 = (227,255,255).
  No DDPCAPS_ALLOW256, so on real hardware entries 0/255 may be forced to black/white by Windows
  (ambiguous; index 0 is used by only 4 sheet pixels and 255 is near-black anyway, so it makes no visible difference).

`FUN_004023e0` releases sprite surface, palette, primary, DirectDraw (WM_DESTROY).
`FUN_004025a0` (WM_ACTIVATEAPP with wParam != 0): if sprite surface `IsLost` -> `Restore` + reload sheet; if primary lost -> `Restore`.

Per frame (`FUN_00407fa0`):
1. `back->Blt(NULL, NULL, NULL, DDBLT_COLORFILL|DDBLT_WAIT (0x1000400), fx)` with `dwFillColor = 0xFFFFFF` ->
   in 8bpp only the low byte counts -> **palette index 255 = (4,4,4) i.e. clear to black**.
2. State handler draws.
3. `primary->Flip(NULL, DDFLIP_WAIT)` (vsync-paced).

**Clipping rule (important for a faithful port):** every blit is preceded by
`x >= 0 && x + w <= 640 && y >= 0 && y + h <= 480`; if any part is off-screen the **whole sprite is
skipped** (no partial clipping). Applies to glyphs, digits, balls, voxels, everything.

FPS: frame-time ring buffer (2000 entries, initialised to 100 ms). Walking backwards from the newest entry it
sums frame times until the sum >= 100 ms; `fps_raw (DAT_00421310) = n*1000/sum`. `DAT_0049d278 = fps_raw`,
or 30.0 if `fps_raw <= 30`. All animations below are "per frame += k / fps", i.e. k per second.

---------------------------------------------------------------------------------------------------------

## 2. Sprite atlas (source rects in `sprites.bmp`, 640x272)

Rects are `(left, top, right, bottom)` (exclusive right/bottom), as passed to SetRect.

### 2.1 Proportional font - `FUN_004026c0(x, y, str, colour)`
Three colour sets stacked vertically, each 48 px tall: colour 0 = white (y 0..47), colour 1 = blue (y 48..95),
colour 2 = red/pink (y 96..143). Each colour set has three 16-px rows of 32 cells, cell pitch 18 px:

| chars | row top (colour c) | cell left |
|---|---|---|
| 0x21 `!` .. 0x3F `?` | 48c + 0 | (ch - 0x21) * 18 |
| 0x40 `@` .. 0x5F `_` | 48c + 16 | (ch - 0x40) * 18 |
| 0x60 `` ` `` .. 0x7E `~` | 48c + 32 | (ch - 0x60) * 18 |

Source rect = `(left, top, left + w + 2, top + 16)` where `w = FUN_00402910(ch)`. Verified against the
sheet: every glyph's non-key pixels span exactly `w+2` columns from the cell's left (only `1` is narrower).
Note glyph 0x5C `\` is drawn as a Yen sign. Space (0x20) and chars outside 0x21..0x7E are not drawn but still advance.

Glyph width table `FUN_00402910(ch)` (default 13):

| w | characters |
|---|---|
| 5 | `! ' , . : ; I i l \|` |
| 7 | space `( ) [ ] `` ` `` { }` |
| 8 | `< > j` |
| 9 | `/` |
| 10 | `" + - = _` |
| 12 | `^` |
| 13 | everything else |
| 14 | `# & G ~` |
| 15 | `@` |
| 16 | `M W m w` |

Pen advance per character = `w - 1` (so the 2-px drop shadow of each glyph overlaps the next glyph by 3 px).
Text width `FUN_004028e0(str) = 1 + sum(w - 1)`. Centring idiom used everywhere: `x = (W - width)/2`
(integer division, toward zero). y is in pixels.

### 2.2 Big digits - `FUN_004025f0(x, yRow, str, colour)`
- Only `0`..`9` are drawn; other chars just advance. Advance 12 px per char.
- Source rect `(d*18, 208 + 32c, d*18 + 15, 240 + 32c)` -> 15x32 cells, pitch 18.
  colour 0 = orange (y 208..239), colour 1 = blue (y 240..271).
- **The y parameter is multiplied by 16** (screen y = yRow*16).

### 2.3 Misc 8/16/32-px sprites (row y = 144..175)

| rect | size | what | used by |
|---|---|---|---|
| (0,144,16,160) | 16x16 | grey bevelled square | playfield wall tile |
| (16,144,32,160) | 16x16 | pink ball | ball radius 8; HUD ball-stock icon; red (type 6) block content; window bullet (FUN_0040a120, FUN_00409570) |
| (32,144,40,152) | 8x8 | pink ball | ball radius 4; 3D-text voxel |
| (40,144,48,152) | 8x8 | blue ball | 3D-text voxel |
| (32,152,40,160) | 8x8 | orange ball | 3D-text voxel |
| (40,152,48,160) | 8x8 | black ball | 3D-text voxel |
| (48,144,80,176) | 32x32 | big pink ball | ball radius 16 |
| (80,144,112,176) | 32x32 | blue rounded window frame, 9-sliced (see 2.7) | pop-up windows |
| (112,144,128,160) | 16x16 | gold cone = **mouse pointer** (hot-spot = top-left) | all menus/windows |
| (128,144,144,160) | 16x16 | white bevelled square | name-entry background tile (FUN_0040b3f0; outside my scope, from asm) |
| (144,144,160,160) | 16x16 | blue ball | cyan (type 9) block content |
| (160,144,176,162) | 16x18 | solid white 16 rows + 2 transparent rows | ending credits mask bars |
| (176,144,192,160) | 16x16 | solid white | pause / ranking windows stage-preview background cells (FUN_004085d0, FUN_0040bb90) |
| (112,160,240,176) | 128x16 | long blue "beam/cone" | (title screen? not referenced by my functions; FUN_0040a120 uses (112,160,240,176)) |
| (240+16k,168,256+16k,176) k=0..12 | 16x8 | mini block icons for stage previews | FUN_004085d0, FUN_0040bb90 |

Mini-icon index k by stage-pixel COLORREF: olive 0x008080->0, yellow 0x00ffff->1, blue 0xff0000->2,
grey 0x808080->3, red 0x0000ff->4, magenta 0xff00ff->5, cyan 0xffff00->6, black 0->7, maroon 0x000080->8,
navy 0x800000->9, dark green 0x008000->10, green 0x00ff00->11, silver 0xc0c0c0->12.

### 2.4 Paddle (row y = 160..175)
Paddle "width units" `w = DAT_004a15ec` (default 6; total width 16*w px, centred on paddle x):
- left cap (0,160,16,176) at `(px - 8w, trunc(py) - 8)`
- middle (16,160,32,176) for k = 0..w-3 at `(px + (2 + 2k - w)*8, trunc(py) - 8)` (step 16 px)
- right cap (32,160,48,176) at `(px + 8w - 16, trunc(py) - 8)`
(px = `DAT_0049d288` int, py = `_DAT_0049d290` double, default 440.0.)

### 2.5 Blocks (row y = 176..191), 32x16, source x = type*32

| type | rect | look | stage colour (from NOTES) |
|---|---|---|---|
| 0 | (0,176,32,192) | orange capsule | olive |
| 1 | (32,176,64,192) | orange grid capsule | yellow |
| 2 | (64,176,96,192) | blue capsule | blue |
| 3 | (96,176,128,192) | blue capsule, 3 dividers | (not from stage data) |
| 4 | (128,176,160,192) | blue grid capsule | (not from stage data) |
| 5 | (160,176,192,192) | grey/silver capsule | grey |
| 6 | (192,176,224,192) | blue outline, see-through dotted magenta interior (pink ball shows through) | red |
| 7 | (224,176,256,192) | pink capsule | magenta |
| 8 | (256,176,288,192) | pink grid capsule | (not from stage data) |
| 9 | (288,176,320,192) | see-through dotted magenta capsule (blue ball shows through) | cyan |
| 10 | (320,176,352,192) | three black balls | black |
| 11 | (352,176,384,192) | white lattice | (not from stage data) |
| 12 | (384,176,416,192) | two up-triangles | maroon |
| 13 | (416,176,448,192) | two down-triangles | navy |
| 14 | (448,176,480,192) | two left-triangles | dark green |
| 15 | (480,176,512,192) | two right-triangles | green |
| 16 | (512,176,544,192) | orange capsule in a chrome tray | silver |
| 17 | (544,176,576,192) | orange grid capsule in a chrome tray | (not from stage data) |
| 18, 19 | (576..640,176..192) | empty | - |

Types 3/4/8/11/17 never come from stage pixels; they look like "damaged" states of 2/7/10/16 (physics agent to confirm).

### 2.6 Fragments, items
- **Fragment rects** table `DAT_0049d2a0` (built in `FUN_00401040`): 18 types x 32 RECTs.
  Fragment j of type t = `(32t + 4*(j%8), 176 + 4*(j/8), +4, +4)` -> the block sprite cut into an 8x4 grid
  of 4x4 pieces.
- **Items** (row y = 192..207), 32x16, source `(type*32, 192, type*32+32, 208)`:
  0 "B" tag (pink), 1 "S" tag (blue), 2 long grey double arrow (expand?), 3 short arrows pointing in
  (shrink?), 4 pink arrows (reverse?), 5 four gold spikes, 6 blue infinity sign (mugen = infinite balls).
  Semantics are guesses from the art + wav names (big/small/reverse/mugen); x = 224..639 empty.

### 2.7 Window frame - `FUN_0040a970(n)`
Window n record at `0x4b8d28 + n*0x38`: `+0 x (8-px units)`, `+4 y (16-px units)`, `+8 w (8-px units)`,
`+0xc h (16-px units)`, `+0x10 state`, `+0x18 curHalfW (double)`, `+0x20 curHalfH`, `+0x28/+0x30 velocities`.
Centre `cx = 8x + 4w`, `cy = 16y + 8h`; `hw = trunc(curHalfW)`, `hh = trunc(curHalfH)`.
9-slice of (80,144)-(112,176): corners 8x8 TL (80,144) TR (104,144) BL (80,168) BR (104,168);
top edge (88,144,104,152), bottom edge (88,168,104,176), left edge (80,152,88,168), right edge (104,152,112,168),
fill (88,152,104,168) (dotted magenta -> mostly transparent "screen-door" fill).
Corners at `(cx-hw, cy-hh)`, `(cx+hw-8, cy-hh)`, `(cx-hw, cy+hh-8)`, `(cx+hw-8, cy+hh-8)`. Edges/fill tiled in
16-px steps starting at `cx-hw+8` / `cy-hh+8`; the last tile is shortened to `(2*(hw-8)) % 16` (resp. hh) px.
Open animation (`FUN_0040b060`): curHalfW springs to `w*4-8` (factor 0.2 per 1/100 s), then curHalfH to
`h*8-8`; close (`FUN_0040b160`) springs both back to 8.0.

---------------------------------------------------------------------------------------------------------

## 3. Playfield render - `FUN_00406c00` (states 1, 2, 4, 8)

Draw order:
1. **Walls**, tile (0,144,16,160):
   top row y=0, x=0..624 step 16; bottom row y=464, x=496..624 only; left column x=0, y=16..464;
   column x=496, y=16..448; column x=624, y=16..448. The playfield interior is x 16..495, y 16..479 and is
   open at the bottom; the right-hand panel x 512..623 is the HUD.
2. **HUD** (all positions top-left, pixels):

| what | call | pos | colour |
|---|---|---|---|
| `STAGE` | text | (512,16) | 2 red |
| stage number `%2.2d` (stage+1) | digits | (597, 16) | 1 blue |
| `TIME` | text | (512,64) | 2 |
| minutes `%2.2d` = ms/60000 | digits | (512,80) | 0 orange |
| `M` | text | (538,96) | 1 |
| seconds `%2.2d` = (ms%60000)/1000 | digits | (556,80) | 0 |
| `S` | text | (582,96) | 1 |
| centiseconds `%2.2d` = (ms%1000)/10 | digits | (597,80) | 0 |
| best-record holder name (stage ranking entry 0, `0x41d4a0 + stage*0x140`) | text | (512,112) | 0 |
| best time `%2.2dm%2.2ds%2.2d` (entry 0 time, `0x41d488 + stage*0x140`) | text | (522,128) | 0 |
| TIME TRIAL only (`DAT_0049d284==1`): `TOTAL TIME` | text | (512,160) | 2 |
|  total minutes / `M` / seconds / `S` / centis | digits/text | digits y=176 at x 512/556/597, `M` (538,192), `S` (582,192) | 0 / 1 |
|  total-ranking entry 0 name `DAT_00428f90` | text | (512,208) | 0 |
|  total best `%2.2dm%2.2ds%2.2d` (`DAT_00428f78`) | text | (522,224) | 0 |
| `BALLS` | text | (512,256) | 2 |
| ball-stock icons (16,144,32,160): icon i=1..10 drawn if i <= `DAT_004b8fc8`; 5 per row at x = 529+16*col, rows y=273 and 289 | sprite | | |
| if `DAT_004b8fcc > 0`: `%ds` with (t+999)/1000 | text, right-aligned: x = 622 - width | y=288 | 0 |
| `ITEMS` | text | (512,320) | 2 |
| if `DAT_00498440 > 0` show it, else if `DAT_004baf2c > 0` show it: `%ds` ceil-seconds | text right-aligned at 622 | y=336 | 0 |
| if `DAT_004b8ee8 > 0`: `%ds` | text right-aligned at 622 | y=368 | 0 |
| `FPS : %d` (trunc(fps_raw `DAT_00421310`), not the clamped value) | text centred on x=568: x=(1136-w)/2 | y=432 | 0 |
| `Ver.1.30` | text centred on 568 | y=448 | 0 |

   No item icons are drawn in the HUD - only the countdowns. "NoEntry" records have time 5999999 ms and
   show as `99m59s99`.
3. **Paddle** (section 2.4).
4. **Blocks**, all 390 cells in index order (c + 15r):
   - if type == 9 (regardless of state!): blue ball (144,144,160,160) at `(fx0 + 6, fy0 - 2)`
   - if state == 2 (alive):
     - if type == 6: pink ball (16,144,32,160) at `(fx0 + 6, fy0 - 2)`
     - block sprite `(type*32, 176, +32, 192)` at `(fx0 - 2, fy0 - 2)`
   where (fx0, fy0) = fragment 0 position = initially `(c*32 + 18, r*16 + 18)` -> **the block sprite is
   drawn at (c*32+16, r*16+16)**. The ball "inside" the see-through types 6/9 is drawn first, so it shows
   through the transparent dotted interior; the type-9 ball stays visible even when the block is not alive
   (whether type stays 9 after destruction is the physics agent's call).
5. **Items** (`DAT_00428f64` records at 0x425270, stride 0x28: +0 x dbl, +8 y dbl, +0x20 type, +0x24 state):
   skip if state == 8; sprite `(type*32,192,+32,208)` at `(trunc(x) - 16, trunc(y) - 8)`.
6. **Fragments** (only if option `DAT_004b8fd8` "DISPLAY BROKEN BLOCKS" != 0): for each block index in the
   list `DAT_0041ce60[0..DAT_0049f6a4)` whose state == 4 (breaking), each fragment j with alive flag 1:
   rect `fragRect[type*32 + j]` at `(trunc(fx_j) - 2, trunc(fy_j) - 2)`.
7. **Balls** (`DAT_00498444` records at 0x498448 stride 0x28; +0x20 = radius r):
   r=4 -> (32,144,40,152); r=8 -> (16,144,32,160); r=16 -> (48,144,80,176); drawn at `(trunc(x) - r, trunc(y) - r)`.
   Any other radius reuses whatever rect the RECT variable last held (stale; presumably never happens).

No screen shake exists in this renderer (all wall/HUD positions are constants, no global offset). The "3D
display" of the readme is the voxel text of section 5 (and the 3D title, outside my scope).

Blinking: in state 4 the frame tick toggles `DAT_00428f70` (0<->1) whenever its accumulator exceeds 50 ms
(accumulator reset to 0, not decremented, so the period is "first frame boundary after 50 ms").

---------------------------------------------------------------------------------------------------------

## 4. Voxel 3D text engine (shared by intro / clear / game over / ending / title / ranking)

`FUN_004046a0(str)` builds voxels from the **white font (colour 0 glyphs, sheet y 0..47)** by GetPixel on a
DIB copy of the sheet:
- Voxel array `0x4a1628`, 0x30 bytes each: `+0 x`, `+8 y`, `+0x10 z`, `+0x18 vx`, `+0x20 vy` (doubles),
  `+0x28 kind` (int). Count `DAT_004b8eec`, max 2000 (returns 0 when full). The caller zeroes the count first.
- `total = sum(w + 1)` over all chars; start column `off = -((total - 1) / 2)` (int division).
- For each char (not space): scan the glyph cell columns `0 .. w+1`, rows 0..15 of its font row
  (`!`..`?` row y 0, `@`..`_` y 16, `` ` ``..`~` y 32, cell left `(ch - base) * 18`):
  pixel == 0xFCFCFC (palette index 2, glyph face) -> voxel kind 0; pixel == 0x040404 (index 255, the
  outline/shadow) -> kind 1. Voxel `x = (col + off) * 8.0`, `y = 48 - 8*row`, `z = 0`.
- After each char (incl. space): `off += w + 1`.
  So a voxel is one font pixel, spaced 8 units, text centred on x = 0, rows y = 48 .. -72.

Rotation helpers are inlined; "rotate about X by a": `y' = y cos a - z sin a; z' = y sin a + z cos a`.
"about Y": `x' = x cos a - z sin a; z' = x sin a + z cos a`. "about Z around pivot px":
`x -= px; x' = x cos a - y sin a; y' = x sin a + y cos a; x' += px`.

Depth sort: indices `DAT_004b8fdc[i] = i`, then `FUN_00404940(0, n-1)` = recursive merge sort on z,
**descending** (largest z = farthest drawn first; ties take the right half first). Temp buffers 0x421318
(left), 0x4222b8 (right), 0x423260 (merged).

Projection (8x8 voxel sprite, rect = `voxRect[kind]`, `DAT_004a15f0 + 16*kind`):
- intro/clear/game over: `d = camZ + z`; `sx = 252 + trunc(x*1000/d)`; `sy = Y0 - trunc(y*1000/d)` with
  Y0 = 236 (intro), 196 (clear), 156 (game over). camZ = `_DAT_0041ce48`.
- ending: `d = z + 2000`; `sx = trunc(x*1000/d + slideX) - 4`; `sy = 196 - trunc(y*1000/d)`.
(252/236 etc. are "centre minus 4" for the 8x8 sprite; 256,240 = playfield centre.)

---------------------------------------------------------------------------------------------------------

## 5. Screens

Common globals: `phase = DAT_004baf20`, `phaseMs = DAT_004baf24`, `angle = _DAT_004b8fd0` (degrees),
`angVel = _DAT_004b8fc0`, `camZ = _DAT_0041ce48`, `slideX = _DAT_0041ce38`, `slideV = _DAT_0049d270`,
`flag = DAT_00428f70`. "per second" means the per-frame code divides by fps.

### 5.1 Stage intro, state 2 - `FUN_00406c00` then `FUN_00404af0`
Voxel rects: kind 0 (face) = (32,144,40,152) pink, kind 1 (outline) = (40,152,48,160) black.
**Drawn in storage order** (the sort is computed but not used here - unlike every other screen).

| phase | what happens | exit |
|---|---|---|
| 0 | slideX = 640, slideV = 0, build `READY`, phase=1; then (shared init) angle=270, rects set, rotate all voxels about X by 4.71239 rad (270 deg), angVel = -3.0, camZ = 1500 | same frame continues |
| 1 | while angle > 10: dA = angVel*200/fps deg (= -600 deg/s); angle += dA; rotate voxels about X by dA | angle <= 10 -> phase 2 |
| 2 | hold (frame tick adds dt only while both windows `DAT_004b8da8`, `DAT_004b8e50` are closed) | phaseMs > 700 -> phase 3 |
| 3 | rotate as phase 1 while angle > -90 | angle <= -90 -> phase 4 |
| 4 | build `GO!!` (count reset), phase=5, angle=270, same init as phase 0 (camZ=1500, angVel=-3) | - |
| 5 | rotate while angle > 10 | -> phase 6 |
| 6 | hold | phaseMs > 300 -> phase 7 |
| 7 | if window `DAT_004b8e50` closed: camZ -= 3000/s; when camZ < 0: phase=0, flag=0, **state = 1**, stop sound 5, play sound 5 (bgm) looped, `SetCursorPos(paddleX, trunc(paddleY))` | |

"STAGE nn" slide-in (uses `flag`):
- flag 0: spring toward 200: `slideV += (slideX <= 200 ? +340 : -340)/fps`; `newX = slideX + slideV*100/fps`;
  if old >= 200 and new <= 200 -> slideV *= 0.3; if old <= 200 and new >= 200 -> slideX = 200, flag = 1.
  (Comes in from the right, overshoots left, snaps when it comes back to 200.)
- flag 1 and phase 7: slideV = 20, flag = 2.
- flag 2 and phase 7, while slideX > -150: same spring but crossing 200 downward multiplies slideV by 3.3
  -> bounces right then shoots off to the left.
- Text every frame: stage index 49 (`stage+1 == 50`): `FINAL STAGE` at `(trunc(slideX) - 4, 160)` colour 2.
  Otherwise `STAGE` at `(trunc(slideX), 160)` colour 0 and big digits `%2.2d` (stage+1) at
  `(trunc(slideX) + 85, row 9 = y 144)` colour 0 (orange). Off-screen text is simply not drawn (clip rule).
Sounds: only the bgm restart at the end.

### 5.2 Stage clear, state 4 - `FUN_00406c00` then `FUN_004050a0`
Phase 0 (once):
- GetLocalTime; stop sounds 18 (mugen), 5 (bgm), 6; play 6 (clear) once.
- Ranking insert: `rank = 10`; find first k in 0..9 with `time < ranking[stage][k].time`; if found shift
  entries k..8 down, write {time, year, month, day, hour, minute, name = player name `DAT_00428f68`};
  `DAT_004b8ef4[stage] = k` (stays 10 if not ranked).
- Build `CLEAR!!` voxels, angle = 0, angVel = 0.5, camZ = 0; rects kind 0 = (40,144,48,152) blue,
  kind 1 = (32,152,40,160) orange; tilt voxels about X by 0.349066 rad (20 deg); phase = 1. No drawing this frame.

Phase >= 1, every frame:
- camZ += 2000/s; if camZ > 1500 -> camZ = 1500 (text flies away from the camera into place in 0.75 s).
- dA = angVel*200/fps (= 100 deg/s); angle += dA; if angle > 30 -> angVel = -0.5; else if angle < -30 ->
  angVel = +0.5; rotate voxels about Y by dA (swings +-30 deg).
- sort, draw voxels (Y0 = 196).
- `Click L Button to Next Stage !!` centred in the playfield `x = (512 - w)/2`, y = 256, colour 0.
- If this clear is the new #1 (`DAT_004b8ef4[stage] == 0`): `NEW RECORD !!` centred (512), y = 320,
  colour 0, **only when flag == 0** (blinks, see section 3); then
  `- %2.2dm%2.2ds%2.2d` of (previous best = ranking entry 1 time) - (new time), colour 1.
  Otherwise `+ %2.2dm%2.2ds%2.2d` of (time - ranking entry 0 time), colour 0. Diff line centred (512), y = 336.
  (If entry 1 was "NoEntry" the minus diff is 5999999 - t.)
- Exit (WndProc, WM_LBUTTONDOWN, only when phase != 0 and both windows closed): phase = 0, stage++;
  if stage == 50: TIME TRIAL -> state 0x10 (ending), FREE -> stage = 0; then state = 2 and `FUN_004012d0` (load stage).
  (TIME TRIAL branch jumps past the state=2 assignment, so it goes to the ending.)

### 5.3 Game over, state 8 - `FUN_00406c00` then `FUN_00405770`
Phase 0 (once): stop 18, 5, 4; play 4 (gameover) once; build `Boo!!`; angle = 0, angVel = 0.5, camZ = 0;
rects kind 0 = (40,152,48,160) black, kind 1 = (32,144,40,152) pink; tilt about X by 0.698132 rad (40 deg);
phase = 1. No drawing this frame.
- Phase 1: camZ += 2000/s; when camZ > 1500: camZ = 1500, phase = 2.
- Phase 2: frame tick, while both windows closed: phaseMs > 1000 -> phase 3.
- Phase 3: while angle < 10: dA = 0.5*200/fps (100 deg/s); angle += dA; rotate about Z around pivot x = 150.0
  (the left end of the word droops by 10 deg - a "sagging" Boo).
- Every phase >= 1: sort, draw voxels (Y0 = 156), then `Click L Button to Retry !!` at (130, 256) colour 0.
- Exit (click, phase != 0): phase 0, state 2, `FUN_004012d0` (same stage reloaded).

### 5.4 Ending, state 0x10 - frame tick + `FUN_00405f70`
Frame tick before the call:
- phase 3: phaseMs += dt; > 3000 -> phase 4, phaseMs = 0.
- phase 4: phaseMs += dt; > 700 -> phase 1, `wordIdx (DAT_0049f6a8)`++ (wraps 14 -> 0), phaseMs = 0.
- Scroll: `DAT_004baf1c += dt`; when > 50: reset to 0, `scrollPx (DAT_004b8ef0)`++; when scrollPx > 15:
  scrollPx = 0, `topLine (DAT_0049d268)`++ (wraps 68 -> 0). => about 1 px per ~50 ms (~16-20 px/s, frame-quantised).

Strings rebuilt every frame on the stack:
- 3D word list (index = wordIdx, 14 entries) and its colour offset `ofs[]`:

| i | word | ofs |
|---|---|---|
| 0 | `BLOCK` | 1 |
| 1 | `Ver.1.30` | 1 |
| 2 | `PROGRAM` | 1 |
| 3 | `KENTA(22)` | 0 |
| 4 | `STAGE EDIT` | 1 |
| 5 | `KENTA(22),` | 0 |
| 6 | `KENICHI` | 0 |
| 7 | `SPECIAL THANKS` | 1 |
| 8 | `oknit,` | 0 |
| 9 | `MORIZUKI,` | 0 |
| 10 | `NORIO,` | 0 |
| 11 | `MOJI,` | 0 |
| 12 | `AND...` | 0 |
| 13 | player name (`DAT_00428f68`) | 0 |

  Voxel rects: rect0 = (32,152,40,160) orange, rect1 = (40,144,48,152) blue, rect2 = (32,144,40,152) pink;
  voxel uses `rect[ofs + kind]` -> headings (ofs 1): blue face, pink outline; names (ofs 0): orange face, blue outline.
- Scroll list (68 lines): 0..13 = 14 copies of the string at `DAT_004baf44` (bss buffer, the same string
  copied into the player name on data reset; probably empty -> blank lines), 14 = `RESULT`, 15 = blank
  (`DAT_004baf44`), 16..65 = `STAGE %2.2d  :  %2.2dm%2.2ds%2.2d` (stage 1..50, `DAT_004251a0[s]`),
  66 = blank, 67 = `TOTAL TIME  :  %2.2dm%2.2ds%2.2d` (`DAT_0041d47c`).
  Colour: line 14 -> 2, line 67 -> 1, others 0.

Phase 0 (once, then falls into phase 1 the same frame): stop 15, play 15 (ending.wav) **looped**;
`DAT_0049d298 = 10`; GetLocalTime; insert total time into the 10-entry total ranking at 0x428f78 (same
algorithm as 5.2, name = player name), `DAT_0049d298` = rank (stays 10 if unranked); topLine = scrollPx =
wordIdx = 0; set the 3 rects; phase = 1.

Phase 1 (once per word): count = 0, build voxels of `word[wordIdx]`; for every voxel: rotate about X by
20 deg (0.349066), then compute an explosion velocity in the (x, y) plane:
`r = sqrt(x^2 + y^2)`, `vx = 50*x/r / (x^2+y^2)^0.1`, `vy = 50*y/r / (x^2+y^2)^0.1` (radial, magnitude 50/r^0.2;
a voxel exactly at x=y=0 gives NaN and is never drawn). Then rotate all voxels about Y by -60 deg
(-1.047198) (velocities are *not* rotated). slideX = 1000, slideV = 0, phase = 2, and fall into the spring.

Phase 2: spring toward 320 (same form as intro: accel +-340/s, pos += v*100/fps, damp 0.2 when crossing 320
going left, snap to 320 and phase = 3 when crossing back rightwards). The word slides in from the right.

Phase 3: static (3 s, timed by the frame tick).

Phase 4 (700 ms): for each voxel `vy -= 119/s` (gravity), `x += vx*100/fps`, `y += vy*100/fps` -> the word
bursts apart and falls. Then phase 1 with the next word.

Drawing every frame, in order:
1. `CONGRATURATIONS !!` (sic) centred `(640 - w)/2`, y = 32, colour 2.
2. 15 scroll lines i = 0..14: line `L = topLine + i` (if L > 67, L -= 68) at y = `96 + 16i - scrollPx`, centred.
3. Mask bars: tile (160,144,176,162) at x = 0..624 step 16, at y = 80 and y = 320 -> two solid white 16-px
   bands (80..95, 320..335) that crop the scroll window to y 96..319.
4. `Hit Any Key to RANKING !` centred, y = 368, colour 0.
5. `THANK YOU FOR PLAYING.` centred, y = 416, colour 1.
6. Voxels, depth-sorted, ending projection (section 4).

Exit (WndProc WM_KEYDOWN, any key except Esc): stop 15; phase = 0; flag = 0; `DAT_0041ce54 = 1`;
**state = 0x100 (ranking)**. Mouse clicks do nothing here.

### 5.5 Reset-data confirmation window - `FUN_00407b60` (window 3, title state 0x40)
Window 3 geometry from `FUN_0040b220`: x = 36, y = 12, w = 36, h = 12 (units as in 2.7).
`FUN_0040a970(3)` draws the frame every call. When the window is open (`DAT_004b8de0 == 2`) and the open
animation has finished (`FUN_0040b060(3)` returns 1):
- Hit-test two options with the cursor: option o (0 = OK at row 6, 1 = CANCEL at row 9):
  `x*8 < cx < (x + w)*8` and `(row + y)*16 < cy < (row + y + 1)*16` -> hovered (drawn in colour 1).
  If hovered and the mouse button is down (`DAT_004290d0`):
  - OK: stop/play 14 (change.wav); `DAT_004b8fd8 = 1` (display broken blocks ON); player name = string at
    `DAT_004baf44`; volume slider `_DAT_004290b8 = 64.0`; `DAT_0041ce54 = 0`; every stage ranking entry and
    the 10 total-ranking entries = {5999999 ms, date 0, name "NoEntry"}; master volume =
    `trunc((1 - 0.5^0.1) * -10000)` (= -669); `DAT_004b8ef4[0..49] = 10`; `DAT_0049d298 = 10`.
    The window stays open (no state change).
  - CANCEL: stop/play 13 (close.wav); window state = 4 (closing).
- Text, each centred on the window: x = `((w*8 + x*16) - textWidth)/2`:
  `RESET YOUR DATA` y = (y+1)*16 colour 2; `Really?` y = (y+3)*16 colour 0; `OK` y = (y+6)*16
  colour hovered?1:0; `CANCEL` y = (y+9)*16 colour hovered?1:0.
- Mouse pointer (112,144,128,160) at the cursor position.
When state == 4: `FUN_0040b160(3)` (close animation) and when done `FUN_0040b220(3)` (reset to closed).

### 5.6 Boot state 0x20 (frame tick)
`Now Loading...` centred `(640 - w)/2`, y = 224, colour 0, for phase 0/1 (init runs in phase 1) and then
until 1000 ms elapsed -> state 0x40.

---------------------------------------------------------------------------------------------------------

## 6. Proposed function names

| address | name | summary |
|---|---|---|
| 00402290 | `DD_Init(hwnd, scrW, scrH, sheetW, sheetH)` | create DD, exclusive 640x480x8, primary+1 back buffer, palette, 640x272 off-screen sheet surface |
| 004023e0 | `DD_Release` | release sheet, palette, primary, DD object |
| 00402420 | `Sprites_Load(resName, w, h)` | copy DIB palette into hardware palette, blit BITMAP resource into the sheet surface, colour key index 0x47 |
| 004025a0 | `DD_RestoreLost` | on re-activation restore lost surfaces and reload the sheet |
| 004025f0 | `DrawBigDigits(x, row16, str, colour)` | 15x32 digit font (orange/blue), 12-px advance, y given in 16-px rows |
| 004026c0 | `DrawText(x, y, str, colour)` | proportional 16-px bitmap font, 3 colours |
| 004028e0 | `TextWidth(str)` | 1 + sum(glyphWidth - 1) |
| 00402910 | `GlyphWidth(ch)` | per-character width table |
| 004046a0 | `Vox_BuildText(str)` | turn white-font glyph pixels into 3D voxels (face/outline) |
| 00404940 | `Vox_SortByDepth(lo, hi)` | recursive merge sort of voxel indices by z, descending |
| 00404a10 | `Vox_Merge(nLeft, nRight)` | merge step for the above |
| 00404af0 | `Screen_StageIntro` | READY / GO!! 3D flip, STAGE nn slide, then start play + bgm |
| 004050a0 | `Screen_StageClear` | record insert, CLEAR!! 3D swing, NEW RECORD blink, time diff |
| 00405770 | `Screen_GameOver` | Boo!! 3D fly-in and droop, retry prompt |
| 00405f70 | `Screen_Ending` | total-time ranking insert, exploding 3D credits words, scrolling results |
| 00406c00 | `Render_Playfield` | walls, HUD, paddle, blocks, items, fragments, balls |
| 00407b60 | `Window_ResetData` | "RESET YOUR DATA / Really? / OK / CANCEL" confirmation window |
| 0040a970 | `Window_DrawFrame(n)` | 9-slice animated window frame |
| 0040b060 | `Window_AnimOpen(n)` | spring half-size toward target; returns 1 when open |
| 0040b160 | `Window_AnimClose(n)` | spring half-size back to 8; returns 1 when closed |
| 0040b220 | `Window_Reset(n)` | set closed + per-window geometry |

## 7. New globals

| address | name | meaning |
|---|---|---|
| 004baf30 | `g_dd` | IDirectDraw* |
| 004baf34 | `g_primary` | primary surface |
| 004baf38 | `g_back` | back buffer |
| 004baf3c | `g_sheet` | sprite-sheet surface 640x272 |
| 004baf40 | `g_palette` | IDirectDrawPalette* |
| 0041ca38 | `g_palEntries[256]` | PALETTEENTRY copy of the sheet palette |
| 00421310 | `g_fpsRaw` | double, measured fps (shown in HUD) |
| 0049d278 | `g_fps` | double, fps used for animation (30 if raw <= 30) |
| 004a1628 | `g_vox[2000]` | voxel records, 0x30 bytes (x,y,z,vx,vy doubles; kind int at +0x28) |
| 004b8eec | `g_voxCount` | voxel count |
| 004b8fdc | `g_voxOrder[2000]` | depth-sorted voxel indices |
| 00421318, 004222b8, 00423260 | merge-sort temp arrays | left, right, output |
| 004a15f0 | `g_voxRect[3]` | RECTs indexed by kind (+ending colour offset) |
| 0041ce48 | `g_camZ` | double, voxel camera distance |
| 004b8fd0 | `g_voxAngle` | double, degrees |
| 004b8fc0 | `g_voxAngVel` | double |
| 0041ce38 | `g_slideX` | double, x of sliding "STAGE nn" text / ending word centre |
| 0049d270 | `g_slideVel` | double |
| 00428f70 | `g_blinkOrSlideState` | state 4: NEW RECORD blink toggle; state 2: slide state 0/1/2 |
| 004baf1c | `g_endScrollMs` | ending scroll timer (ms) |
| 004b8ef0 | `g_endScrollPx` | 0..15 pixel offset |
| 0049d268 | `g_endTopLine` | 0..67 first visible scroll line |
| 0049f6a8 | `g_endWordIdx` | 0..13 current 3D credits word |
| 004b8fd8 | `g_optShowFragments` | option "DISPLAY BROKEN BLOCKS" |
| 0041ce60 | `g_breakingList[]` | indices of blocks in break animation |
| 0049f6a4 | `g_breakingCount` | count of the above |
| 0049d2a0 | `g_fragRect[18*32]` | fragment source rects |
| 004a15ec | `g_paddleUnits` | paddle width in 16-px tiles (default 6; half-width = 8*units px) |
| 00425270 | `g_items[]` | item records, stride 0x28 (+0 x, +8 y, +0x20 type, +0x24 state; 8 = not drawn) |
| 00428f64 | `g_itemCount` | |
| 0041d488 | `g_stageRank[50][10]` | {time ms, year, month, day, hour, minute, name[8]} 0x20 each, 0x140 per stage |
| 00428f78 | `g_totalRank[10]` | same layout, total time (name at 0x428f90) |
| 00428f68 | `g_playerName` | current player name |
| 004baf44 | `g_defaultName` | bss string copied into the player name on reset and used for blank credit lines |
| 004b8ef4 | `g_lastClearRank[50]` | rank achieved on the last clear of each stage (10 = unranked) |
| 0049d298 | `g_lastTotalRank` | rank of the last total time (10 = unranked) |
| 004290b8 | `g_volumeSlider` | double 0..128 (reset to 64) |
| 0041ce54 | ? | set 1 when leaving the ending to the ranking screen, 0 on data reset (ranking agent) |
| 004b8d28 | `g_windows[8]` | window records, 0x38 bytes (section 2.7) |
| 004b8fc8 | (known) ball stock | HUD icons |
| 004b8fcc | timer shown under BALLS | likely infinite-ball (mugen) time left |
| 00498440 / 004baf2c / 004b8ee8 | item timers shown under ITEMS | y 336 / 336 (alternative) / 368 |

## 8. Things in NOTES.md that look wrong / imprecise

1. **States 0x80 / 0x100 are swapped.** `FUN_0040b3f0` (state 0x80) plays sound 0x11 nameentry.wav, works on
   the player name and exits to state 2 -> it is **name entry**. `FUN_0040bb90` (state 0x100) plays 0x10
   ranking.wav, draws stage previews and exits to 0x40 -> it is **ranking**. The ending's key handler goes
   to 0x100, matching its "Hit Any Key to RANKING !" prompt.
2. Block record: the 32 fragments are stored as parallel arrays, not records. With record base 0x4290d8
   (cleaner than ~0x4290d4): `+0 state, +4 type, +8 face flags, +0xc alive[32] (int), +0x90 fx[32],
   +0x190 fy[32], +0x290 fvx[32], +0x390 fvy[32]` (all doubles), size 0x490. Block state 4 = breaking
   (in the fragment list).
3. "block (c,r) screen rect x = c*32+18, y = r*16+18": that is fragment 0's position; the **sprite is
   drawn 2 px up-left, at (c*32+16, r*16+16)**, 32x16.
4. Paddle draw: half-width is `8 * DAT_004a15ec` px (default 48), height 16 centred on paddle y.
5. "WM_KEYDOWN other key -> pause window (state 1)" happens for every state with `(state & 0xf) != 0`
   (1, 2, 4, 8): TIME TRIAL opens window `DAT_004b8da8`, FREE opens `DAT_004b8e50`; plays open.wav and
   stops bgm/mugen. In state 0x10 a key goes to the ranking (0x100).
6. Ball `+0x20` is the radius (4/8/16 -> 8/16/32-px sprites drawn at centre - r).

## 9. Ambiguities

- Whether palette entries 0/255 are forced to black/white (no DDPCAPS_ALLOW256). Visually irrelevant.
- Item meanings (B, S, arrows, spikes, infinity) are inferred from the art only.
- Content of `DAT_004baf44` (bss) is not set in my functions; if it is an empty string the first 14 and
  2 more credit lines are blank, which matches the layout (RESULT appears after a blank screenful).
- The type-9 overlay ball is drawn regardless of block state; whether it remains visible after the block
  breaks depends on whether physics changes the type.
- Balls with a radius other than 4/8/16 would use a stale rect (undefined in the original).
