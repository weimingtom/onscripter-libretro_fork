#!/bin/sh

case "$1" in
    start)
# Get timezone information from IP and calculate offset
ZONEINFO=$(wget -qO- http://worldtimeapi.org/api/ip)
UTC_OFFSET=$(echo "$ZONEINFO" | grep '"utc_offset"' | cut -d'"' -f4)
OFFSET_HOURS=$(echo "$UTC_OFFSET" | sed 's/^\([+-][0-9][0-9]\):[0-9][0-9]$/\1/' | sed 's/^+//')

# Obtain the current UTC time from Google
DATE_STR=$(wget --server-response --spider http://google.com 2>&1 \
  | grep '^ *Date:' \
  | head -n 1 \
  | cut -d' ' -f5-)

# Convert to local time using the offset and set the system date
LOCAL_DATE=$(date -u -d "$DATE_STR ${OFFSET_HOURS} hour" "+%Y-%m-%d %H:%M:%S")
echo "Setting date to: $LOCAL_DATE"
date -s "$LOCAL_DATE"
hwclock --systohc
sync
;;
esac
