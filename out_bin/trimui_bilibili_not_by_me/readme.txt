https://www.bilibili.com/video/BV1stUsYrEy6/
https://tieba.baidu.com/p/9114508080
(onsyuri, not this) https://tieba.baidu.com/p/9161272364

https://tieba.baidu.com/p/9114508080
https://tieba.baidu.com/p/9161272364

unzip ONS.7z and ONSYURI.7z to SDCARD:/Emus/

===
ONS.7z==https://tieba.baidu.com/p/9114508080
ONSYURI.7z==https://tieba.baidu.com/p/9161272364
7z is my repack compression
===
https://tieba.baidu.com/p/9114508080?pn=1
very same as ONS.7z, except bg.png
ONS模拟器.rar==ONS_xunlei_pan_original.rar
https://pan.xunlei.com/s/VO8Hf-38EYkY4fupDFPA7J7UA1?path=%2Fons解压码yanacg
2024-08-06 12:28

===

20250627: about ONSYURI color bug in firmware 1.1.0  

For TRIMUI SMART PRO firmware 1.1.0, you should modify 
/mnt/SDCARD/Emus/ONSYURI/launch.sh
to remove --sharpness 3.1 param, and then reboot,  
otherwise the color in the games will be wrong  

tieba上有人反映说ONSYURI模拟器会出现反色现象，我试过可以修改launch.sh，
把参数--sharpness 3.1去掉然后重启掌机即可（可能是opengles的问题，具体原因不详）

可以试试这样，我是这样解决的，仅供参考：
（1）在PC上用Notepad++或者另外安装一个TRIMUI的文件管理器修改/Emus/ONSYURI/launch.sh文件，把倒数第三行的./onsyuri后面的参数--sharpness 3.1去掉，
（2）然后（可做可不做）系统设置显示把数值调整到默认中间值（例如对比度饱和度色温），
（3）然后重启一下机器，再进入ONSYURI模拟器应该就能颜色恢复正常了。猜测可能是OpenGL ES的问题，但具体原因不明

===
