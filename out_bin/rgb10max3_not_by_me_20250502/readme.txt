JELOS-RGB10MAX3.aarch64-20240811-MOD_kk.img
JELOS-RGB10MAX3.aarch64-20240811-MOD_kk.zip
(Official, kk mod and G.R.H mod, these three versions maybe all are from G.R.H version, see usr_bin/start_onscripter.sh)
(But, kk mod is better than G.R.H mod, use EEROMS as FAT32 partition, easier for copying files)

onscripter_libretro.so 64bit version just for Japanese SJIS games
onscripter_32b_libretro 32bit version is for Chinese GBK games

===

put to EEROMS:/onscripter, need to put xxx.ons file into EEROMS:/onscripter/game_name/, like
EEROMS:/onscripter/game_name/game_name.ons, 
otherwise you need to launch it with retroarch

Start Button->主菜单(MAIN MENU)->游戏设置(GAME SETTINGS)->按系统配置(PER SYSTEM ADVANCED CONFIGURATION)->Onscripter->模拟器(EMULATOR)->
默认
ONSCRIPTER: ONSCRIPTER-SA
RETROARCH: ONSCRIPTER 32B
RETROARCH: ONSCRIPTER
(这四个分别对应：独立程序onscripter，独立程序onscripter，RetroArch GBK版ONS（字体偏大，可能是安伯尼克的版本），RetroArch SJIS版ONS)

===

???
https://doc.embedfire.com/linux/imx6/base/zh/latest/linux_env/qt_cross_compiling.html
https://developer.arm.com/-/media/Files/downloads/gnu-a/8.3-2019.03/binrel/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf.tar.xz

https://github.com/search?q=rhe6x86_64--arm-linux-gnueabihf&type=code&p=1

