"""One-off conversion of block130.exe resources into the rebuild's source assets.

    python re/convert_assets.py original/block130.exe assets/

Writes:
  sprites.bmp  the BITMAP resource unchanged (640x272, 8bpp, magenta colour key)
  stages.txt   the DATA resource (50 stages as a colour-coded 4bpp image) as editable text
  block.ico    the application icon
  icon.bmp     the same icon as a 32-bit BMP, for the window icon on macOS and Linux
"""
import pathlib
import struct
import sys

import pefile

# COLORREF (0x00BBGGRR) -> block type, from the stage loader FUN_004012d0
COLOUR_TO_TYPE = {
    0x008080: 0, 0x00FFFF: 1, 0xFF0000: 2, 0x808080: 5, 0x0000FF: 6, 0xFF00FF: 7, 0xFFFF00: 9,
    0x000000: 10, 0x000080: 12, 0x800000: 13, 0x008000: 14, 0x00FF00: 15, 0xC0C0C0: 16,
}
EMPTY = 0xFFFFFF
TYPE_CHARS = "0123456789abcdefg"  # block type n is written as TYPE_CHARS[n]
COLS, ROWS, STAGES = 15, 26, 50


def resources(pe, type_id):
    for t in pe.DIRECTORY_ENTRY_RESOURCE.entries:
        if t.id == type_id:
            for n in t.directory.entries:
                leaf = n.directory.entries[0].data.struct
                yield (str(n.name) if n.name else n.id), pe.get_data(leaf.OffsetToData, leaf.Size)


def dib_to_bmp(dib):
    hdr_size, _, _, _, bpp, _, _, _, _, clr_used = struct.unpack_from("<IiiHHIIiiI", dib)
    ncolors = clr_used or (1 << bpp if bpp <= 8 else 0)
    return b"BM" + struct.pack("<IHHI", 14 + len(dib), 0, 0, 14 + hdr_size + ncolors * 4) + dib


def stage_pixels(dib):
    """Yields a COLORREF accessor for the 4bpp bottom-up DATA bitmap."""
    hdr_size, w, h, _, bpp, _, _, _, _, clr_used = struct.unpack_from("<IiiHHIIiiI", dib)
    assert bpp == 4, bpp
    ncolors = clr_used or 16
    palette = [struct.unpack_from("<BBBx", dib, hdr_size + i * 4) for i in range(ncolors)]
    bits = hdr_size + ncolors * 4
    stride = ((w * 4 + 31) // 32) * 4

    def colorref(x, y):
        row = bits + (h - 1 - y) * stride
        byte = dib[row + x // 2]
        index = byte >> 4 if x % 2 == 0 else byte & 0xF
        b, g, r = palette[index]
        return (b << 16) | (g << 8) | r

    return colorref


def stages_text(dib):
    px = stage_pixels(dib)
    out = [
        "# BLOCK v1.30 stage data, converted from the original DATA resource.",
        "# 50 stages, each 15 columns x 26 rows of 32x16 px blocks.",
        "# '.' = empty; otherwise the character is the block type: 0-9 then a=10 ... g=16.",
        "# Types c, d, e, f (12-15) and 5 do not count towards clearing the stage.",
        "",
    ]
    for s in range(STAGES):
        out.append(f"stage {s + 1}")
        ox, oy = (s % 10) * 16 + 1, (s // 10) * 27 + 1
        for y in range(ROWS):
            line = ""
            for x in range(COLS):
                c = px(ox + x, oy + y)
                if c == EMPTY:
                    line += "."
                elif c in COLOUR_TO_TYPE:
                    line += TYPE_CHARS[COLOUR_TO_TYPE[c]]
                else:
                    raise ValueError(f"stage {s + 1} ({x},{y}): unmapped colour {c:06x}")
            out.append(line)
        out.append("")
    return "\n".join(out)


def icon_file(pe):
    icons = dict(resources(pe, pefile.RESOURCE_TYPE["RT_ICON"]))
    _, group = next(resources(pe, pefile.RESOURCE_TYPE["RT_GROUP_ICON"]))
    _, _, count = struct.unpack_from("<HHH", group)
    entries, images = [], []
    offset = 6 + count * 16
    for i in range(count):
        w, h, colors, _, planes, bpp, size, icon_id = struct.unpack_from("<BBBBHHIH", group, 6 + i * 14)
        data = icons[icon_id]
        entries.append(struct.pack("<BBBBHHII", w, h, colors, 0, planes, bpp, len(data), offset))
        images.append(data)
        offset += len(data)
    return struct.pack("<HHH", 0, 1, count) + b"".join(entries) + b"".join(images)


def main():
    exe, outdir = sys.argv[1], pathlib.Path(sys.argv[2])
    outdir.mkdir(parents=True, exist_ok=True)
    pe = pefile.PE(exe)
    bitmaps = dict(resources(pe, pefile.RESOURCE_TYPE["RT_BITMAP"]))
    (outdir / "sprites.bmp").write_bytes(dib_to_bmp(bitmaps["BITMAP"]))
    (outdir / "stages.txt").write_text(stages_text(bitmaps["DATA"]), encoding="ascii", newline="\n")
    (outdir / "block.ico").write_bytes(icon_file(pe))
    # window icon for macOS / Linux (SDL loads BMP, not ICO)
    from PIL import Image
    Image.open(outdir / "block.ico").convert("RGBA").save(outdir / "icon.bmp")
    print("wrote", ", ".join(p.name for p in sorted(outdir.iterdir())))


if __name__ == "__main__":
    main()
