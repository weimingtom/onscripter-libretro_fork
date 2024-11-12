# onscripter-libretro_fork
[WIP] My onscripter-libretro fork, **NOTE, the latest version original code see: **     
https://github.com/YuriSizuku/OnscripterYuri/tree/master/src/onsyuri_libretro  

Status: tested under xubuntu 20 64bit, and may be tested well under MIYOO A30 and MIYOO Mini Plus, 
RG28XX, Android 12 (Redmi 12C, 64bit), Windows 10, Trimui Smart Pro (64bit), R36S, RGB10X,   
Waveshare GPM280Z2 (Retropie)  
Test binary files (not stable):   
https://github.com/weimingtom/onscripter-libretro_fork/tree/master/out_bin/build_jh_joypad_20240724  

It may be used well for MIYOO A30 (open 0.txt as content using RetroArch32) and   
MIYOO MINI Plus (only for .sh script running with ra32, or change settings to show menu 'Load Content'),   
not very sure.  

RG28XX and RGB10X and R36S have their own prebuilt good onscripter_libretro.so files  
(Closed sources ? May be built from YuriSizuku/OnscripterYuri, not sure),   
but it can be replaced with my build .so file, something will be wrong about key mapping.  

* onscripter-libretro is the SDL1.2 branch, old code    
* onsyuri_libretro is the SDL2 branch, latest code   

**NOTE:**  
The original code seems be merged into Onscripter Yuri, Commits on Oct 8, 2024    
https://github.com/YuriSizuku/OnscripterYuri/tree/master/src/onsyuri_libretro    
https://github.com/YuriSizuku/OnscripterYuri/commits/b3aad4f7ced52861fcf570a87d92cfb43522069e/  
ONScripter Yuri 0.7.4+1, onsyuri  
https://github.com/YuriSizuku/OnscripterYuri/blob/master/src/onsyuri_libretro/onsyuri_libretro.info  

## Bugs or TODO  
* (TODO, IMP) 安卓版可运行，但需要很长时间整理ANDROID宏替换问题  
onscripter-libretro_fork_20241112_v2_perfect_run.7z  
* (TODO, IMP) 我试了一下编译运行trimui smart pro的onsyuri核心，虽然也可以运行，但声音不行  
* (done) No ARMv8 64bit support (cannot run on Trimui Smart Pro)  
* ONScripter save menu text is not shown with good charset (JH version ? original vesion ?)  
* JH version dialog text third line is outside the dialog
* (TODO) test ONS游戏整合包.rar, ONS.zip.001 (harddisk work_ons2, use Ons_for_PC.rar)
* (TODO) test PSP game like:  
```
[PSP][PC移植版][月姬][中文版].rar      
```
* (TODO) running failed: narcissu for psp β.zip
* (TODO) running failed: 突然之间发现我已恋上你  
* (TODO) running failed: 我所希冀的未来  
* (TODO) running failed: 孤独少女百合物语    
* (TODO) text or font bug: 水仙1+2  
* (TODO) text or font bug: 纯白交响曲  

## References  
* (origin, dead?) https://github.com/iyzsong/onscripter-libretro
* https://github.com/gouchi/onscripter-libretro
* https://github.com/madcock/libretro-onscripter  

## ARM Toolchain (all use one toolchain, include a30 and mini and rg28xx and rpizero2w, not include Trimui Smart Pro aarch64)  
* (for miyoo a30) https://github.com/XK9274/a30-sdk-miyoo/releases/tag/16042024  
see https://github.com/weimingtom/miyoo_a30_playground  
see https://github.com/weimingtom/onscripter-jh-miyoo-a30  
* (not tested) https://releases.linaro.org/components/toolchain/binaries/latest-7/arm-linux-gnueabihf/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf.tar.xz  
see https://releases.linaro.org/components/toolchain/binaries/latest-7/arm-linux-gnueabihf/  
* (for miyoo mini, not tested) https://github.com/Yorisoft/HelloMiyoo  
see https://github.com/shauninman/miyoomini-toolchain-buildroot/releases/tag/v0.0.3  
see https://github.com/shauninman/miyoomini-toolchain-buildroot/releases/download/v0.0.3/miyoomini-toolchain.tar.xz
* (for rpi0, not tested) https://github.com/raspberrypi/tools/blob/master/arm-bcm2708/arm-linux-gnueabihf  
or use gcc on rpi3 / rpi4    
* (for Trimui Smart Pro, aarch64) https://github.com/trimui/toolchain_sdk_smartpro/releases/tag/20231018  

## Building ONScripter version and ONScripter-jh merge version for ARM
* Status: Miyoo A30 (tested)  
* Status: Miyoo Mini Plus (tested)  
* Status: RG28XX (tested)  
* Status: Xubuntu 20.04 x86-64 (tested)   
* Status: Waveshare GPM280Z2 (tested)  
* Status: Trimui Smart Pro (tested, 64bit aarch64)  
* Status: R36S (tested, 64bit aarch64)  
* Status: RGB10X (tested, 64bit aarch64)  
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
$ make MIYOO=0 clean && make MIYOO=0  
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

* MIYOO MINI Plus: RetroArch 1.10.2  
The first method: (not only) for .sh script running with ra32 with -L parameter.  
The second method: but you can also toggle "Show 'Load Content'" to load 0.txt.  
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

* RG28XX: RetroArch 1.18.0, 32bit  
$ make clean && make  
```
copy to /mnt/vendor/deep/retro/cores
```

* Trimui Smart Pro: RetroArch 1.18.0, 64bit  
$ make MIYOO=2 clean && make MIYOO=2  
```
through sdcard reader, copy to SDCARD:\RetroArch\.retroarch\cores  
aka: /mnt/SDCARD/RetroArch/.retroarch/cores/onscripter_libretro.so  
```

* R36S: RetroArch 1.18.0, 64bit  
$ make MIYOO=2 clean && make MIYOO=2  
```
through retropie->file manager (from /roms/), copy to /home/ark/.config/retroarch/cores/onscripter_libretro.so  
Select+X or two joystick press down: retroarch quick menu
Select+Start: retroarch exit  
```

* RGB10X: RetroArch 1.19.1, 64bit  
ArkOS same as R36S  
$ make MIYOO=2 clean && make MIYOO=2  
```
through retropie->file manager (from /roms/), copy to /home/ark/.config/retroarch/cores/onscripter_libretro.so  
-+X: retroarch quick menu  
-+Start: retroarch exit  
```

* Android armeabi-v7a (Retro Arch 32-bit): RetroArch 1.19.1  
RetroArch_ra32.apk  
> cd jni  
> set PATH=%PATH%;D:\android-ndk-r10e  
> ndk-build  
(Modify Android.mk, include $(CORE_DIR)/Makefile-jh.common, to build jh version)   

* Android arm64-v8a (Retro Arch AArch64): RetroArch 1.19.1  
RetroArch_aarch64.apk  
> cd jni  
> set PATH=%PATH%;D:\android-ndk-r10e  
> ndk-build  
(Modify Android.mk, include $(CORE_DIR)/Makefile-jh.common, to build jh version)   
(Modify Application.mk, APP_ABI := arm64-v8a)  

* Windows 64bit, 1.19.1, win11    
RetroArch-Win64-setup.exe  
TDM-GCC-64_tdm64-gcc-10.3.0-2.7z  
msys_v11_retroarch_build_64.7z  
gcc  10.3.0 (tdm64-1), msys  
$ make MIYOO=0 clean && make MIYOO=0  
modify Makefile with -m64  
NOTE: don't put two files with same prefix file name in cores folder (like onscripter_libretro.dllxxxx),    
keep only one dll file in cores  

* Windows 32bit, 1.19.1, win10      
RetroArch.7z, RetroArch-Win32, gcc version 5.1.0 (tdm-1), msys  
msys_v11_retroarch_build_32.7z  
$ make MIYOO=0 clean && make MIYOO=0  
modify Makefile with -m32  
NOTE: don't put two files with same prefix file name in cores folder (like onscripter_libretro.dllxxxx),    
keep only one dll file in cores  

* Waveshare GPM280Z2 32bit, RetroArch 1.10.0, Retropie  
$ make clean && make  
Use WinSCP to copy to /home/pi/.config/retroarch/cores  
SSH user/pass: pi/raspberry  
or GPICASE2W, see retropie-buster-4.8-rpi2_3_zero2w.img.gz  
see GPICASE2W-display-patch-main.zip

## About loading core so file failed  
* Make sure .info and .so files are all put into cores/ folder  
* Try to delete cores/core_info.cache and restart retroarch  
```
我怀疑RA为什么有时候能加载核心文件有时候却不能，可能是RA本身的缓存问题，
我之前的解决方法是用--static-libgcc --static-libstdc++ -s来链接so文件，
不过也有可能不是这个原因。
我试过可以删除cores目录下的core_info.cache文件再重新启动ra，
就可以正常加载核心文件了，待考，反正就是很玄乎
（最好确保同时放入info和so文件）
```

## Build Android so file  
* Modify jni/Application.mk to change APP_ABI to armeabi-v7a or arm64-v8a.    
* Don't make the folder too long path name, it will fail to be compiled.   
* Execute ndk-build to compile it.  
* Change the so file name in folder libs.    

