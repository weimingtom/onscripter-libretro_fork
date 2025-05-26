#!/bin/bash

cd /userdata/roms/ports/ons

cp /usr/lib/libretro/onscripter_libretro.so .
cp /usr/lib/libretro/onsyuri_libretro.so .
cp /usr/share/libretro/info/onscripter_libretro.info .
cp /usr/share/libretro/info/onsyuri_libretro.info .

./onscripter > a.txt 2>&1

