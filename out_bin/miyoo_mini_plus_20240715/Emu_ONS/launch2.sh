#!/bin/sh
echo $0 $*
progdir=`dirname "$0"`
filename=${1##*/}
TMP1=${filename%.*}
EMU="onscripter_libretro.so"

RA_DIR=/mnt/SDCARD/RetroArch
cd $RA_DIR/
HOME=$RA_DIR/ $RA_DIR/ra32.ss -v -L $RA_DIR/.retroarch/cores/$EMU "/mnt/SDCARD/Roms/ONS/tukihime/0.txt"
