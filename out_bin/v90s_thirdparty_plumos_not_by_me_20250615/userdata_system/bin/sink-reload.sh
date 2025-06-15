#!/bin/sh

case $1 in
  add)
    USBDAC=`pw-dump | grep -B 5 -A 10 '"media.class": "Audio/Sink"' | grep '"node.name"' | awk -F'"' '{print $4}'|grep -v "effect_input.eq6\|alsa_output._sys_devices_platform_soc_sndcodec_sound_card0.playback.0.0"`
    pactl set-default-sink $USBDAC
    pactl get-default-sink
    ;;
  remove)
    pactl set-default-sink effect_input.eq6
    ;;
esac
