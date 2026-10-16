# Gameplay simulation (physics, blocks, items)

Scope: `FUN_004029f0` (physics step), `FUN_00401900` (items + debris + spawned balls),
`FUN_004046a0` / `FUN_00404940` / `FUN_00404a10` (READY/GO particle text, not gameplay),
WndProc `FUN_00409030` mouse handling, and the parts of `FUN_004012d0` (stage load) and `FUN_00407fa0` (frame tick)
that feed the simulation. I checked tricky parts against the disassembly (capstone), because Ghidra garbled the
x87 `pow` / `acos` calls.

Coordinates are screen pixels, y grows downward. All simulation state is `double` unless noted.

---------------------------------------------------------------------------------------------------
## 0. CRT helpers used (all in the CRT range, identified from disassembly)

| addr | real function | notes |
|---|---|---|
| `FUN_0041021c` | `rand()` (MSVC) | `seed = seed*0x343FD + 0x269EC3; return (seed>>16)&0x7FFF`, seed at `DAT_0041bb40` |
| `FUN_0041028c` | `_ftol` | truncate toward zero |
| `FUN_004102c0` | `_CIpow` | `pow(st1, st0)`. Every use in scope is `pow(x, 2.0)`, except fragments, which use `pow(d2, 0.8)` |
| `FUN_004104e0` | `_CIacos` | `atan2(sqrt(1-x²), x)`; acos(-1)=π, acos(1)=0 |

Ghidra renders `pow(a,2)` as `FUN_004102c0()` with lost arguments (`fVar11 / SQRT(fVar12 + extraout_ST1)`).
Each such pattern is a unit-vector component `(a - b) / sqrt((..)² + (..)²)`. The pseudocode below gives the real formulas.

---------------------------------------------------------------------------------------------------
## 1. Constants (.rdata, decoded with `struct.unpack('<d')`)

| addr | value | used as |
|---|---|---|
| 0x419208 | 1.0 | FPS sample counter increment |
| 0x419220 | 638.0 | fragment kill x max |
| 0x419228 | 478.0 | fragment kill y max (gravity down) |
| 0x419230 | 200.0 | fragment gravity scale (`g*200/fps`) |
| 0x419238 | 0.0 | zero |
| 0x419240 | 0.3 | spawned-ball velocity step |
| 0x419248 | 6.0 | block centre y offset (`fragY[0]+6`) |
| 0x419250 | 14.0 | block centre x offset (`fragX[0]+14`) |
| 0x419258 | 16.0 | block half-width, wall offset, paddle y tolerance, item catch y tolerance |
| 0x419260 | 488.0 | item lost when y > 488 |
| 0x419268 | 1.7 | item fall gravity (`vy += 1.7/fps` per frame) |
| 0x419270 | 100.0 | velocity → displacement scale (`pos += v*100/fps`) |
| 0x419278 | 1/30 = 0.0333… | item homing gain |
| 0x419280 | 568.0 | HUD target x for item 6 |
| 0x419288 | 288.0 | HUD target y for item 6 |
| 0x419290 | 376.0 | HUD target y for item 5 |
| 0x419298 | 360.0 | HUD target y for items 2,3,4 |
| 0x4192a0 | 2.0 | pow exponent; also fragment kill x/y min |
| 0x4192a8 | 544.0 | HUD target x for items 0–5 |
| 0x4192b0 | 344.0 | HUD target y for items 0,1 |
| 0x4192b8 | 0.95 | restitution on block bounce |
| 0x4192c0 | 0.8 | exponent in fragment speed formula |
| 0x4192c8 | 6.28318530718 | 2π (literal, truncated) |
| 0x4192d0 | -0.0625 | `-1/16` grid row factor |
| 0x4192d8 | -0.95 | wall/ceiling restitution |
| 0x4192e0 | -4.0 | vx min after paddle hit |
| 0x4192e8 | 4.0 | vx max after paddle hit |
| 0x4192f0 | -6.5 | vy min (fastest upward) after paddle hit |
| 0x4192f8 | -3.7 | vy max (slowest upward) after paddle hit, normal gravity only |
| 0x419300 | 0.017453292519944444 | deg→rad (stored literal, about 1e-15 off π/180) |
| 0x419308 | 0.0625 | `1/16` grid row factor (resize check) |
| 0x419310 | -0.03125 | `-1/32` grid col factor |
| 0x419318 | 8.0 | block half-height; paddle top offset; also ×8 in particle text |
| 0x419320 | -17.0 | repulsor strength |
| 0x419328 | 440.0 | paddle rest y |
| 0x419330 | 472.0 | paddle pressed y |
| 0x419338 | 0.5 | paddle tilt smoothing |
| 0x419360 | 1000.0 | ms→s in FPS estimate |
| 0x419390 | 30.0 | FPS floor |

Doubles written inline as raw dwords:

| hex | value | where |
|---|---|---|
| 0x3F916872B020C49C | 0.017 | normal gravity `g` |
| 0xBFB5C28F5C28F5C3 | -0.085 | reversed gravity |
| 0x3FE999999999999A | 0.8 | launch vx |
| 0xC010000000000000 | -4.0 | launch vy |
| 0x3FB999999999999A | 0.1 | spawned-ball vx when it would be 0 |
| 0xBFF0000000000000 | -1.0 | item initial vy |
| 0x4000…/0xC000… (hi dword) | ±2.0 | paddle vertical velocity; arrow-block velocity |
| 0x407B8000 / 0x407D8000 (hi) | 440.0 / 472.0 | paddle y |

Not used by the functions in this file (they belong to other subsystems): 0x419200 -10000, 0x419210 0.1, 0x419218 0.0078125,
0x419340 3.3, 0x419348 -150, 0x419350 340.00000000000006, 0x419358 -1000, 0x419368 3000.

---------------------------------------------------------------------------------------------------
## 2. Time base

`FUN_00407fa0` (frame tick):
```
dtMs = GetTickCount() - lastTick;  ring[idx] = dtMs;  idx = (idx+1) % 2000;   // DAT_0049f6ac, DAT_0041ce50
sum = 0; n = 0; k = idx_of_this_sample;
do { sum += ring[k]; k = (k-1 < 0) ? 1999 : k-1; n += 1.0; } while (sum < 100.0);
fps = n * 1000.0 / sum;                       // DAT_00421310
DAT_0049d278 = (fps <= 30.0) ? 30.0 : fps;    // "fps", the only time input to physics
```
So `fps` is the frame rate over the most recent ≥100 ms of frames, with a floor of 30 (the step is never longer than 1/30 s).

In state 1, while no pop-up window is open (`DAT_004b8da8==1 && DAT_004b8e50==1`):
1. Each item timer that is > 0 is reduced by `dtMs` (it can go negative): `DAT_00498440`, `DAT_004baf2c`, `DAT_004b8ee8`, `DAT_004b8fcc`.
2. The stage and total elapsed times are increased by `dtMs`.
3. `PhysicsStep()` runs **twice**, then `UpdateItemsAndDebris()` once.
4. If `remaining == 0`, state becomes 4 (clear). Otherwise, if `ballCount==0 && stock==0 && !infinite`, state becomes 8 (game over).

Every integration step has the form `pos += v * 100 / fps`. `v` is in pixels per 1/100 s of one step. Two steps run per
frame, so a ball moves **200·|v| px/s** in real time. Items and fragments are integrated once per frame, so they move 100·|v| px/s.
To reproduce this exactly in SDL3, keep the same FPS estimator, or replace `fps` with `1/dt_seconds`
(floor 30) and keep the two physics sub-steps.

---------------------------------------------------------------------------------------------------
## 3. Data layouts (corrections to NOTES.md included)

### Ball (`DAT_00498448`, stride 0x28, count `DAT_00498444`, cap 500)
`+0 x`, `+8 y`, `+0x10 vx`, `+0x18 vy` (doubles), `+0x20 int r` (radius: 4 small / 8 normal / 16 big), `+0x24` unused.
Removing a ball copies the next records down. Only 9 dwords are copied, so `+0x24` is not moved.

### Block (stride 0x490, 390 = 15×26 records; **the record really starts at 0x4290d8**)
| off from 0x4290d8 | global | meaning |
|---|---|---|
| +0x000 | `DAT_004290d8` | state: 1 empty, 2 alive, 4 destroyed (debris animating or hidden), 8 destroyed + spawns balls (types 6, 9) |
| +0x004 | `DAT_004290dc` | type |
| +0x008 | `DAT_004290e0` | neighbour flags (see §6) |
| +0x00c | `DAT_004290e4` | `int alive[32]` (fragment alive) |
| +0x08c | — | 4 bytes padding |
| +0x090 | `DAT_00429168` | `double fragX[32]` |
| +0x190 | `DAT_00429268` | `double fragY[32]` |
| +0x290 | `DAT_00429368` | `double fragVX[32]` |
| +0x390 | `DAT_00429468` | `double fragVY[32]` |

The stage loader (`FUN_004012d0`) sets the fragments up as a 8×4 grid of 4×4-px pieces:
`fragX[k] = 32c+18 + (k%8)*4`, `fragY[k] = 16r+18 + (k/8)*4`, `alive[k]=1`, velocities 0.
Physics uses `fragX[0]`, `fragY[0]` as the block's position:
**collision centre `(cx,cy) = (fragX[0]+14, fragY[0]+6) = (32c+32, 16r+24)`, half-extents 16×8**, so the
collision box is `x∈[32c+16, 32c+48]`, `y∈[16r+16, 16r+32]`. That box is 2 px left of and 2 px above the fragment/sprite origin (32c+18, 16r+18).
The grid lookup also uses this origin: `col = trunc((x-16)/32)`, `row = trunc((y-16)/16)`. The renderer team should check where
the block sprite is drawn. The physics box clearly starts at x=16 / y=16.

### Item (`DAT_00425270`, stride 0x28, count `DAT_00428f64`, never removed until stage reload; room for 390)
`+0 x`, `+8 y`, `+0x10 vx`, `+0x18 vy` (doubles), `+0x20 int type (0..6)`, `+0x24 int state`.
State 1 = falling, 2 = flying to the HUD, 4 = parked in the HUD (effect active), 8 = gone (fell off the screen).

### Dying-block list
`int DAT_0041ce60[]` holds block indices, with count `DAT_0049f6a4`.

---------------------------------------------------------------------------------------------------
## 4. Paddle

Globals: `px = DAT_0049d288` (int), `py = DAT_0049d290` (double), `pvy = DAT_004290c8` (double),
`tilt = DAT_004290c0` (double, degrees), `w = DAT_004a15ec` (int; **half-width = 8·w px**, default 6 → 96 px wide),
`pressed = DAT_004290d0`.

At the start of every physics step (so twice per frame):
```
GetCursorPos(&m);
oldPx = px;  px = m.x;
tilt  = (m.x + tilt - oldPx) * 0.5;          // smoothed horizontal mouse speed (px/step), used as degrees
lo = 8*w + 16;  hi = (62 - w) * 8;           // = 496 - 8w
if (m.x < lo)       { px = lo; SetCursorPos(lo, m.y); }
else if (m.x > hi)  { px = hi; SetCursorPos(hi, m.y); }
// paddle edges therefore stay inside [16, 496]
if (!pressed) { if (py <= 440) { pvy = 0; py = 440; } else pvy = -2.0; }
else          { if (py >= 472) { pvy = 0; py = 472; } else pvy = +2.0; }
py += pvy * 100 / fps;
```
Flick mechanic: holding the left button pushes the paddle down 32 px at 200 px/s-units (`pvy=+2`). Releasing brings it back up
(`pvy=-2`). While `pvy=-2`, a hit gives the ball extra upward speed; while `pvy=+2`, the ball bounces softer (see §5.4).
`tilt` uses the raw cursor x (before clamping) minus the previous clamped paddle x. The second sub-step of a frame
usually sees dx≈0, so `tilt` halves.

Mouse (WndProc `FUN_00409030`):
- `WM_LBUTTONDOWN`: sets `pressed=1` (always). If no window is open and `DAT_004baf20 != 0`, it also advances state 4 → next stage
  (stage 50 in TIME TRIAL → ending) or state 8 → retry same stage. Both go to state 2 + `FUN_004012d0` (stage reload).
- `WM_LBUTTONUP`: `pressed=0`.
- `WM_RBUTTONDOWN`: **launch** if `ballCount<500 && state==1 && (infinite || stock>0)`. More than one ball can be in play.
  ```
  play(2);   // "ball"
  ball = { x=px, y=py-8-R, vx=0.8, vy=-4.0, r=R }   // R = DAT_0041ce58 (current global radius)
  if (!infinite) stock--;
  ```
  The launch is not blocked while windows are open, because it checks only `state==1`.

---------------------------------------------------------------------------------------------------
## 5. Physics step — `FUN_004029f0` → `PhysicsStep()`

Globals: `g = DAT_00498438` (double, 0.017 normally), `R = DAT_0041ce58` (global ball radius 4/8/16).

```cpp
void PhysicsStep() {
  UpdatePaddle();                                     // §4
  for (int i = 0; i < ballCount; ) {
    Ball& b = balls[i];
    double x0 = b.x, y0 = b.y;
    double vx = b.vx;
    double vy = b.vy + g * 100.0 / fps;               // gravity
    // --- repulsor blocks (type 10 or 11, alive) -- inverse-square push AWAY from block centre
    for (int k = 0; k < 390; ++k) if ((type[k]==10||type[k]==11) && state[k]==2) {
      double cx = fragX[k][0]+14, cy = fragY[k][0]+6;
      double dx = b.x-cx, dy = b.y-cy, d2 = dx*dx+dy*dy, d = sqrt(d2);
      double a = (-17.0 / d2) * 100.0 / fps;          // computed with ORIGINAL b.x,b.y
      vx += ((cx - b.x) / d) * a;                     // = +17*dx/d^3 *100/fps  (repulsion)
      vy += ((cy - b.y) / d) * a;
    }
    double x = b.x + vx * 100.0 / fps;
    double y = b.y + vy * 100.0 / fps;

    // --- deferred resize (big/small items). The ball takes the new global radius only when it fits.
    int r = b.r;
    if (b.r != R) {
      bool inPaddleBox = (px-8*w-R < x && x <= px+8*w+R) && (py-8-R < y && y < py+16);
      bool inWalls = (R+16 <= x && x <= 496-R && R+16 <= y && y <= 480-R);
      if (!inPaddleBox && inWalls && !OverlapsAnyBlock3x3(x, y, R)) {   // same test as §5.5, radius R
        play(R > b.r ? 8 /*big*/ : 9 /*small*/);
        b.r = R;
      }
      r = b.r;
    }
    // --- paddle (box test only; no direction test, no radius in x)
    if (px-8*w < x && x <= px+8*w && py-8-r < y && y <= py+16) {
      play(3);                                       // "pad"
      double s = sin(tilt*DEG), c = cos(tilt*DEG);   // DEG = 0.017453292519944444
      double wv = pvy - vy;                          // reflect vy relative to paddle speed (pvy NOT added back)
      double nvx = c*vx - wv*s;
      double nvy = vx*s + wv*c;
      vx = nvx; vy = nvy;
      if (vy > -3.7 && g > 0) vy = -3.7;             // minimum launch speed (only with normal gravity)
      else if (vy < -6.5)     vy = -6.5;
      if (vx > 4.0) vx = 4.0; else if (vx < -4.0) vx = -4.0;
      y = py - 8 - r;
    }
    // --- walls (playfield x 16..496, ceiling 16, no floor)
    double L = r + 16, Rw = 496 - r;
    if (x < L)  { vx *= -0.95; x = (x - L)  * vx / (x - x0) + L;  }
    if (x > Rw) { vx *= -0.95; x = (x - Rw) * vx / (x - x0) + Rw; }
    if (y < L)  { vy *= -0.95; y = (y - L)  * vy / (y - y0) + L;  }
    if (y > 480 - r) {                               // lost: remove, do NOT advance i
      erase(balls, i); --ballCount; continue;
    }
    // --- blocks: 3x3 neighbourhood, row-major; cell index recomputed from CURRENT x,y every cell
    unsigned arrows = 0;                             // 2:up 8:down 1:left 4:right
    for (int ro = 0; ro < 3; ++ro) for (int co = 0; co < 3; ++co) {
      int row = (int)((y-16)/16), col = (int)((x-16)/32);       // trunc
      int k = (row-1+ro)*15 + (col-1+co);            // no column wrap guard (harmless aliasing)
      if (k < 0 || k > 389 || state[k] != 2) continue;
      if (!Overlaps(k, x, y, r)) continue;           // §5.5
      HitBlock(k, x, y, vx, vy, r, arrows);          // §6, may move/reflect ball
    }
    if (arrows & 2) vy = -2.0; else if (arrows & 8) vy = 2.0;
    if (arrows & 1) vx = -2.0; else if (arrows & 4) vx = 2.0;
    b.x = x; b.y = y; b.vx = vx; b.vy = vy;
    ++i;
  }
}
```
Notes and quirks:
- The wall formula divides by the step displacement `x - x0` (= `vx_old*100/fps` when nothing else changed vx this step).
  The result is `L + 0.95·(L-x)·fps/100`, so the penetration is mirrored and scaled by fps/100, not 1. If `x == x0`, this divides by zero (+inf/NaN).
  This is very unlikely but possible. A faithful port should keep the formula and guard the zero case.
- Gravity reversal (`g<0`) turns off the -3.7 clamp, so a paddle hit can leave the ball slow or even moving downward.
- There is no ball–ball interaction.
- The resize is deferred per ball: each ball keeps its old radius until it is clear of the paddle box, the walls and blocks.

### 5.5 Ball–block overlap test (block centre cx,cy; L=cx-16, Rt=cx+16, T=cy-8, B=cy+8)
All comparisons are strict:
```
overlap = (L-r < x && x < Rt+r && T < y && y < B)          // horizontally expanded box
       || (L < x && x < Rt && T-r < y && y < B+r)          // vertically expanded box
       || dist2(x,y,L,T) < r*r || dist2(x,y,Rt,T) < r*r
       || dist2(x,y,Rt,B) < r*r || dist2(x,y,L,B) < r*r;   // rounded corners
```

### 5.6 Which face was hit (octant), used by reflection
The 8 vertices of the rounded-rectangle outline:
`p0=(L,T-r) p1=(Rt,T-r) p2=(Rt+r,T) p3=(Rt+r,B) p4=(Rt,B+r) p5=(L,B+r) p6=(L-r,B) p7=(L-r,T)`.
```
ang(dx,dy) = acos(dx/hypot) ; if (dy/hypot < 0) ang = 2π - ang     // = atan2(dy,dx) in [0,2π), y-down, 2π=6.28318530718
θk  = ang(pk.x - x, pk.y - y)                    // direction from ball centre to each vertex
φ   = ang(-vx, -vy)                              // direction the ball came from
for k in 0..7: k1=(k+1)%8
  if ((θk1 < θk && ((θk <= φ && φ < 2π) || (0 <= φ && φ < θk1))) || (θk <= φ && φ < θk1)) seg = k;   // last match wins
```
`seg`: 0 top face, 1 top-right corner, 2 right, 3 bottom-right, 4 bottom, 5 bottom-left, 6 left, 7 top-left.
`seg` is a function local that is **not reset** between blocks or balls. If nothing matches (v=0 → NaN), it keeps its previous value
(the first time, the value is whatever is on the stack). A port should default it, for example to 0.

Neighbour flags change corners into faces (bit set = a solid neighbour on that side, see §6.1):
```
if (f&1) { if (seg==7) seg=0; else if (seg==5) seg=4; }   // left neighbour
if (f&2) { if (seg==1) seg=2; else if (seg==7) seg=6; }   // top neighbour
if (f&4) { if (seg==1) seg=0; else if (seg==3) seg=4; }   // right neighbour
if (f&8) { if (seg==3) seg=2; else if (seg==5) seg=6; }   // bottom neighbour
```
### 5.7 Reflection (`LAB_004042f3`)
```
seg 0: vy = -vy*0.95; y = T - r;
seg 2: vx = -vx*0.95; x = Rt + r;
seg 4: vy = -vy*0.95; y = B + r;
seg 6: vx = -vx*0.95; x = L - r;
seg 1/3/5/7: corner P = (Rt,T)/(Rt,B)/(L,B)/(L,T)
   d = |P - ball|; n = (P - ball)/d;  s = |v|;
   t  = vy*n.x - vx*n.y;                 // tangential   (computed as ((vy/s)nx-(vx/s)ny)*s)
   vn = (vx*n.x + vy*n.y) * 0.95;        // normal
   vx = -t*n.y - vn*n.x;  vy = t*n.x - vn*n.y;
   x = P.x - r*n.x;  y = P.y - r*n.y;
```
The ball is pushed out and reflected whether or not it is moving into the face.

---------------------------------------------------------------------------------------------------
## 6. Block types and hit behaviour

### 6.1 Neighbour flags (`+0x08`) — **NOTES.md has the meaning inverted**
A bit is **set when that side is covered** by a solid neighbour (or by the wall/ceiling). It does not mean the face is exposed.
Stage load (`FUN_004012d0`, row-major order) sets them for every non-white cell whose type is not 12–15:
- col 0 → `|=1`, col 14 → `|=4`, row 0 → `|=2` (the walls and ceiling count as neighbours, the floor does not).
- If the left cell (state≠1, type∉12..15) exists: `self|=1`, `left|=4`. If the cell above qualifies: `self|=2`, `above|=8`.
Types 12–15 neither set flags nor count as neighbours.
When a block is destroyed, its neighbours' bits are cleared: `left &= ~4` (if col≠0), `above &= ~8` (if idx>14),
`right &= ~1` (if col≠14), `below &= ~2` (if idx<375).
The flags only matter for the corner→face remap in §5.6. Arrow blocks never reflect, so their flags are irrelevant.

### 6.2 Per-type rules (r = ball radius; "destroy" = §6.3; "reflect" = §5.6+5.7)
Sound ids: 7 = block2 (damage), 0 = block (destroy), 3 = pad (indestructible clink).

| type | colour | on hit | reflect? |
|---|---|---|---|
| 0 | olive | r==4: → type 1, snd 7. else destroy | r==4 yes; r==8 yes; r==16 **no** (big ball ploughs through) |
| 1 | yellow (also olive after small hit) | destroy | only if r==4 |
| 2 | blue | r==4: → 3, snd 7; r==8: → 4, snd 7; r==16: destroy | yes |
| 3 | (blue, 2nd stage) | r==4: → 4, snd 7; else destroy | yes |
| 4 | (blue, last stage) | destroy | unless r==16 |
| 5 | grey | indestructible, snd 3 | yes |
| 6 | red | destroy → state 8 → spawns **1** ball next frame (§7.3) | yes |
| 7 | magenta | r==4: → 8, snd 7; else destroy + **item** | r==16 no, else yes |
| 8 | (magenta after small hit) | destroy + **item** | only if r==4 |
| 9 | cyan | destroy → state 8 → spawns a ball **every frame for the rest of the stage** while balls<500 (§7.3) | yes |
| 10 | black **repulsor** (§5) | r==4: → 11, snd 7; else destroy | unless r==16 |
| 11 | (black after small hit, still repulsor) | destroy | only if r==4 |
| 12 | maroon arrow | pass-through, forces vy=-2 (up) after the block loop | no |
| 13 | navy arrow | forces vy=+2 (down) | no |
| 14 | dark-green arrow | forces vx=-2 (left) | no |
| 15 | green arrow | forces vx=+2 (right) | no |
| 16 | silver | only breakable **from above** (seg 0,1,7 after the remap). Other sides: snd 3, reflect. From above: r==4 → 17 + snd 7; else destroy | from above: unless r==16 |
| 17 | (silver after small hit) | from above: destroy; else snd 3 + reflect | from above: only if r==4 |
| 9999 | unknown colour | destroy (counts toward clear) | yes |

So the small ball deals 1 damage per hit and "soft" types let the normal/big ball pass. Blue takes 3/2/1 hits (small/normal/big).
Arrow priority: up beats down, and left beats right. They are combined over all overlapped arrow blocks in the step.

Clear counter `DAT_0041d478`: at load, +1 for each non-white cell, and −1 again for types 5, 12, 13, 14, 15. Each destroy subtracts 1.
There is **no score**. The only result is the elapsed time (`DAT_004251a0[stage]`, `DAT_0041d47c`).

### 6.3 Destroy (`LAB_00403fbb`)
```
play(0);
if (type==6 || type==9) { state=8; dying[n++]=k; }
else { state=4; if (DISPLAY_BROKEN_BLOCKS /*DAT_004b8fd8*/) dying[n++]=k; }
if (type==7 || type==8) items[nItems++] = { x=cx, y=cy, vx=0, vy=-1.0, type=rand()%7, state=1 };
clear neighbour bits (6.1);  remaining--;
if (DISPLAY_BROKEN_BLOCKS) {
  double s2 = vx*vx + vy*vy;                       // ball speed SQUARED, pre-reflection velocity & position
  for f in 0..31: dx = fragX[f]-x; dy = fragY[f]-y; d2 = dx*dx+dy*dy;
     fragVX[f] = (dx/sqrt(d2)) * s2 * 8.0 / pow(d2, 0.8);
     fragVY[f] = (dy/sqrt(d2)) * s2 * 8.0 / pow(d2, 0.8);   // = 8*s2*d̂ / d^1.6 : explosion away from impact point
}
```
If the option is off, a type-6 block's fragments still "animate" after the ball spawns, starting at velocity 0. The renderer does
not draw them (render checks the option), so this has no visible effect.

---------------------------------------------------------------------------------------------------
## 7. `FUN_00401900` → `UpdateItemsAndDebris()` (once per frame, after the 2 physics steps)

### 7.1 Items
Item types (`rand()%7`, uniform): **0 BIG ball, 1 SMALL ball, 2 paddle +, 3 paddle −, 4 paddle MAX, 5 REVERSE gravity, 6 infinite balls ("mugen")**.
```
state 1 (falling):  vy += 1.7/fps;  y += vy*100/fps;   (x is not integrated)
                    if (y > 488) state = 8;
                    if (px-(8w+16) < x < px+(8w+16) && py-16 < y < py+16) { Catch(type); state = 2; }
state 2 (to HUD):   T = target(type);  d = |T - pos|;  u = (T-pos)/d;
                    v = d * u / 30;  pos += v*100/fps;          // exponential approach
                    if ((int)(vx*100)==0 && (int)(vy*100)==0) state = 4;
                    targets: 0,1 → (544,344); 2,3,4 → (544,360); 5 → (544,376); 6 → (568,288)
state 4 (in HUD):   tests below; when one is true the icon goes back to state 1 and falls off the HUD
                    (the paddle cannot reach x≥544, so it cannot be caught again and ends in state 8)
state 8: dead (kept in the array, presumably not drawn)
```
Catch effects and sounds (stop+play = restart the sample):

| type | catch | HUD icon drops (expiry) when |
|---|---|---|
| 0 BIG | `R=16; bigTimer(DAT_00498440) += 10000; smallTimer=0` (no sound here; each ball plays 8 when it grows) | `R==4` (replaced by small), or `bigTimer<1` → **also sets R=8** |
| 1 SMALL | `R=4; smallTimer(DAT_004baf2c) += 10000; bigTimer=0` | `R==16`, or `smallTimer<1` → **sets R=8** |
| 2 PADDLE+ | snd 11; `if (w<28) w+=3` (6,9,…,27,30) | `w<7 || w==30` |
| 3 PADDLE− | snd 11; `if (w>5) w-=3` (6→3 min) | `w>5` |
| 4 PADDLE MAX | snd 11; `w=30` (paddle 480 px = whole field, pinned at x=256) | `w<7` |
| 5 REVERSE | snd 19; `g=-0.085; revTimer(DAT_004b8ee8) += 5000` | `revTimer<1` → snd 14, `g=0.017` |
| 6 MUGEN | stop 5 (bgm), play 18 looped; `infinite(DAT_0049f6a0)=1; mugenTimer(DAT_004b8fcc) += 20000` | `mugenTimer<1` → stop 18, play 5 looped, `infinite=0` |

The paddle size has no timer and lasts until the stage reloads. The expiry checks run in the order of the table, inside an if/else-if chain per icon.
Effects are tied to the icon, not to the timer. Two caught BIG items both park in the HUD, and both reset R when the timer runs out.
Stage load resets: balls 0, R=8, stock **10**, all four timers 0, infinite 0, items 0, dying list 0, w=6, px=256,
py=440, tilt=0, pvy=0, g=0.017. Pausing does not touch the bgm/mugen choice: the menus code re-picks sound 5 or 18 using `DAT_004b8fcc`.

### 7.2 Debris fragments (dying list entries with state ≠ 8)
```
for each f with alive[f]:
   fragVY += g*200/fps;  fragX += fragVX*100/fps;  fragY += fragVY*100/fps;
   if (g > 0) { if (fragY > 478 || fragX < 2 || fragX > 638) alive[f]=0; }
   else if (g < 0 && fragY < 2) alive[f]=0;              // g==0: never dies
if no fragment was alive at the start of this pass: remove entry (shift list down)
```
There is no lifetime: a fragment lives until it leaves the screen. The gravity is twice the ball's per call, but it is called half as often, so the effective acceleration is the same.
Quirk: after a removal the loop index still advances, so the entry that shifted into this slot is skipped for one frame.

### 7.3 Ball-spawning blocks (dying list entries with state == 8)
```
if (ballCount < 500) {
  play(2);
  ball = { x=fragX[0]+14, y=fragY[0]+6,                  // block centre
           vx=(5 - rand()%11)*0.3, vy=(3 - rand()%11)*0.3, r=8 };   // vx ∈ [-1.5,1.5], vy ∈ [-2.1,0.9]
  if (vx == 0.0) vx = 0.1;
  if (type == 6) state = 4;   // red: one ball, then debris
}                             // cyan (9): stays in state 8 → one new ball EVERY FRAME until the stage ends
```
The spawned ball always has r=8 and then adopts R through the deferred resize.
I believe the cyan "fountain" is intended (a multiball block), because nothing else ever changes state 8. The rewrite must not rely on stage reload alone if it pools memory: the list entry is never removed.

### 7.4 500-ball cap
`ballCount < 500` is checked only at launch (RBUTTON) and at the red/cyan spawn. The array has exactly 500 slots.

---------------------------------------------------------------------------------------------------
## 8. READY/GO particle text (not gameplay, listed because it is in scope)
- `FUN_004046a0(str)` → **BuildParticleText**: samples the font glyphs in the `BITMAP` sheet. Rows: `'!'..'?'` y=0, `'@'..'_'` y=16,
  `` '`'..'~' `` y=32, glyph x=(c-base)*18, width from `FUN_00402910`, sampling `w+2` columns × 16 rows. Each pixel of colour
  0xFCFCFC (flag 0) or 0x040404 (flag 1) becomes a particle `{x=(col+xoff)*8, y=48-8*row, z=0, flag}` in `DAT_004a1628`
  (stride 0x30: +0 x, +8 y, +0x10 z, +0x18/+0x20 written later by `FUN_00404af0`, +0x28 int flag). Count `DAT_004b8eec`, max 2000
  (returns 0 when full). xoff starts at `-((Σ(w+1))-1)/2` (int division) and advances by w+1 per char. Spaces are skipped. Called with "READY" and "GO!!" (0x41b1cc).
- `FUN_00404940(lo,hi)` → **SortParticlesByDepth**: recursive merge sort of the index array `DAT_004b8fdc[]` using temporaries
  `DAT_00421318` (left), `DAT_004222bc` (right), and `DAT_00423260` (out).
- `FUN_00404a10(nL,nR)` → **MergeParticleRuns**: merge step. It takes the right element when `z[left] <= z[right]`, so the order
  is **descending z** (painter's order). Ties prefer the right half (not stable).

---------------------------------------------------------------------------------------------------
## 9. Proposed names

| function | name | summary |
|---|---|---|
| FUN_004029f0 | `PhysicsStep` | Paddle from mouse + every ball: gravity, repulsors, integrate, resize, paddle, walls, block hits |
| FUN_00401900 | `UpdateItemsAndDebris` | Items (fall/catch/HUD/expiry), debris fragments, ball spawning from red/cyan blocks |
| FUN_004012d0 | `LoadStage` | Reset per-stage state, read stage bitmap → block types, flags, fragments |
| FUN_004046a0 | `BuildParticleText` | Font bitmap → 3-D particle list for READY/GO |
| FUN_00404940 | `SortParticlesByDepth` | Merge sort of particle indices by z |
| FUN_00404a10 | `MergeParticleRuns` | Merge step for the above |
| FUN_0041021c / 0041028c / 004102c0 / 004104e0 | `rand` / `_ftol` / `_CIpow` / `_CIacos` | CRT |

## 10. New globals
| addr | name | meaning |
|---|---|---|
| 0x0041ce58 | `g_ballRadius` | global target radius 4/8/16 (applied to balls lazily) |
| 0x00498438 | `g_gravity` (double) | 0.017, or -0.085 while reversed |
| 0x00498440 | `g_bigTimerMs` | BIG ball effect |
| 0x004baf2c | `g_smallTimerMs` | SMALL ball effect |
| 0x004b8ee8 | `g_reverseTimerMs` | gravity reversal (+5000 per catch) |
| 0x004b8fcc | `g_mugenTimerMs` | infinite balls (+20000 per catch) |
| 0x0049f6a0 | `g_infiniteBalls` | launches do not use stock; no game over |
| 0x004a15ec | `g_paddleHalfW8` | paddle half-width / 8 (default 6, range 3..30) |
| 0x004290c0 | `g_paddleTilt` (double) | smoothed mouse dx, used as degrees in the bounce |
| 0x004290c8 | `g_paddleVy` (double) | ±2.0 / 0 |
| 0x004290d0 | `g_lmbDown` | paddle pressed |
| 0x00425270 | `g_items[]` | item records, count 0x00428f64 |
| 0x0041ce60 | `g_dyingBlocks[]` | indices of blocks in debris/spawn phase, count 0x0049f6a4 |
| 0x004b8fd8 | `g_optShowDebris` | "DISPLAY BROKEN BLOCKS" option |
| 0x0041d478 | `g_blocksRemaining` | (already in NOTES) |
| 0x00421310 | `g_fpsRaw` | unclamped FPS estimate |
| 0x00428f60 | `g_lastTick` | GetTickCount of the previous frame |
| 0x0041bb40 | `g_randSeed` | CRT rand state |
| 0x004a1628 | `g_particles[2000]` | READY/GO particles, count 0x004b8eec, sort index 0x004b8fdc |

## 11. NOTES.md corrections
1. **Neighbour flags are inverted.** Bit set = that side is *covered* by a solid neighbour (or by the wall/ceiling), not "face exposed".
2. **Block record base is 0x4290d8**: state +0, type +4, flags +8, `alive[32]` +0xc, then SoA `fragX[32]` +0x90, `fragY` +0x190, `fragVX` +0x290,
   `fragVY` +0x390. The fragments are not interleaved records. States 4 and 8 exist (see §3).
3. The collision box of block (c,r) is x∈[32c+16,32c+48], y∈[16r+16,16r+32]. 32c+18 / 16r+18 is only the fragment origin.
4. Types 12–15 are **direction-arrow pass-through blocks**, not items. Types 1, 3, 4, 8, 11, 17 are damaged states of 0/2/7/10/16.
   Type 10 (black) is a **repulsor**.
5. Ball `+0x20` is the radius (4/8/16). The paddle half-width is `8*DAT_004a15ec`.
6. Stock `DAT_004b8fc8` is reset to **10 on every stage load**, not just once per game.
7. Timers: `DAT_00498440` big, `DAT_004baf2c` small, `DAT_004b8ee8` reverse gravity, `DAT_004b8fcc` infinite balls.
8. `DAT_0049d278` is `max(fps, 30)`, where fps = frames / seconds over the most recent ≥100 ms of frame times.

## 12. Open questions
- Whether the renderer draws state-8 items or skips them (render scope).
- The initial value of `seg` on the very first octant computation is undefined stack garbage. It matters only for a zero-velocity ball.
