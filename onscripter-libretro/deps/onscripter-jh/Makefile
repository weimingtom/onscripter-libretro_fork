# -*- Makefile -*-
#
# Makefile.Linux - Makefile rules for linux
#

#copy this file from Makefile.Linux
#
#sudo apt-get install libsdl-dev
#(x)sudo apt-get install liblua5.1-0-dev
#sudo apt-get install libsdl-image1.2-dev 
#sudo apt-get install libsdl-ttf2.0-dev 
#sudo apt-get install libsdl-mixer1.2-dev 
#sudo apt-get install libbz2-dev
#(x)sudo apt-get install libfontconfig1-dev
#(x)sudo apt-get install libogg-dev
#(x)sudo apt-get install libvorbis-dev
#sudo apt-get install libfreetype-dev
#
MIYOO:=0
#now only for MIYOO A30, not MIYOO MINI
#if MIYOO==0, built for PC, xubuntu20 or rpd:
#make clean && make MIYOO=0

#SDL_VIDEO_FBCON_ROTATION=NONE,CW,CCW,UD

EXESUFFIX =
OBJSUFFIX = .o

.SUFFIXES:
.SUFFIXES: $(OBJSUFFIX) .cpp .h

TARGET = onscripter$(EXESUFFIX) 
#\
#	sardec$(EXESUFFIX) \
#	nsadec$(EXESUFFIX) \
#	sarconv$(EXESUFFIX) \
#	nsaconv$(EXESUFFIX) 
EXT_OBJS = 

# mandatory: SDL, SDL_ttf, SDL_image, SDL_mixer, bzip2, libjpeg
ifeq ($(MIYOO),1)
SYSROOT?=/home/wmt/work_miyoo_mini/miyoomini-toolchain/arm-linux-gnueabihf/libc
ARCH=-marm -mtune=cortex-a7 -mfpu=neon-vfpv4 -mfloat-abi=hard 
#-march=armv7ve+simd
DEFS = -DLINUX -DNDEBUG -DMIYOO
#-DUSE_SDL_RENDERER  
#-DMIYOO, search SDL_RenderPresent in ONScripter.cpp, there is a display flush bug for SDL2
INCS = -Os $(ARCH) -I${SYSROOT}/usr/include -I${SYSROOT}/usr/include/SDL -I${SYSROOT}/usr/include/freetype2 -I./bzip2-1.0.4_mod -ffunction-sections -fdata-sections -Wall -I./libjpeg

LIBS = -L./libjpeg -L${SYSROOT}/usr/lib $(ARCH) -lSDL_ttf  -lSDL_mixer -lSDL -lfreetype -ljpeg -lpng -lz -lpthread -lm
#-lSDL_image
#removed -lSDL2_image
#-L${SYSROOT}/usr/lib 
EXT_FLAGS =
else
DEFS = -DLINUX -DMIYOO -g3 -O0 -DFREETYPE_HDR_DIRECTORY
INCS = -I./SDL_ttf-2.0.9_mod `sdl-config --cflags` -I/usr/include/freetype2
LIBS = `sdl-config --libs` -lSDL_image -lSDL_ttf -lSDL_mixer -lfreetype -lpng -ljpeg -lbz2 -lz -lm
#
endif

# recommended: smpeg
#DEFS += -DUSE_SMPEG
#INCS += `smpeg-config --cflags`
#LIBS += `smpeg-config --libs`

# recommended: fontconfig (to get default font)
#DEFS += -DUSE_FONTCONFIG
#LIBS += -lfontconfig

# recommended: OggVorbis 
#DEFS += -DUSE_OGG_VORBIS
#LIBS += -logg -lvorbis -lvorbisfile

# optional: Integer OggVorbis
#DEFS += -DUSE_OGG_VORBIS -DINTEGER_OGG_VORBIS
#LIBS += -lvorbisidec

# optional: support CD audio
#DEFS += -DUSE_CDROM

# optional: avifile
#DEFS += -DUSE_AVIFILE
#INCS += `avifile-config --cflags`
#LIBS += `avifile-config --libs`
#TARGET += simple_aviplay$(EXESUFFIX)
#EXT_OBJS += AVIWrapper$(OBJSUFFIX)

# optional: lua
#DEFS += -DUSE_LUA
#INCS += -I/usr/include/lua5.1
#LIBS += -llua5.1
#EXT_OBJS += LUAHandler$(OBJSUFFIX)

# optional: force screen width for PDA
#DEFS += -DPDA_WIDTH=640

# optional: enable English mode
#DEFS += -DENABLE_1BYTE_CHAR -DFORCE_1BYTE_CHAR


# for GNU g++
ifeq ($(MIYOO),1)
CC = /home/wmt/work_miyoo_mini/miyoomini-toolchain/bin/arm-linux-gnueabihf-g++ 
LD = /home/wmt/work_miyoo_mini/miyoomini-toolchain/bin/arm-linux-gnueabihf-g++ -o
else
CC = g++ 
LD = g++ -o
endif

#CFLAGS = -g -Wall -pipe -c $(INCS) $(DEFS)
CFLAGS = -O3 -Wall -fomit-frame-pointer -pipe -c $(INCS) $(DEFS)

# for GCC on PowerPC specfied
#CC = powerpc-unknown-linux-gnu-g++
#LD = powerpc-unknown-linux-gnu-g++ -o

#CFLAGS = -O3 -mtune=G4 -maltivec -mabi=altivec -mpowerpc-gfxopt -mmultiple -mstring -Wall -fomit-frame-pointer -pipe -c $(INCS) $(DEFS)

# for Intel compiler
#CC = icc
#LD = icc -o

#CFLAGS = -O3 -tpp6 -xK -c $(INCS) $(DEFS)

RM = rm -f

include Makefile.onscripter
