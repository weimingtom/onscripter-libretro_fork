## About Libretro core for ONScripter

ONScripter is a visual novel games engine compatible to NScripter,
this project provides a libretro core allowing the ONScripter visual
novel games to be played with libretro frontends such as RetroArch.


This project is based on:
- bzip2: https://sourceware.org/bzip2/
- libogg: https://xiph.org/ogg/
- libvorbis: https://xiph.org/vorbis/
- mad: https://www.underbit.com/products/mad/
- stb_truetype: https://github.com/nothings/stb, https://github.com/codewitch-honey-crisis/stb
- SDL, SDL_image, SDL_mixer, SDL_ttf: https://libsdl.org/
- ONScripter: https://github.com/ogapee/onscripter
- sdl-libretro: https://github.com/libretro/sdl-libretro
- libretro-common: https://github.com/libretro/libretro-common
- wuffs: https://github.com/google/wuffs

Thanks them!

## Building

### Linux

    git clone --recursive https://github.com/iyzsong/onscripter-libretro
    cd onscripter-libretro
    ./update-deps.sh
    make
