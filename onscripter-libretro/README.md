## About Libretro core for ONScripter

ONScripter is a visual novel games engine compatible to NScripter,
this project provides a libretro core allowing the ONScripter visual
novel games to be played with libretro frontends such as RetroArch.

This version is based on the ogapee upstream, you may want to use
[OnscripterYuri](https://github.com/YuriSizuku/OnscripterYuri) for Chinese games.



This project is based on:
- bzip2: https://sourceware.org/bzip2/
- zlib: https://zlib.net/
- FreeType: https://www.freetype.org/
- libogg: https://xiph.org/ogg/
- libvorbis: https://xiph.org/vorbis/
- mad: https://www.underbit.com/products/mad/
- (optional) libjpeg-turbo: https://libjpeg-turbo.org/
- (optional) libpng: http://www.libpng.org/
- SDL, SDL_image, SDL_mixer, SDL_ttf: https://libsdl.org/
- ONScripter: https://github.com/ogapee/onscripter
- sdl-libretro: https://github.com/libretro/sdl-libretro
- libretro-common: https://github.com/libretro/libretro-common
- (optional) TinyCoroutine: https://github.com/soundsrc/tinycoroutine

Thanks them!

## Building

### Linux

    git clone --recursive https://github.com/iyzsong/onscripter-libretro
    cd onscripter-libretro
    ./update-deps.sh
    mkdir build; cd build; cmake .. && make
