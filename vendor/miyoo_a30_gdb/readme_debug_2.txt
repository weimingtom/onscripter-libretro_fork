$ sudo apt install libncurses5
$ /home/wmt/work_a30/gcc-linaro-7.5.0-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gdb ra32.miyoo ra32.miyoo.5616343.1146.11.core 
(gdb) set solib-search-path .
(gdb) set sysroot /home/wmt/work_a30/staging_dir/target/
(gdb) set sysroot /home/wmt/work_a30/staging_dir/target/rootfs
(gdb) info sharedlibrary


(adb pull ra32.miyoo.5616343.1146.11.core from /tmp/)



(gdb) info sharedlibrary
From        To          Syms Read   Shared Object Library
0xb6f98900  0xb6f995fc  Yes (*)     /home/wmt/work_a30/staging_dir/target/rootfs/lib/libdl.so.2
0xb6f82700  0xb6f85aac  Yes (*)     /home/wmt/work_a30/staging_dir/target/rootfs/lib/librt.so.1
0xb6e307e8  0xb6f55c98  Yes (*)     /home/wmt/work_a30/staging_dir/target/rootfs/usr/lib/libMali.so
0xb6de9600  0xb6df3d1c  Yes (*)     /home/wmt/work_a30/staging_dir/target/rootfs/usr/lib/libz.so.1
0xb6d62988  0xb6dc9b1c  Yes (*)     /home/wmt/work_a30/staging_dir/target/rootfs/usr/lib/libasound.so.2
0xb6d1c180  0xb6d299b0  Yes         /home/wmt/work_a30/staging_dir/target/rootfs/lib/libpthread.so.0
                        No          /mnt/SDCARD/miyoo//lib/libSDL-1.2.so.0
                        No          /mnt/SDCARD/miyoo//lib/libtmenu.so
                        No          /mnt/SDCARD/miyoo//lib/libSDL_ttf-2.0.so.0
                        No          /mnt/SDCARD/miyoo//lib/libSDL_image-1.2.so.0
                        No          /mnt/SDCARD/miyoo//lib/libSDL_mixer-1.2.so.0
0xb6b03814  0xb6b05c14  Yes (*)     /home/wmt/work_a30/staging_dir/target/rootfs/usr/lib/libtinyalsa.so.1
0xb6ade384  0xb6ae5518  Yes (*)     /home/wmt/work_a30/staging_dir/target/rootfs/lib/libmad.so.0
0xb6a6b040  0xb6ab799c  Yes (*)     /home/wmt/work_a30/staging_dir/target/rootfs/usr/lib/libfreetype.so.6
0xb6a48080  0xb6a51094  Yes (*)     /home/wmt/work_a30/staging_dir/target/rootfs/usr/lib/libbz2.so.1.0
0xb69b10c0  0xb6a1c924  Yes (*)     /home/wmt/work_a30/staging_dir/target/rootfs/lib/libstdc++.so.6
0xb68ccc00  0xb68fa678  Yes         /home/wmt/work_a30/staging_dir/target/rootfs/lib/libm.so.6
0xb68abbb8  0xb68b0ef8  Yes         /home/wmt/work_a30/staging_dir/target/rootfs/lib/libgcc_s.so.1
0xb67a1100  0xb6873ff8  Yes         /home/wmt/work_a30/staging_dir/target/rootfs/lib/libc.so.6
0xb6fab800  0xb6fc3968  Yes         /home/wmt/work_a30/staging_dir/target/rootfs/lib/ld-linux-armhf.so.3
0xb2de41a0  0xb300dc94  Yes         /home/wmt/work_ons/debug/onscripter_libretro.so
(*): Shared library is missing debugging information.
(gdb) 
(gdb) 





