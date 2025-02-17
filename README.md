# onscripter-libretro_fork
[WIP] My onscripter-libretro fork, **NOTE, the latest version original code see: **     
https://github.com/YuriSizuku/OnscripterYuri/tree/master/src/onsyuri_libretro  

**Status:**   
NOTE: Sadly my current build onscripter_libretro.so GBK version (I call it onscripter_jh_libretro) is worse than the official version (like MIYOO FLIP), some games will crash.  
Tested under xubuntu 20 64bit, and may be tested well under MIYOO A30 and MIYOO Mini Plus (32bit), RG28XX (32bit), Android 12 (Redmi 12C, 32 and 64bit), Windows 10 (32 and 64bit), Trimui Smart Pro and Trimui Brick (64bit), R36S (64bit), RGB10X (64bit), Waveshare GPM280Z2 (Retropie, 32bit)  
Cmake compiling is not availabe yet, use make instead.  

Test binary files (not stable, buggy, different from the versions of other peoples or official ones):   
https://github.com/weimingtom/onscripter-libretro_fork/tree/master/out_bin/build_20250209  
https://github.com/weimingtom/onscripter-libretro_fork/tree/master/out_bin/build_20241123  
(old) https://github.com/weimingtom/onscripter-libretro_fork/tree/master/out_bin/build_jh_joypad_20240724  

It may be used well for MIYOO A30 (open 0.txt as content using RetroArch32) and MIYOO MINI Plus (only for .sh script running with ra32, or change settings to show menu 'Load Content'), not very sure.  

RG28XX and RGB10X and R36S have their own prebuilt good onscripter_libretro.so files (Closed sources ? May be built from YuriSizuku/OnscripterYuri, not sure), but it can be replaced with my build .so file, something will be wrong about key mapping.  

**Branches:**   
* onscripter-libretro is the SDL1.2 branch, old code, buggy and available, removed by author            
* onsyuri_libretro is the SDL2 branch, latest code, only runnable and tested in Xubuntu 20, merged into other project by author      

**NOTE:**  
The original code seems be merged into Onscripter Yuri, Commits on Oct 8, 2024    
https://github.com/YuriSizuku/OnscripterYuri/tree/master/src/onsyuri_libretro    
https://github.com/YuriSizuku/OnscripterYuri/commits/b3aad4f7ced52861fcf570a87d92cfb43522069e/  
ONScripter Yuri 0.7.4+1, onsyuri  
https://github.com/YuriSizuku/OnscripterYuri/blob/master/src/onsyuri_libretro/onsyuri_libretro.info  

**Onscripter-yuri build, WIP**  
Onsyuri Test binary files (not stable very much):  
(alpha test) https://github.com/weimingtom/onscripter-libretro_fork/tree/master/out_bin/build_yuri_20241219    
https://github.com/weimingtom/onscripter-libretro_fork/tree/master/out_bin/build_20241123   
(old) https://github.com/weimingtom/onscripter-libretro_fork/tree/master/out_bin/build_yuri_android_20241113   
```
我测试过，onsyuri_libretro这个新代码库（相当于onscripter_libretro的SDL2版），目前的研究结果是：
（1）PC、安卓和ARM版都可以编译，但Windows版暂时还不能编译（SDL2代码暂时编译不了）
（2）手头上大部分掌机都能跑onsyuri新核心，但trimui smart pro和rg28xx不行
（trimui smart pro是我编译安卓版之前可以编译运行，但后来编译安卓版后就不行）。
我有时间会把目前修改的代码开源到gh上
2024/11/21:目前上述问题都已修复，未测试    
```

## Install *_libretro.so and .info in Android  
* The so files couldn't be loaded in tf card storage.
* Set the info folder to tf card; install *_libretro.so into /data; Save the configuration.  
* Don't Set the info and the so folder all to tf card, *_libretro.so can not be executed outside /data/ folder,
You have to install core file, not copy or modify cores' folder      
```
我测试安卓版两个版本安装onscripter 和onsyuri libretro也是正常的。
不过要注意，如果是非官方的核心info文件，只能info指定文件夹，
然后安装核心so文件（需要保存配置）——如果info和cores文件夹都指定，
则无法运行核心so文件，可能因为tf卡不允许执行so文件，
所以只能通过安装核心来复制文件到有权限的地方，
然后info指向新目录（因为不能安装info文件）
```

## Other release versions of onscripter_libretro.so except me    
* Known three versions: rg28xx, crossmixos, and tieba (not include me)    
```
我目前知道有三个onscripter_libretro正式发布版本（不计算我自己在内，
我自己编译那个有严重bug），
第一个是rg28xx和同系列，出厂就有，应该是最古老的版本，字体有问题；
第二个是crossmix os版，工具链非官方，似乎是debian的gcc。
第三个版本应该是在tieba上发布的（难道是原作者？），
用的是trimui官方工具链（我也是用这个工具链），
我这三个版本都放到gh上，顺便比较测试

我试了，tieba版的onsyuri（非RA插件）是目前用于trimui的最完美的版本，
不过我不编译这个版本，除非是RA插件，我倾向于用最上游版本，onsyuri的代码是偏旧的
（为了整合jh版的代码），虽然和最上游代码差不多，不过最上游代码的ONScripter_text.cpp
还是有比较大的修改，当然我也还没研究清楚如何整合jh版代码到最上游版本

Trimui Brick的ONS模拟器.zip
```
* RG28xx_Upgrade_20240511-MOD-v2.0.7z\Roms\APPS\upgrade\update1.dep\update1\vendor\deep\retro\cores\onscripter_libretro.so  
* https://github.com/cizia64/CrossMix-OS/blob/main/RetroArch/.retroarch/cores/onscripter_libretro.so  
* (released with standalone non-system retroarch elf application) https://tieba.baidu.com/p/9114508080  
see https://www.bilibili.com/video/BV1stUsYrEy6/  
see https://github.com/weimingtom/onscripter-libretro_fork/tree/master/out_bin/trimui_bilibili_not_by_me  
unzip ONS.7z to SDCARD:/Emus/  
* (onsyuri, without retroarch, standalone application) https://tieba.baidu.com/p/9161272364  
see https://www.bilibili.com/video/BV1stUsYrEy6/   
see https://github.com/weimingtom/onscripter-libretro_fork/tree/master/out_bin/trimui_bilibili_not_by_me  
unzip ONSYURI.7z to SDCARD:/Emus/  

## Bugs or TODO  
* onscripter-jh_ori编译的核心产生闪退
```
原因：libretro.cpp包含了错误的ONScripter.h头文件，导致getWidth()返回0，产生crash，如果指向正确的头文件目录即可解决这个问题  
```
* libpng的ARM汇编代码（可能协程库也有）如何消除？    
* F1菜单退出动作有问题？会退出整个ra；还有有人反映问题如下
```
onsyuri_libretro的SDL退出逻辑有点bug，没有正确注销SDL导致该进程退出后，系统无法再次申请SDL
```
* (done, ignore) RGB10X运行我编译的核心时会失败中途退出（但能进入游戏开头，我用的是我的mizuiro测试游戏）
```
对于RGB10X，如果从：Launcher -> RETROARCH-RETROARCH or RETROARCH32，则会出现这种闪退情况；
如果直接通过：Launcher -> Options -> File Manager -> /opt/retroarch/bin/retroarch or retroarch32，也会出现此问题；
如果通过: Launcher -> ONScripter，进入则不会出现闪退；
故暂时忽略此问题，不修复此BUG

上次说的关于RGB10X无法运行onsyuri-libretro和onscripter-libretro的问题，
这个问题应该暂时无法解决，但不影响使用，
因为如果是从启动器直接启动/roms/onscripter目录中的游戏，
不会出现闪退。如果是从RA/RA32菜单进入或者从/opt下的elf文件启动进入，
才会出现闪退情况——我怀疑是动态库问题，不过没找到相关的错误信息，目前无法修复
```  
* (TODO) see onscripter_jp_test.zip, sjis版有一点乱字问题，其他应该都正常，sjis版(原版日文)的乱字是在点右键菜单选择回到开始的时候，显示确认是否，那里字乱了，不过在gbk版和yuri版都没有这个问题  
* (TODO) win32 onsyuri_libretro.dll, if change window scale to 1x, the black mouse cursor will be hidden  
* (TODO) Fail to compile it (SDL1 version) with old gcc,  
like RG300X gcw0 opendingux MIPS gcc toolchain   
(because of libretro-common compiling ?)    
* (done) 安卓版可运行，但需要很长时间整理ANDROID宏替换问题  
onscripter-libretro_fork_20241112_v2_perfect_run.7z  
* (done) 我试了一下编译运行trimui smart pro的onsyuri核心，虽然也可以运行，但声音不行  
* (done) No ARMv8 64bit support (cannot run on Trimui Smart Pro)  
* (done, see 0x0a problem) ONScripter save menu text is not shown with good charset (JH version ? original vesion ?)  
* (done, see 0x0a problem) JH version dialog text third line is outside the dialog
* (TODO) test ONS游戏整合包.rar, ONS.zip.001 (harddisk work_ons2, use Ons_for_PC.rar)
* (TODO) test PSP game like:  
```
[PSP][PC移植版][月姬][中文版].rar      
```

## games test  
* (TODO) running failed: narcissu for psp β.zip
* 突然之间发现我已恋上你：（20250209修复）无法进入；yuri版正常，语音和bgm似乎有点破音，立绘似乎有点左右压扁。  
修改无法进入的bug后，游戏开始开头第二句有乱字情况；  
游戏是宽屏的导致4比3屏幕的字体太小（居中缩小有黑边），如果RA的输出设置为全屏填满不留黑边（上下拉长），字体会清晰一些；  
修改无法进入的bug后，加载、保存和历史记录有乱字情况；  
```
see ONScripter_command.cpp:2347 int ONScripter::gettagCommand() nullptr bug
don't know reason   
```
* 我所希冀的未来：（20250209修复）进到主界面，然后就开始不了；yuri版正常，终了对话框少了终字    
```
see ONScripter_command.cpp:2347 int ONScripter::gettagCommand() nullptr bug
```
* 孤独少女百合物语：（20250209修复）进到主界面，然后就开始不了；yuri版正常，主菜单无法选择结束游戏      
```
see ONScripter_command.cpp:2347 int ONScripter::gettagCommand() nullptr bug
```
* 水仙1+2：叠行导致有些字没显示，超出屏幕；yuri版没缺字，但有时也会超出屏幕右边    
* 纯白交响曲：新吾名字后面有个方块，bgm似乎有破音;yuri版没有方块  
* 退出问号有回车；yuri版没这个问题  
* 星之梦：对话偶尔会叠到同一行；start无法自动模式  
* eden：自动模式声音会截断  
* 秋之回忆2: yuri版，遇到选择肢时，按X会跳到新的右键上下文菜单（再按一次X退出上下文菜单，但选择肢不显示）  
```
我看到b站的演示，其实miyoo flip是有做ONS入口的，只不过出厂时候隐藏了（还隐藏了FFMPEG和FFPLAY）
只要把Emu/新建文件夹/ONS目录复制到Emu目录即可。我猜测可能觉得ONS（实际是onsyuri）核心有bug，
这个bug主要体现在进入RA后无法退出和调出RA菜单，只能通过ONS游戏本身的上下文菜单退出。
其实我也注意到RA使用onsyuri后会有乱字情况，不过我没找到方法解决
```
* 纯白交响曲：yuri版，如果按住Y快进不放手，可能到饭堂时候会闪退（可能是因为内存不足？），但如果不快进，按A前进，不闪退  
* 秋之回忆2: 所有版本，首页菜单-图片鉴赏-选上下进入，缩略图会花屏；似乎无法通过方向键切换到旁边的缩略图    

## References  
* (origin, dead?) https://github.com/iyzsong/onscripter-libretro
* https://github.com/gouchi/onscripter-libretro  
* https://github.com/madcock/libretro-onscripter    
* (origin) https://github.com/YuriSizuku/OnscripterYuri/tree/master/src/onsyuri_libretro  

## ARM Toolchain (all use one toolchain, include a30 and mini and rg28xx and rpizero2w, not include Trimui Smart Pro aarch64)  
* [MAIN, First used, target 64bit] (for Trimui Smart Pro and Trimui Brick, aarch64) https://github.com/trimui/toolchain_sdk_smartpro/releases/tag/20231018
* [MAIN, Second used, target 32bit] (for miyoo a30) https://github.com/XK9274/a30-sdk-miyoo/releases/tag/16042024  
see https://github.com/weimingtom/miyoo_a30_playground  
see https://github.com/weimingtom/onscripter-jh-miyoo-a30  
* (not tested) https://releases.linaro.org/components/toolchain/binaries/latest-7/arm-linux-gnueabihf/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf.tar.xz  
see https://releases.linaro.org/components/toolchain/binaries/latest-7/arm-linux-gnueabihf/  
* (for miyoo mini, not tested) https://github.com/Yorisoft/HelloMiyoo  
see https://github.com/shauninman/miyoomini-toolchain-buildroot/releases/tag/v0.0.3  
see https://github.com/shauninman/miyoomini-toolchain-buildroot/releases/download/v0.0.3/miyoomini-toolchain.tar.xz
* (for rpi0, not tested) https://github.com/raspberrypi/tools/blob/master/arm-bcm2708/arm-linux-gnueabihf  
or use gcc on rpi3 / rpi4    
* (rg351p-toolchain, not tested) aarch64-buildroot-linux-gnu_sdk-buildroot.tar.gz    
see https://github.com/AdrienLombard/sm64-351elec-port/releases/tag/v1.0.0    
```
xubuntu 20.04 64bit  

sdk_miyoo282_allwinnerA33.tgz (inside gcc-linaro-7.5.0-arm-linux-gnueabihf.tgz tar xzf and move outside)  
staging_dir.tgz (only for weimingtom/onscripter-jh-miyoo-a30)
aarch64-linux-gnu-7.5.0-linaro.tgz
SDK_usr_tg5040_a133p.tgz (only for weimingtom/onscripter-jh-trimui-smart-pro)
android-ndk-r10e-windows-x86_64.exe
TDM-GCC-64_tdm64-gcc-10.3.0-2.7z (merge into msys)    
msys_v11_retroarch_build_64.7z  
msys_v11_retroarch_build_32.7z  

onscripter_cn_test.zip
onscripter_jp_test.zip
```

## Building ONScripter version and ONScripter-jh merge version for ARM
* Status: Miyoo A30 (tested)  
* Status: Miyoo Mini Plus (tested)  
* Status: RG28XX (tested)  
* Status: Xubuntu 20.04 x86-64 (tested)   
* Status: Waveshare GPM280Z2 (tested)  
* Status: Trimui Smart Pro and Trimui Brick (tested, 64bit aarch64)  
* Status: R36S (tested, 64bit aarch64)  
* Status: RGB10X (tested, 64bit aarch64)  
* For ONScripter version: make MIYOO=1 JH=0  
* For ONScripter and ONScripter-jh merge version: make MIYOO=1 JH=1  
* For PC xubuntu 20.04 x86-64 ONScripter-jh merge version: make MIYOO=0 JH=1  
* Also, you can convert 0.txt to UTF-8-BOM charset to use ONScripter version, not JH merge version, because newest version ONScripter may (?) support UTF-8-BOM     
* JH merge version is for GBK/GB2312 charset 0.txt   

## Xubuntu 20.04 64bit Ref  
```
sudo snap install retroarch
(Don't need to install snap,
don't use sudo apt install because that's too old version retroarch)  
see https://www.retroarch.com/index.php?page=linux-instructions  

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

* Trimui Smart Pro: RetroArch 1.18.0, 64bit (Trimui Brick is RetroArch 1.19.1 64bit)    
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
**NOTE**: sometimes delete info/core_info.cache and restart.
* Another method is to change 'Settings->Core->Cache Core Info Files' to 'OFF',  
and then click 'Main Menu->Configuration File->Save Current Configuration' to save it and then restart it.     
```
我怀疑RA为什么有时候能加载核心文件有时候却不能，可能是RA本身的缓存问题，
我之前的解决方法是用--static-libgcc --static-libstdc++ -s来链接so文件，
不过也有可能不是这个原因。
我试过可以删除cores目录下的core_info.cache文件再重新启动ra，
就可以正常加载核心文件了，待考，反正就是很玄乎
（最好确保同时放入info和so文件）
```
```
windows版（32位，用mingw编译，我这个是在win11测试运行）的onsyuri_libretro.dll也可以编译出来了和正常运行，
晚上我可能先把修改过的代码提交到gh，然后等测试好再把所有平台的so和dll插件都重新编译一次。
可能需要刷新核心信息缓存，我的做法是设置-核心-缓存核心信息文件：设置为关闭，
然后菜单-配置文件-保存当前配置
```

## Build Android so file  
* Modify jni/Application.mk to change APP_ABI to armeabi-v7a or arm64-v8a.    
* Don't make the folder too long path name, it will fail to be compiled.   
* Execute ndk-build to compile it.  
* Change the so file name in folder libs.
* Changing APP_ABI to 'all' or multiple values will causes ndk-build too many warnings, so I use one target in APP_ABI per time I build it.     

## Debugging onsyuri_libretro.so on Android  
* BUG: android couldn't load core (fixed)  
```
我大概定位到onsyuri_libretro（onscripter_libretro的SDL2版，
基于onscripter-yuri）在安卓版RA上显示出问题的地方，
应该是在ONScripter::initSDL()里头有一段SDL_GetDisplayMode(0, 0, &mode);的代码用于缩放屏幕，
我怀疑可能这个函数没返回正确的像素大小导致整个屏幕都显示不出内容，和SDL2代码无关。
我的做法是加上一个宏定义判断跳过这段代码
```

## Debugging onsyuri_libretro.so on Trimui and RG28XX    
* BUG: trimui smart pro and rg28xx couldn't load core (fixed), and trimui smart pro no sound (fixed)    
```
上次我编译的onsyuri_libretro，关于trimui smart pro和rg28xx无法加载这个核心，
我改了一下，似乎又能用了，虽然trimui无声音问题仍然未解决。
rg28xx我是删了核心重新安装就正常，不清楚是不是info文件没读对
（也可能是因为我重新编译过so的原因）。至于trimui之前无法加载核心so，
应该是因为我改了SDL2的pthread部分代码导致的，改回去就没问题了，
至于声音，可能是因为dsp设备有问题，但不确定具体位置。
这部分修改代码未提交，我只提交了测试so文件和一些patch说明
```
```
我查到为什么onsyuri_libretro在其他设备上都有声音，唯独在trimui smart pro上没有声音，
是因为SDL2音频驱动被外部环境变量SDL_HINT_AUDIODRIVER干扰了，
选择加载了dsp音频驱动，然而dsp音频驱动没有实际编译进去代码里，
当然就会没声音了，实际应该是NULL，加载dummy SDL2音频驱动。
修改方法就是强制跳过或者直接赋值NULL给SDL_AudioInit的driver_name参数即可
```

## About onsyuri_libretro/deps/SDL_config.h and SDL_dynapi.h  
* The *_libretro.so need to overlay SDL_config.h and SDL_dynapi.h in SDL2.
* SDL_config.h overlay is through Makefile CFLAGS (you can also delete all SDL_config.h files except deps/SDL_config.h)     
* SDL_dynapi.h overlay is failed, so I have to modify all SDL_dynapi.h everywhere  

## xbox360 wireless controller wrong input  
* Sometimes I have to disable xbox360 wireless controller device on Windows, otherwise the button input will be frequent  
 
## onscripter_libretro cursor0.bmp not shown and drawString output characters wrong when it meets 0x0a  
* Adding code to show or hide cursor in processText()     
* Try to eat 0x0a character to solve this problem  
```
我合并的onscripter_libretro jh版的两个显著bug，不显示等待输入光标和字符变乱的bug，
我似乎找到办法修复了，这两个问题都是我合并text.cpp代码时造成的，
等待光标的显示隐藏代码需要参考原版的写法。至于第二个问题乱字问题，这个比较难解决，
我是通过在textCommand和processText函数中消除0x0a字符（斜杠r回车）的方式，
看能不能解决这个问题，但不是很确定，可能最终还是要研究原版的写法来规避这个bug
（我测试过用原版不修改的话会显示不出字符，所以必须修改）
```
* Debugging VC6 project see also    
https://github.com/weimingtom/onscripter_mergejh_sdl1_fork    
* UTF8_CAPTION not necessary    
see https://github.com/weimingtom/onscripter_mergejh_sdl1_fork/blob/master/win32_prj/ref.txt    
* change all sources to sjis or gbk, see    
https://github.com/weimingtom/onscripter-libretro_fork/blob/master/onscripter-libretro/deps/onscripter-jh_gbk.txt  
https://github.com/weimingtom/onscripter-libretro_fork/blob/master/onscripter-libretro/deps/onscripter_sjis.txt  
