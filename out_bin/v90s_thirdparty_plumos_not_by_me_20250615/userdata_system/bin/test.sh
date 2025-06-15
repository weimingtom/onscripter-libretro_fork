#!/bin/sh
#
# Starts audio services with PipeWire and pipewire-pulse
#

. /etc/profile.d/xdg.sh
. /etc/profile.d/dbus.sh

BOARD=$(cat /boot/boot/batocera.board)

XDG_RUNTIME_DIR="/run/user/1000"
FLAG="/var/run/pipewire.pid"

start_dbus_session() {
    # Check if DBus session is alive for batocera user
    if ! su - batocera -c 'dbus-send --session --dest=org.freedesktop.DBus --type=method_call --print-reply /org/freedesktop/DBus org.freedesktop.DBus.ListNames' >/dev/null 2>&1; then
        echo "Starting new DBus session bus for batocera user..."
        su - batocera -c "dbus-launch --sh-syntax > /tmp/dbus_env_batocera"
    fi
    # Load the environment variables exported by dbus-launch
    . /tmp/dbus_env_batocera
}

start_pipewire() {
    echo "Preparing runtime directory for batocera user..."
    mkdir -p "$XDG_RUNTIME_DIR"
    chown batocera:batocera "$XDG_RUNTIME_DIR"
    chmod 700 "$XDG_RUNTIME_DIR"

    start_dbus_session

    echo "Starting pipewire and pipewire-pulse as batocera user..."
    su - batocera -c "
        export XDG_RUNTIME_DIR=$XDG_RUNTIME_DIR
        export DBUS_SESSION_BUS_ADDRESS=$DBUS_SESSION_BUS_ADDRESS
        /usr/bin/pipewire > /tmp/pipewire.log 2>&1 &
        /usr/bin/pipewire-pulse > /tmp/pipewire-pulse.log 2>&1 &
    "

    echo -n "Waiting for PipeWire sinks..."
    N=0
    while [ $N -lt 100 ]; do
        su - batocera -c "
            export XDG_RUNTIME_DIR=$XDG_RUNTIME_DIR
            export DBUS_SESSION_BUS_ADDRESS=$DBUS_SESSION_BUS_ADDRESS
            pactl list sinks
        " 2>/dev/null | grep -q 'Name:' && { echo " OK"; return 0; }

        echo -n "."
        sleep 0.3
        N=$((N+1))
    done

    echo " FAIL"
    echo "Check /tmp/pipewire.log and /tmp/pipewire-pulse.log for errors."
    return 1
}

stop_pipewire() {
    echo "Stopping pipewire and pipewire-pulse..."
    start-stop-daemon -K -q -p "$FLAG"
    killall pipewire pipewire-pulse 2>/dev/null
    echo "OK"
}

case "$1" in
    start)
        alsactl init # initialize ALSA cards
        start_pipewire
        ;;
    stop)
        stop_pipewire
        ;;
    restart|reload)
        stop_pipewire
        start_pipewire
        ;;
    *)
        echo "Usage: $0 {start|stop|restart}"
        exit 1
        ;;
esac

exit $?

