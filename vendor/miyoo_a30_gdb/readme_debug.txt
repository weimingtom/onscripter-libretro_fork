$ sudo apt install libncurses5
$ /home/wmt/work_a30/gcc-linaro-7.5.0-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gdb
$ /home/wmt/work_a30/gcc-linaro-7.5.0-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gdb ra32.miyoo ra32.miyoo.5616343.1146.11.core 
(gdb) set solib-search-path .
(gdb) core-file ra32.miyoo.5616343.1146.11.core 

$ /home/wmt/work_a30/gcc-linaro-7.5.0-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gdb ra32.miyoo ra32.miyoo.5618583.1148.11.core

$ set sysroot /home/wmt/work_a30/staging_dir/target/
$ set sysroot /home/wmt/work_a30/gcc-linaro-7.5.0-arm-linux-gnueabihf/arm-linux-gnueabihf/libc/usr/lib/

(gdb) info sharedlibrary



(gdb) info sharedlibrary
From        To          Syms Read   Shared Object Library
                        No          /lib/libdl.so.2
                        No          /lib/librt.so.1
                        No          /usr/lib/libMali.so
                        No          /usr/lib/libz.so.1
                        No          /usr/lib/libasound.so.2
                        No          /lib/libpthread.so.0
                        No          /mnt/SDCARD/miyoo//lib/libSDL-1.2.so.0
                        No          /mnt/SDCARD/miyoo//lib/libtmenu.so
                        No          /mnt/SDCARD/miyoo//lib/libSDL_ttf-2.0.so.0
                        No          /mnt/SDCARD/miyoo//lib/libSDL_image-1.2.so.0
                        No          /mnt/SDCARD/miyoo//lib/libSDL_mixer-1.2.so.0
                        No          /usr/lib/libtinyalsa.so.1
                        No          /lib/libmad.so.0
                        No          /usr/lib/libfreetype.so.6
                        No          /usr/lib/libbz2.so.1.0
                        No          /lib/libstdc++.so.6
                        No          /lib/libm.so.6
                        No          /lib/libgcc_s.so.1
                        No          /lib/libc.so.6
                        No          /lib/ld-linux-armhf.so.3
--Type <RET> for more, q to quit, c to continue without paging--
0xb2fb81a0  0xb31e1c94  Yes         /home/wmt/work_ons/debug/onscripter_libretro.so
(gdb) bt


(gdb) set sysroot /home/wmt/work_a30/staging_dir/target/rootfs:/home/wmt/work_a30/staging_dir/target/usr/:/home/wmt/work_a30/staging_dir/target/rootfs/usr/miyoo/

set sysroot /home/wmt/work_a30/staging_dir/target/rootfs:/home/wmt/work_ons/debug/miyoo/lib/

set sysroot /home/wmt/work_ons/debug/miyoo/lib/


