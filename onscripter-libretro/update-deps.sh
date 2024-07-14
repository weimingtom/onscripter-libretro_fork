#!/bin/sh
set -eu
rm -rf deps
mkdir -p deps
git submodule update --init


# Get deps tarball from github release.
if [ ! -f deps.tar.xz ]; then
    wget -O deps.tar.xz https://github.com/iyzsong/onscripter-libretro/releases/download/v0.1/libretro-onscripter-deps-20230212.tar.xz
fi

# cp -rv "$(guix build -f deps.scm || kill $$)"/* ./deps/
tar -C deps -xf $(pwd)/deps.tar.xz
chmod -R u+w deps
cp -rv deps.overlay/* ./deps/
