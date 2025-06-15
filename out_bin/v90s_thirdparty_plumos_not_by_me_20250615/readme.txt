https://github.com/game-de-it/plumOS-V90S/releases/tag/plumOS-V90S_v0.3

ssh:
root/linux

wifi to usb:
I use ugreen


我又可以吹v90s掌机了，我找到一个别人的外面大佬的办法可以ssh进去v90s的batocera系统，
答案是用game-de-it/plumOS-V90S提供的固件，那个固件也是基于batocera系统，
而且它的ssh的用户名密钥是root/linux——
不过缺点是，它没有提供它是如何在开机后修改root密钥的，
所以不能用于v90s和行动派的出厂系统；而且必须自备一个ugreen
（我试过只能用这个，我的其他无线网卡都不行）或者其他batocera
支持的无线网卡（需要自己逐个试），然后通过无线连上去，
否则用网线转usb也不能ssh；这个固件也无法adb，
所以adb的问题依然无法解决，不过能用ssh已经足够了；
如果你不需要调试或者用python，可以不必获取ssh
