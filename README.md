# onscripter-libretro_fork
[WIP] My onscripter-libretro fork  
Status: only tested under xubuntu 20, and may be tested well under MIYOO A30 and MIYOO Mini Plus.    

It may be used well for MIYOO A30 (open 0.txt as content using RetroArch32) and   
MIYOO MINI Plus (only for .sh script running with ra32, or change settings to show menu 'Load Content'),   
not very sure.  

RG28XX has its own prebuilt good onscripter_libretro.so file (closed sources ?),   
but it can be replaced with my build .so file, something will be wrong about key mapping.  

## References  
* (origin, dead?) https://github.com/iyzsong/onscripter-libretro
* https://github.com/gouchi/onscripter-libretro
* https://github.com/madcock/libretro-onscripter  

## ARM Toolchain (all use one toolchain, include a30 and mini and rg28xx and rpizero2w)  
* (for miyoo a30) https://github.com/XK9274/a30-sdk-miyoo/releases/tag/16042024  
see https://github.com/weimingtom/miyoo_a30_playground  
see https://github.com/weimingtom/onscripter-jh-miyoo-a30  
* (not tested) https://releases.linaro.org/components/toolchain/binaries/latest-7/arm-linux-gnueabihf/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf.tar.xz  
see https://releases.linaro.org/components/toolchain/binaries/latest-7/arm-linux-gnueabihf/  
* (for miyoo mini, not tested) https://github.com/Yorisoft/HelloMiyoo  
see https://github.com/shauninman/miyoomini-toolchain-buildroot/releases/tag/v0.0.3  
see https://github.com/shauninman/miyoomini-toolchain-buildroot/releases/download/v0.0.3/miyoomini-toolchain.tar.xz   

## Building ONScripter version and ONScripter-jh merge version for ARM
* Status: Miyoo A30 (tested)  
* Status: Miyoo Mini Plus (not tested)  
* Status: RG28XX (tested, key mapping bad)  
* Status: Xubuntu 20.04 x86-64 (not tested)   
* Status: Waveshare GPM280Z2 (tested, key mapping bad)  
* For ONScripter version: make MIYOO=1 JH=0  
* For ONScripter and ONScripter-jh merge version: make MIYOO=1 JH=1  
* For PC xubuntu 20.04 x86-64 ONScripter-jh merge version: make MIYOO=0 JH=1  
* Also, you can convert 0.txt to UTF-8-BOM charset to use ONScripter version, not JH merge version, because newest version ONScripter may (?) support UTF-8-BOM     
* JH merge version is for GBK/GB2312 charset 0.txt   

## Xubuntu 20.04 64bit Ref  
```
retroarch->~/snap/retroarch/2879/.config/retroarch
或查看系统菜单games里面retroarch的快捷方式，打开后看设置，目录中的设置
```

## Test RetroArch version  
* xubuntu 20.04 64bit : RetroArch 1.19.1 (open RetroArch with desktop main system menu, not command line)  
$ make clean && make MIYOO=0  
```
/snap/retroarch/2879/usr/local/bin/retroarch  
/home/wmt/snap/retroarch/2879/.config/retroarch/cores  
https://docs.libretro.com/development/retroarch/compilation/linux-and-bsd/  
https://www.retroarch.com/index.php?page=linux-instructions  
sudo snap install retroarch  
```

* MIYOO A30: RetroArch 1.16.0 (for RetroArch32 from 软件应用 / APP)    
$ make clean && make  
```
/mnt/SDCARD/RetroArch/.retroarch/cores/  
(not used) /mnt/SDCARD/RetroArch/.retroarch/core_info/
Need to put all two files (.info and .so) to cores/  
Open 0.txt as content using RetroArch32
```

* MIYOO MINI Plus: RetroArch 1.10.2 (only for .sh script running with ra32)  
$ make clean && make  
```
/mnt/SDCARD/RetroArch/.retroarch/cores/
It can use same onscripter_libretro.so as MIYOO A30
launch2.sh (copy folder /mnt/SDCARD/Emu/FC)  
...
HOME=$RA_DIR/ $RA_DIR/ra32.ss -v -L $RA_DIR/.retroarch/cores/$EMU "/mnt/SDCARD/Roms/ONS/tukihime/0.txt"
Then run this launch2.sh with file explorer in MIYOO MINI Plus

Or
Toggle on Menu: 设置(Settings)-界面(User Interface)-菜单项可见性(Menu Item Visibility)-
显示加载核心(Show 'Load Core') and 显示加载游戏(Show 'Load Content') and 显示系统信息(Show 'Information')  
Then run 0.txt from menu 加载游戏(load content) and select core : ONScripter  
```

* (???TODO key mapping not good) RG28XX: RetroArch 1.18.0, 32bit???  
$ make clean && make  
```
copy to /mnt/vendor/deep/retro/cores
```
