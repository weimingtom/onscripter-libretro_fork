#!/bin/sh

. /etc/profile.d/xdg.sh
. /etc/profile.d/dbus.sh

export SDL_GAMECONTROLLERCONFIG="19000000330100009011000000000000,adc_gamepad,platform:Linux,a:b0,b:b1,dpdown:h0.4,lefttrigger:b6,dpleft:h0.8,rightshoulder:b5,leftshoulder:b4,righttrigger:b7,dpright:h0.2,back:b8,start:b9,dpup:h0.1,x:b2,y:b3,"

PYXEL_DIR="/userdata/system/.config/.pyxel"
PYXEL_BIN="/userdata/system/.local/bin/pyxel"
ROM="${1}"
EXTENSION=`echo "${ROM}" | awk -F. '{print $NF}'`
ROMNAME=`basename "${ROM}" | awk -F. '{print $1}'`

if [ "${EXTENSION}" = "py" ]; then
  "${PYXEL_BIN}" run "${ROM}"
elif [ "${EXTENSION}" = "pyxapp" ]; then
  "${PYXEL_BIN}" play "${ROM}"
elif [ "${EXTENSION}" = "edit" ]; then
  mkdir -p "${PYXEL_DIR}"/save
  "${PYXEL_BIN}" edit "${PYXEL_DIR}"/save/"${ROMNAME}".pyxres
  sync
else
  exit 0
fi
