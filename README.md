# onscripter-libretro_fork
[WIP] My onscripter-libretro fork  
Status: only tested under xubuntu 20, not tested well under MIYOO A30.    
It may be used well for MIYOO A30 (open 0.txt as content using RetroArch32) and   
MIYOO MINI Plus (only for .sh script running with ra32), not very sure.  

## Xubuntu 20.04 64bit Ref  
```
retroarch->~/snap/retroarch/2879/.config/retroarch
或查看系统菜单games里面retroarch的快捷方式，打开后看设置，目录中的设置
```

## Test RetroArch version  
* xubuntu 20.04 64bit : RetroArch 1.19.1  
```
/snap/retroarch/2879/usr/local/bin/retroarch  
/home/wmt/snap/retroarch/2879/.config/retroarch/cores  
https://docs.libretro.com/development/retroarch/compilation/linux-and-bsd/  
https://www.retroarch.com/index.php?page=linux-instructions  
sudo snap install retroarch  
```

* MIYOO A30: RetroArch 1.16.0 (for RetroArch32 from 软件应用)    
```
/mnt/SDCARD/RetroArch/.retroarch/cores/  
(not used) /mnt/SDCARD/RetroArch/.retroarch/core_info/
Need to put all two files (.info and .so) to cores/  
Open 0.txt as content using RetroArch32
```

* MIYOO MINI Plus: RetroArch 1.10.2 (only for .sh script running with ra32)
```
/mnt/SDCARD/RetroArch/.retroarch/cores/
It can use same onscripter_libretro.so as MIYOO A30
launch2.sh (copy folder /mnt/SDCARD/EMU/FC)  
...
HOME=$RA_DIR/ $RA_DIR/ra32.ss -v -L $RA_DIR/.retroarch/cores/$EMU "/mnt/SDCARD/Roms/ONS/tukihime/0.txt"
Then run this launch2.sh with file explorer in MIYOO MINI Plus    
```
