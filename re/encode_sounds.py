"""Encodes the original wav files into the Ogg Vorbis files built into the game.

usage: python re/encode_sounds.py original/wave assets/sounds

Needs ffmpeg with libvorbis on PATH. Quality 5 (about 100 kbit/s for these mono 44.1 kHz sounds) keeps the
coding noise under the masking threshold while shrinking 2.3 MB of wav to about 340 KB.
"""
import pathlib
import subprocess
import sys

source, target = map(pathlib.Path, sys.argv[1:3])
target.mkdir(parents=True, exist_ok=True)
for wav in sorted(source.glob('*.wav')):
    out = target / (wav.stem + '.ogg')
    subprocess.run(['ffmpeg', '-v', 'error', '-y', '-i', str(wav), '-map_metadata', '-1', '-fflags', '+bitexact',
                    '-flags:a', '+bitexact', '-c:a', 'libvorbis', '-q:a', '5', str(out)], check=True)
    print(f'{wav.name}: {wav.stat().st_size} -> {out.stat().st_size} bytes')
