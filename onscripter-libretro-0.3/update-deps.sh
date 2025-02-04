#!/bin/sh
set -eu
rm -rf deps
mkdir -p deps
git submodule update --init


# Get deps tarball from github release.
if [ ! -f deps.tar.xz ]; then
    wget -O deps.tar.xz https://github.com/iyzsong/onscripter-libretro/releases/download/v0.2/libretro-onscripter-deps-20240118.tar.xz
fi

# cp -rv "$(guix build -f deps.scm || kill $$)"/* ./deps/
tar -C deps -xf $(pwd)/deps.tar.xz
chmod -R u+w deps
cp -rv deps.overlay/* ./deps/

# fix some errors for the compiler
sed -i 's#vf, char \*initial#vf, const char *initial#' deps/sdl-mixer/dynamic_ogg.h
sed -i 's#^	return;#	return 0;#' deps/sdl-mixer/music_mad.c
