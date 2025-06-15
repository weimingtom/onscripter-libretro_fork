#!/bin/sh
case "$1" in
    start)
chmod -R 755 /userdata/system/bin/
mount -o remount,rw /userdata/roms
mkdir -p /userdata/roms/pyxel
mkdir -p /userdata/roms/odcommander/
mkdir -p /userdata/roms/ports
cp /userdata/system/bin/PortMaster.sh /userdata/roms/ports/
rsync -av /userdata/system/bin/odcommander/ /userdata/roms/odcommander/
/etc/init.d/S91smb restart

if [ ! -d "/storage" ] ; then
  cd /
  ln -sf userdata storage
fi

if [ ! -d "/roms" ] ; then
  cd /
  ln -sf userdata/roms/ roms
fi

# Set the root password to "linux"
/userdata/system/bin/S35securepasswd start
sync

;;
esac

