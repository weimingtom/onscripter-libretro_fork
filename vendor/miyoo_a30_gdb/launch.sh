#!/bin/sh
echo $0 $*
progdir=`dirname "$0"`
cd /mnt/SDCARD/RetroArch/
ulimit -c unlimited
HOME=/mnt/SDCARD/RetroArch/ $progdir/ra32.miyoo -v > /mnt/SDCARD/App/RetroArch32/a.txt 2>&1
