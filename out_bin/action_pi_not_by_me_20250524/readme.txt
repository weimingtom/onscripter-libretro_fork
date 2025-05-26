研究了半天，终于搞清楚怎样给Helegaly的Action π行动派掌机添加
onscripter游戏和打开ONS模拟器——简单来说，就是把游戏文件，
例如0.txt和nscript.dat之类的放到一个文件夹里面，
然后放到tf卡的roms/ons里面，但这个文件夹必须用.ons作为后缀
（不是文件是文件夹），例如秋之回忆2.ons之类的文件夹，
然后重启掌机，就能看到onscripter分类了（或者通过菜单创建roms子目录）。
另外，实际上掌机里面自带三个ONS模拟器，除了onscripter和onsyuri这两个核心，
还有一个单独的程序onsyuri，可以通过长按A键-高级游戏设置选项-模拟器来切换。
也因为上面的原因，所以onsyuri核心的info文件不指定后缀名也没关系，
因为batocera系统会把.ons后缀的文件夹目录传给RA，
就不需要根据info文件去选择后缀名了


The odcommander.zip is from qq group, unzip to sdcard:/roms/odcommander

The roms/ons/game_name.ons folder's name must end with .ons
Select game_name.ons and long press A button to choose lauch method of onscripter_libretro or onsyuri_libretro or onsyuri

