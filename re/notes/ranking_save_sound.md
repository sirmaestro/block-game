# Ranking, name entry, save/load, sound (EZSound)

Scope: `FUN_0040b3f0` (state 0x80), `FUN_0040bb90` (state 0x100), `FUN_0040cbd0` (save), `FUN_0040cef0` (load),
EZSound wrapper 0x40d880–0x40f3f0. Also the ranking-insert code in `FUN_004050a0` (stage clear) and
`FUN_00405f70` (ending), because they feed the tables.

Doubles and strings below were read from `block130.exe` (file offset = VA - 0x400000).
"colour" is the 4th argument of `FUN_004026c0` (text draw). In these screens 0 = normal, 1 = hover / header,
2 = selected / highlighted. The actual RGB values belong to the text renderer, which is not covered here.

---------------------------------------------------------------------------------------------------
## 0. Corrections to NOTES.md

1. **The state labels are swapped.** **0x80 = NAME ENTRY** (`FUN_0040b3f0`, plays sound 17 nameentry), and
   **0x100 = RANKING** (`FUN_0040bb90`, plays sound 16 ranking).
2. **Name entry comes before play, not after the time trial.** MODE SELECT (`FUN_00409d90`) sends both modes to
   0x80: TIME TRIAL sets `DAT_0049d284=1`, and FREE MODE sets `=2` (only if `DAT_0041ce54==1`). OK on the name-entry
   screen then starts stage 0 (state 2). After the time trial (stage 50 cleared → state 0x10 ending), **any non-Esc
   key** goes to state 0x100 ranking (WndProc). That keypress also sets the free-mode-unlocked flag.
   The title menu's second item also opens 0x100.
3. **Free mode also writes per-stage rankings.** The per-stage ranking is updated in `FUN_004050a0` (stage clear,
   phase 0) with no mode check, so free-mode clears are recorded too. Only the TOTAL ranking is time-trial-only,
   because it is updated in the ending.
4. `FUN_0040df10` "stop" is Stop **+ rewind to 0**. `FUN_0040e440` master volume is
   `IDirectSoundBuffer::SetVolume` on the **primary buffer** (hundredths of dB). It is not waveOut directly,
   but see §3.4.
5. Platform-layer note: on WM_KEYDOWN (non-Esc), if `state & 0xF` is non-zero (states 1,2,4,8) the pause window
   opens in TT mode (`DAT_004b8da8=2`) or the stage-select window opens in free mode (`DAT_004b8e50=2`), with
   sound 12. State 0x10 → ranking. Every other state ignores keys. **There is no keyboard text input anywhere.**
6. `DAT_00428f70` sits right after the 8-byte name buffer but is a separate flag: it toggles every 50 ms in
   state 4 (the "NEW RECORD !!" blink).

---------------------------------------------------------------------------------------------------
## 1. Name entry — state 0x80, `FUN_0040b3f0`

### Entry
Reached from MODE SELECT (`DAT_004baf20=0`, `DAT_00421308=0x80`). Phase 0 init:
- stop+play sound **17 (nameentry), looping**
- `g_nameLen (DAT_0041d480) = strlen(g_playerName)`. The name is **pre-filled** with the last name, which is
  loaded from block130.sys or kept from the previous session.
- logo yaw angle `DAT_004b8fd0 = 0.0`, yaw speed `DAT_004b8fc0 = +0.5`
- dot sprites: `DAT_004a15f0[0] = (0x20,0x98)-(0x28,0xA0)`, `[1] = (0x28,0x98)-(0x30,0xA0)` (8x8)
- phase = 1 ("rebuild logo")

### Per frame (draw order)
1. Background: sprite (0x80,0x90)-(0x90,0xA0), 16x16, tiled over the whole 640x480 screen.
2. **Character grid**: 3 rows x 32 columns. Row r = 0..2 at y = 288 + 16r. Column c = 0..31.
   char = 0x20*(r+1) + c, skipping 0x20 (space) and 0x7F. That gives **all printable ASCII 0x21..0x7E** (94 glyphs):
   - row 0: `!"#$%&'()*+,-./0123456789:;<=>?` (c=1..31)
   - row 1: `@A..Z[\]^_`
   - row 2: `` `a..z{|}~ ``
   - Text x = (36c + 82 - textWidth)/2 (centred on x = 41 + 18c), y = 288 + 16r.
   - Hit box (inclusive-left/top): `32+18c <= mx < 50+18c` and `288+16r <= my < 304+16r`.
   - colour 1 when hovered, else 0.
3. Click on a char (hover and `DAT_004290d0` "LMB pressed" flag set): if `len < 7`, append the char, play **sound 12**
   (open), and set phase=1 (rebuild logo). Otherwise play **sound 10** (error). Either way clear `DAT_004290d0`,
   so each press fires once. Because the press flag stays set until it is consumed or the button is released,
   pressing on empty space and dragging onto a key also fires it.
4. Buttons. Row test is `row*16 < my < row*16+16` (both strict), with **no x test** (the whole screen width):
   | button | row | text y | action |
   |---|---|---|---|
   | `SPACE` | 22 | 352 | len<7: append ' ', sound 12, rebuild; else sound 10 |
   | `BACK SPACE` | 24 | 384 | len>0: name[len-1]=0, len--, sound 12, rebuild; else sound 10 |
   | `OK` | 27 | 432 | see below |
   Each label is centred at x=320, colour 1 when hovered, else 0.
   **OK**: stop 17, play **14** (change). Then `stage=0`, all `g_stageRankThisRun[50]=10`, `g_totalMs (DAT_0041d47c)=0`,
   `g_totalRankThisRun=10`, `FUN_004012d0()` (load stage), and **state = 2** (stage intro). **An empty name is
   accepted.** Phase is not reset here, so the stage intro handler presumably resets it. Not checked.
5. 3D "logo" of the current name, made of dots (shared 3D-text system `FUN_004046a0` / `FUN_00404940`, owned elsewhere):
   - Rebuild (phase 1 → 2): `point count DAT_004b8eec=0; FUN_004046a0(name)`. Rotate every point about X by 20°
     (`_DAT_004193a8`=0.349066 rad, which mixes y/z), then about Y by the current yaw (deg).
   - Each frame: if yaw > 30 → speed = -0.5. Else if yaw < -30 → speed = +0.5. Then
     `d = speed*200/fps` degrees (`_DAT_00419230`=200, fps = `DAT_0049d278`), yaw += d, and all points are rotated
     about Y by d. Net effect: the name swings ±30° at 100°/s.
   - Painter-sort the indices (`FUN_00404940`), then blit the 8x8 dot sprite `[pt.spriteIdx]` at
     `x = 316 - ftol(-1000*X/(Z+1800))`, `y = 172 - ftol(1000*Y/(Z+1800))`.
     Point record: 0x30 bytes at 0x4a1628, with X,Y,Z doubles at +0,+8,+0x10 and the sprite index int at +0x28.
6. Title `NAME ENTRY` centred, y=16, colour 2. Prompt `Enter Your Name (MAX 7 Characters) and Click 'OK' !!`
   centred, y=48, colour 0.
7. Mouse cursor sprite (0x70,0x90)-(0x80,0xA0) at the cursor position (GetCursorPos, full-screen so screen = client).

The typed name is only shown as the 3D dot logo. There is no flat text field.
Timings: none (no timeout). The only time-based thing is the logo swing.

**Hazard:** `$` (0x24) can be selected, but it is the field separator in both save files (§2). A name containing
`$` corrupts parsing of block130.sys and block130.dat on the next start. The rewrite should either exclude `$`
or escape it, and say which in the code.

---------------------------------------------------------------------------------------------------
## 2. Ranking tables (data model)

Record (0x20 bytes, 8 dwords):
```
+0x00 int timeMs        (clear time in milliseconds)
+0x04 int year          (SYSTEMTIME.wYear, from GetLocalTime at insertion)
+0x08 int month
+0x0C int day
+0x10 int hour
+0x14 int minute
+0x18 char name[8]      (7 chars + NUL)
```
- `g_stageRanking[50][10]` at **0x41d488** (stage-major: index = stage*10 + rank, stride 0x140 per stage)
- `g_totalRanking[10]` at **0x428f78**
- Default/empty entry: `timeMs = 5999999` (shows as `99m59s99`), date fields 0, name `"NoEntry"`.

**Insertion** (stage clear: `t = DAT_004251a0[stage]`. Ending: `t = DAT_0041d47c` total):
```
i = 0; while (i < 10 && table[i].timeMs <= t) i++;   // ties go BELOW existing entries
if (i == 10) rankThisRun = 10 (not ranked)
else { shift entries i..8 down one (entry 9 dropped); table[i] = {t, now.Y,M,D,h,m, g_playerName}; rankThisRun = i; }
```
- Per stage: `g_stageRankThisRun[stage] (0x4b8ef4)` is set to 10 first, then to i. The stage-clear screen shows
  `NEW RECORD !!` (blinking) when the rank is 0.
- Total: `g_totalRankThisRun (0x49d298)`. Set in ending phase 0. The ending also starts sound 15 (looped).
- Both "this run" ranks are reset to 10 at init, at name-entry OK, and at RESET YOUR DATA. When the ranking is
  opened from the title they still hold the values from the last run, so those rows stay highlighted.

Time text format `%2.2dm%2.2ds%2.2d`: minutes = t/60000, seconds = (t%60000)/1000, centiseconds = (t%1000)/10.
Minutes are not clamped (`%2.2d` widens past 99).

---------------------------------------------------------------------------------------------------
## 3. Ranking screen — state 0x100, `FUN_0040bb90`

### Entry (phase 0)
From the ending (keypress), or from the title menu item that stops sound 1 and plays sound 12.
- `g_rankingViewMode (DAT_0049d280) = 1` (**STAGE TIME view first**), `g_rankingStage (DAT_004baf28) = 0`
- play **sound 16 (ranking), looping**. There is no stop first. Sound 16 is stopped on EXIT.
- logo: `DAT_004b8eec=0`, yaw speed = **-0.2** (`0xbfc999999999999a`), camera distance `DAT_0041ce48 = 1500.0`.
  Dot sprites `[0]=(0x20,0x90)-(0x28,0x98)`, `[1]=(0x28,0x90)-(0x30,0x98)`.
- builds a 3D ring logo "RANKING" from the 7 one-letter strings R,A,N,K,I,N,G (0x41b684..0x41b670). For letter k:
  `FUN_004046a0(letter)`. On the new points only: rotate about X by 30° (0.5236 rad), Z -= 220, rotate about Y
  by `ang`, Y -= 300. Then (except after the last letter) `ang += (width(next)+width(cur))*1.2` degrees
  (`_DAT_00419408`=1.2, `_DAT_00419418`=220, `_DAT_00419410`=300).

### Per frame
1. Background: same 16x16 tile (0x80,0x90) over the full screen.
2. Logo: rotate all points about Y by `-0.2*200/fps` degrees (-40°/s, continuous), depth-sort, then draw at
   `x = 444 - ftol(-1000*X/(Z+1500))`, `y = -136 - ftol(1000*Y/(Z+1500))` (top right of the screen).
3. **STAGE TIME view (mode 1):**
   - Stage preview: frame tile (0xB0,0x90)-(0xC0,0xA0) tiled for x=16..240 and y=16..208 (step 16). Then the
     `DATA` bitmap is loaded with LoadImage **every frame** and read with GetPixel at stage `g_rankingStage`
     (same layout as NOTES: x = (s%10)*16+1+c, y = (s/10)*27+1+r). Each cell c=0..14, r=0..25 is drawn as a
     16x8 mini-block at screen (16+16c, 16+8r) from sprite ((idx+15)*16, 0xA8)-((idx+16)*16, 0xB0). Colour → idx:
     | COLORREF | idx | | COLORREF | idx |
     |---|---|---|---|---|
     | 0x008080 olive | 0 | | 0x000000 black | 7 |
     | 0x00ffff yellow | 1 | | 0x000080 maroon | 8 |
     | 0xff0000 blue | 2 | | 0x800000 navy | 9 |
     | 0x808080 grey | 3 | | 0x008000 dkgreen | 10 |
     | 0x0000ff red | 4 | | 0x00ff00 green | 11 |
     | 0xff00ff magenta | 5 | | 0xc0c0c0 silver | 12 |
     | 0xffff00 cyan | 6 | | other (white) | not drawn |
   - Table for stage `g_rankingStage` (see layout below). The highlighted row is `g_stageRankThisRun[stage]`.
4. **TOTAL TIME view (mode 0):** no preview. Table from `g_totalRanking`, highlighted row = `g_totalRankThisRun`.
5. Table layout (both views):
   - header row y=240, colour 1: `RANK` x=80, `TIME` x=144, `NAME` x=272, `DATE` x=384 (left-aligned x)
   - rows i=0..9 at y = 256 + 16i: `%2.2d` (01..10) at x=90, time at x=144, name at x=272,
     date `%4.4d/%2.2d/%2.2d %2.2d:%2.2d` at x=384. Colour 2 if i == highlighted rank, else 0.
     Defaults show as `0000/00/00 00:00`.
6. Buttons. Row test `row*16 < my < row*16+16` (strict). Hover → colour 1:
   | # | label | text pos (centre x, y) | row | x range (strict) | action |
   |---|---|---|---|---|---|
   | 0 | `TOTAL TIME` | 448, 160 | 10 | 256 < mx < 640 | mode=0, sound 12 |
   | 1 | `STAGE TIME` | 448, 192 | 12 | 256 < mx < 640 | mode=1, sound 12 |
   | 2 | `PREVIOUS` (mode 1 only) | 136, 160 | 10 | 16 < mx < 256 | stage-- (wraps 0→49), sound 12 |
   | – | `%d` stage number (stage+1), colour 2 (mode 1 only) | 136, 176 | – | – | – |
   | 3 | `NEXT` (mode 1 only) | 136, 192 | 12 | 16 < mx < 256 | stage++ (wraps 49→0), sound 12 |
   | 4 | `EXIT` | 320, 448 | 28 | any | stop 14+play 14 (change), stage=0, mode=0, phase=0, **state=0x40 (title)**, stop 16 |
   The currently selected view's label (TOTAL TIME or STAGE TIME) is drawn in colour 2, or 1 while hovered.
   Each click clears `DAT_004290d0`, except EXIT, which does not, so the press may carry into the title.
   PREVIOUS/NEXT are ignored in mode 0. Their hover is still computed, but they are not drawn.
7. Cursor sprite (0x70,0x90) at the mouse position.

No timers and no auto-exit.

---------------------------------------------------------------------------------------------------
## 4. Save / load

Both files are in the current directory and use MSVC old-iostream text mode: `ofstream(name, ios::out=2, openprot)`
and `ifstream(name, ios::in|ios::nocreate = 0x21)`. The content is a single line with no newline. Every field
ends with `$`. **The writer adds one 0x00 byte at the end of each file.**

### 4.1 block130.sys — `"%d$%d$%d$"` + name + `"$"` + `\0`
| # | field | global | meaning | default (no file) |
|---|---|---|---|---|
| 1 | volume | `_DAT_004290b8` (double; ftol on save) | master volume slider 0..128 | 64 |
| 2 | show broken blocks | `DAT_004b8fd8` | 1 = ON (fragment animation), 0 = OFF (option "DISPLAY BROKEN BLOCKS") | 1 |
| 3 | free mode unlocked | `DAT_0041ce54` | 1 after the time-trial ending | 0 |
| 4 | player name | `DAT_00428f68` (char[8]) | last name entered; pre-fills name entry | `""` |

Example `block130.sys` = `64$1$0$$\0` (9 bytes) = the defaults exactly.

### 4.2 block130.dat — 510 records of `"%d$%d$%d$%d$%d$%d$"` + name + `"$"`, then `\0`
- Records 0..499: `g_stageRanking`, stage-major (stage 0 ranks 1..10, stage 1 …).
- Records 500..509: `g_totalRanking`, ranks 1..10.
- Fields: `timeMs $ year $ month $ day $ hour $ minute $ name $`. The time is in ms. The date is the local time
  when the record was set (minute resolution). There is no per-stage "best time" outside these tables: the best
  time is rank 0 of each stage.
- Default record `5999999$0$0$0$0$0$NoEntry$` (26 bytes). All defaults → 510*26 + 1 = **13261 bytes**.
- Example `block130.dat` checked: 13261 bytes, 3570 `$`, all 510 records equal the default, and it ends with
  0x00. So both example files are pristine (no game ever completed).

### 4.3 Load details (`FUN_0040cef0`, called first thing in init `FUN_00401040`)
- **.dat missing:** every entry = default (5999999 / zeros / "NoEntry").
- **.dat present:** first zero the int fields (names untouched). Then for each record, read chars up to `$` and
  parse the field as an unsigned decimal: `value += digit * 10^(len-1-i)` with `digit = c - '0'`
  (`FUN_004102c0` = `_CIpow`).
  - **There is no sign or validation.** A `-` gives a garbage digit (-3).
  - The name is read up to `$` and copied with an unbounded strcpy into the 8-byte slot. A name longer than 7
    chars overflows into the next record. Its int fields are *added to* by the parse, so they would be corrupted.
- **EOF/short file (likely, not verified):** old-iostream `get(char&)` leaves the char unchanged on failure.
  The previous char was `$`, so every remaining field parses as empty → **time 0** and name `""`.
  A time of 0 would make that rank unbeatable. The rewrite should validate the input and fall back to defaults.
- **.sys missing:** volume 64.0, broken=1, free=0, name `""`. **.sys present:** parse the 3 ints the same way, and
  the name into `g_playerName` (also unbounded).
- After loading, init saves the current primary volume (`DAT_0041ce40 = FUN_0040e460()`) and applies the master
  volume (§5.4). It then loads the 20 sounds.

### 4.4 Save (`FUN_0040cbd0`)
Called on WM_DESTROY (Esc, or the window closing) before the primary volume is restored, DirectDraw is released,
and sound shuts down. Writes .sys and then .dat in the formats above, overwriting both. There is no save at any
other time, so a crash loses the whole session.

### 4.5 RESET YOUR DATA (options, `FUN_00407b60` item 0, after "Really?" OK)
Plays sound 14. Sets broken=1, volume=64.0, name="", free-mode unlocked=0, and all 510 records to default.
Sets master volume from 0.5^0.1 (i.e. vol 64), and all "this run" ranks to 10. It does not write the files;
that happens on exit.

---------------------------------------------------------------------------------------------------
## 5. Sound — EZSound wrapper (DirectSound)

### 5.1 Init / shutdown
- `FUN_0040d880(hwnd, 22050, 8, 1, 32)` is __stdcall. The call is from WinMain: rate 22050 Hz, 8-bit, mono,
  32 sample slots. It loads winmm and ole32 and dsound.dll dynamically, then DirectSoundEnumerate,
  CoInitialize, CoCreateInstance(CLSID_DirectSound), Initialize(NULL), and SetCooperativeLevel(hwnd,
  **DSSCL_PRIORITY=2**). It creates the primary buffer (`DSBCAPS_PRIMARYBUFFER|CTRLVOLUME` = 0x81) and SetFormat
  to 22050/8/mono, callocs 32 x 0x2C slot records, and calls `timeBeginPeriod(min)`. On failure it shows a
  MessageBox "EZSound Error" and returns 0. The game ignores the result. All later calls are then no-ops,
  because the slot count is 0.
- `FUN_0040da80` shutdown: releases everything. Bug: it calls `timeBeginPeriod` again instead of `timeEndPeriod`.
  This is harmless.

### 5.2 API the game uses
| fn | proposed name | semantics |
|---|---|---|
| `FUN_0040db50(id, name)` | `Snd_Load` | Tries a `"WAVE"` resource called `name` first, then the file `name` (e.g. `wave/block.wav`). PCM only (formatTag 1). Skips an optional `fact` chunk; expects `data` immediately after. Creates one static secondary buffer per id with flags `0x100E8` = CTRLFREQUENCY\|CTRLPAN\|CTRLVOLUME\|LOCSOFTWARE\|GETCURRENTPOSITION2 (+GLOBALFOCUS if `DAT_004bba78`, which stays 0). Returns 0 if the slot is already loaded or out of range. |
| `FUN_0040e3b0(id, vol)` | `Snd_SetVolume` | `IDirectSoundBuffer::SetVolume`. **Units: hundredths of a dB of attenuation** (0 = unity, -10000 = silent). Confirmed. Linear gain = 10^(vol/2000). |
| `FUN_0040de80(id, loop)` | `Snd_Play` | `Play(0,0, loop ? DSBPLAY_LOOPING : 0)` |
| `FUN_0040df10(id)` | `Snd_Stop` | `Stop()` + `SetCurrentPosition(0)` (rewind) |
| `FUN_0040e440(mB)` | `Snd_SetMasterVolume` | primary buffer `SetVolume(mB)` |
| `FUN_0040e460()` | `Snd_GetMasterVolume` | primary buffer `GetVolume`. Returns the value (Ghidra's pointer return type is wrong; the disassembly returns the local). Returns 1 if there is no primary buffer. |
| `FUN_0040d880`, `FUN_0040da80` | `Snd_Init`, `Snd_Shutdown` | see above |

Per-sound volumes set at load (everything else is 0): 0 block **-500**, 2 ball **-1200**, 3 pad **-1200**,
7 block2 **-200**, 8 big **-500**, 9 small **-500**.
Gains: -200 → 0.794, -500 → 0.562, -1200 → 0.251.
Files: `wave/<name>.wav` for the 20 ids in NOTES (e.g. `wave/ranking.wav`, `wave/nameentry.wav`).

### 5.3 Playback semantics for the SDL3 port
- **One buffer per id, so a sound never overlaps itself.** Different ids mix freely.
- Calling Play on a buffer that is already playing does **not** restart it in DirectSound; it keeps playing from
  where it is. But the game almost always calls `Stop(id)` (which rewinds) right before `Play(id)`. Effectively,
  **replaying a sound cuts it off and restarts it from the start.** Model it as one voice per id with
  restart-on-play.
- Loop flag 1 is used for BGM-style sounds: title (1), bgm (5), ending (15), ranking (16), nameentry (17), and
  probably mugen (18) (check the caller).
- **No pan or frequency changes are used.** SetPan and SetFrequency exist (unlisted 0x40e290 and 0x40e320) but
  nothing calls them.
- The primary format is 22050 Hz / 8-bit / mono, so the original's output was downmixed and quantised to that.
  Matching this is optional.

### 5.4 Master volume
- The slider value `_DAT_004290b8` is 0..128. The options window ADJUST VOLUME (`FUN_0040a120`) sets it while the
  mouse is held on row 4: `vol = clamp(mx - (winX*8 + 64), 0, 128)`. The value is continuous while dragging.
  The knob is drawn at `vol + 64 + winX*8`. Labels are `MIN` / `MAX`. `TEST` plays sound 10.
- Applied as **`mB = (int)(-10000 * (1 - (vol/128)^0.1))`** (constants `_DAT_00419218`=1/128,
  `_DAT_00419210`=0.1, `_DAT_00419208`=1.0, `_DAT_00419200`=-10000). Sample values:
  vol 128 → 0, 64 → -670, 32 → -1294, 1 → -3844, 0 → -10000 (silent).
- This is the **primary buffer** volume. On Win9x/2000-era DirectSound, the primary-buffer volume is tied to the
  system **wave-out mixer volume**. That is why the game saves the original value at startup (`DAT_0041ce40`) and
  restores it on WM_DESTROY. I treat this as "effectively the waveOut volume", but that behaviour belongs to the
  OS/driver and is not visible in this code.
- For SDL3: use a master gain of `10^(mB/2000)` (vol 64 → 0.462), multiplied by the per-sound gain. Treat vol 0 as
  mute. Do not touch the OS volume.

### 5.5 Other functions in 0x40d850–0x40f3f0 (one line each)
| addr | proposed name | purpose |
|---|---|---|
| `FUN_0040ced0` | `ofstream_dtor_thunk` | ofstream destructor via virtual-base adjust (+8), used by save |
| `FUN_0040d850` | `ifstream_dtor_thunk` | ifstream destructor (+0xC), used by load |
| `FUN_0040ddd0` | `Snd_Unload(id)` | stop, free the name copy, release the buffer |
| `FUN_0040de50` | `Snd_UnloadAll` | Snd_Unload for every slot |
| `FUN_0040e0f0` | `Stream_Close` | stop the stream, release the stream buffer, close the file (stream API unused by the game) |
| `FUN_0040e240` | `Stream_Stop` | Stop + timeKillEvent + seek the file back to the data start |
| `FUN_0040e2d0` | `Snd_GetPan(id)` | GetPan (unused) |
| `FUN_0040e360` | `Snd_GetFrequency(id)` | GetFrequency (unused) |
| `FUN_0040e3f0` | `Snd_GetVolume(id)` | GetVolume (unused) |
| `FUN_0040e6a0` | `Snd_CreatePrimary` | create the primary buffer and SetFormat(rate,bits,ch); also GetFormat into 0x4bba40 |
| `FUN_0040e7b0` | `Snd_Fatal(fmt,…)` | sprintf, shut sound down, MessageBox "EZSound Error", return 0 |
| `FUN_0040e800` | `Stream_TimerProc` | double-buffer refill callback for streamed WAV (fills silence at EOF / loops). Unused by the game |
| `FUN_0040ec10` / `FUN_0040ecf0` | `Ole32_Load` / `Ole32_Unload` | refcounted LoadLibrary of ole32 (CoInitialize/CoUninitialize/CoCreateInstance) |
| `FUN_0040ed20` / `FUN_0040ef40` | `Winmm_Load` / `Winmm_Unload` | refcounted LoadLibrary of winmm (time*, joy* procs) |
| `FUN_0040ef70` | `Wav_ParseResource` | parse RIFF/WAVE in a locked resource; fills the 9-dword wave info (WAVEFORMATEX, dataOffset, dataSize, isResource=1, dataPtr) |
| `FUN_0040f0d0` | `Wav_LoadFile` | parse the header (f1c0), malloc, and read the data chunk |
| `FUN_0040f190` | `Wav_Free` | free the data if it was malloc'd (not a resource) |
| `FUN_0040f1c0` | `Wav_ParseFileHeader` | `_open(O_BINARY)`, parse RIFF/fmt/(fact)/data headers |
| `FUN_0040f3a0` | `Wav_Error` | OutputDebugString(message) and close the fd. Bug: it also closes fd 0 when called from the resource path |
| unlisted 0x40ded0 | `Snd_Pause(id)` | Stop without rewind (unused) |
| unlisted 0x40df60 | `Stream_Open` | open a WAV for streaming (unused) |
| unlisted 0x40e140, 0x40e200 | `Stream_Play` / `Stream_*` | stream control (unused; not analysed) |
| unlisted 0x40e290 / 0x40e320 | `Snd_SetPan` / `Snd_SetFrequency` | (unused) |
| unlisted 0x40e490 / 0x40e540 | `Snd_GetPosMs` / `Snd_SetPosMs` | position in ms via Get/SetCurrentPosition and frequency (unused) |
| unlisted 0x40e670 | `Snd_GetDS` | returns the IDirectSound* (unused) |
| `LAB_0040eb90` | `DSEnumCallback` | DirectSoundEnumerate callback |
| `FUN_004102c0` (CRT) | `_CIpow` | x87 pow(st1, st0) |

---------------------------------------------------------------------------------------------------
## 6. Function names (scope)
| addr | name | summary |
|---|---|---|
| `FUN_0040b3f0` | `NameEntry_Frame` | state 0x80: mouse-only 94-char grid, SPACE/BACK SPACE/OK, 3D name logo; OK → stage 0 |
| `FUN_0040bb90` | `Ranking_Frame` | state 0x100: per-stage / total top-10 tables, stage preview, 3D "RANKING" ring, EXIT → title |
| `FUN_0040cbd0` | `SaveData` | write block130.sys and block130.dat |
| `FUN_0040cef0` | `LoadData` | read both files or apply defaults |
| (others) | see §5 | |

## 7. New globals
| addr | name | meaning |
|---|---|---|
| 0x428f68 | `g_playerName[8]` | current player name (7 chars + NUL); saved in .sys |
| 0x41d480 | `g_nameLen` | name length during name entry |
| 0x428f70 | `g_blinkFlag` | toggles every 50 ms in state 4 (NEW RECORD blink) |
| 0x41d488 | `g_stageRanking[50][10]` | 0x20-byte records (§2) |
| 0x428f78 | `g_totalRanking[10]` | 0x20-byte records |
| 0x4b8ef4 | `g_stageRankThisRun[50]` | rank 0..9 achieved this run, 10 = none |
| 0x49d298 | `g_totalRankThisRun` | 0..9, 10 = none |
| 0x49d280 | `g_rankingViewMode` | 1 = STAGE TIME, 0 = TOTAL TIME |
| 0x4baf28 | `g_rankingStage` | stage shown in the ranking (0..49); also the stage-select cursor elsewhere |
| 0x4290b8 | `g_volume` (double) | master volume slider 0..128 |
| 0x4b8fd8 | `g_showBrokenBlocks` | fragment animation option |
| 0x41ce54 | `g_freeModeUnlocked` | set by the time-trial ending |
| 0x41ce40 | `g_origPrimaryVolume` | primary volume at startup, restored on exit |
| 0x4baf44 | `g_emptyString` | BSS "" used as the default name |
| 0x4b8fd0 / 0x4b8fc0 | `g_logoYaw`, `g_logoYawSpeed` (doubles) | 3D dot-text yaw (deg) and speed |
| 0x41ce48 | `g_logoCamDist` (double) | projection distance for the ranking logo (1500); animated in stage clear |
| 0x4b8eec | `g_logoPointCount` | dot count |
| 0x4a1628 | `g_logoPoints[]` | 0x30 stride: X,Y,Z doubles, spriteIdx int at +0x28 |
| 0x4b8fdc | `g_logoSortIdx[]` | painter-sort index array |
| 0x4a15f0 | `g_logoDotRects[]` | RECTs (0x10 each) of the dot sprites |
| 0x4bba68 | `g_pDS` | IDirectSound* |
| 0x4bba6c | `g_pDSPrimary` | primary buffer |
| 0x4bba70 | `g_sndSlots` | 32 x 0x2C: +0 buffer*, +4 malloc'd name, +8 wave info (9 dwords) |
| 0x4bba74 | `g_sndSlotCount` | 32 (0 if init failed) |
| 0x4bba78 | `g_sndGlobalFocus` | 0 |
| 0x4bba7c/80/84 | primary rate / bits / channels | 22050 / 8 / 1 |
| 0x4bba38 | `g_timerPeriod` | from timeGetDevCaps |
| 0x4bba24, 0x4bb9f8 | stream fd / stream buffer | unused stream API |

## 8. Open / ambiguous
- The RGB values of colours 0/1/2 (text renderer).
- How `FUN_004046a0` builds the dot glyphs, and what `FUN_00404940` sorts by (assumed Z, painter's).
- EOF behaviour on a truncated .dat (§4.3) is inferred from old-iostream semantics. It was not traced into the CRT.
- Whether primary-buffer SetVolume really changes the OS wave volume depends on the OS/driver.
- The stage intro (state 2) handler presumably resets the phase after name-entry OK. Not checked here.
