#!/bin/sh

killall -9 pipewire pipewire-pulse pipewire-media-session
sleep 1
/etc/init.d/S06audio restart
sleep 0.5
pactl set-default-sink effect_input.eq6
pactl get-default-sink
# pactl set-default-sink alsa_output._sys_devices_platform_soc_sndcodec_sound_card0.playback.0.0

cp /userdata/system/bin/99-usb-dac.rules /etc/udev/rules.d/
udevadm control --reload
#udevadm trigger

