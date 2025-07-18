# xubuntu 20.04 64bit
MIYOO:=0
JH:=2

ifeq ($(MIYOO),w32)
#sudo apt install mingw-w64
CC  := i686-w64-mingw32-gcc 
CXX := i686-w64-mingw32-g++ -std=c++11
AR  := i686-w64-mingw32-ar
else ifeq ($(MIYOO),w64)
#sudo apt install mingw-w64
CC  := x86_64-w64-mingw32-gcc 
CXX := x86_64-w64-mingw32-g++ -std=c++11
AR  := x86_64-w64-mingw32-ar
else ifeq ($(MIYOO),2)
CC  := /home/wmt/work_trimui/aarch64-linux-gnu-7.5.0-linaro/bin/aarch64-linux-gnu-gcc
CXX := /home/wmt/work_trimui/aarch64-linux-gnu-7.5.0-linaro/bin/aarch64-linux-gnu-g++
AR  := /home/wmt/work_trimui/aarch64-linux-gnu-7.5.0-linaro/bin/aarch64-linux-gnu-ar
else ifeq ($(MIYOO),1)
CC  := /home/wmt/work_a30/gcc-linaro-7.5.0-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc -marm -mtune=cortex-a7 -mfpu=neon-vfpv4 -mfloat-abi=hard
CXX := /home/wmt/work_a30/gcc-linaro-7.5.0-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++ -marm -mtune=cortex-a7 -mfpu=neon-vfpv4 -mfloat-abi=hard
AR  := /home/wmt/work_a30/gcc-linaro-7.5.0-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-ar
else
CC  := gcc 
CXX := g++ -std=c++11
AR  := ar
endif

STATIC_LINKING := 0
AR             := ar

ifneq ($(V),1)
   Q := @
endif

ifneq ($(SANITIZER),)
   CFLAGS   := -fsanitize=$(SANITIZER) $(CFLAGS)
   CXXFLAGS := -fsanitize=$(SANITIZER) $(CXXFLAGS)
   LDFLAGS  := -fsanitize=$(SANITIZER) $(LDFLAGS)
endif

ifeq ($(platform),)
platform = unix
ifeq ($(shell uname -a),)
   platform = win
else ifneq ($(findstring MINGW,$(shell uname -a)),)
   platform = win
else ifneq ($(findstring Darwin,$(shell uname -a)),)
   platform = osx
else ifneq ($(findstring win,$(shell uname -a)),)
   platform = win
endif
endif

ifeq ($(MIYOO),w32)
platform = win
else ifeq ($(MIYOO),w64)
platform = win
endif

# system platform
system_platform = unix
ifeq ($(shell uname -a),)
	EXE_EXT = .exe
	system_platform = win
else ifneq ($(findstring Darwin,$(shell uname -a)),)
	system_platform = osx
	arch = intel
ifeq ($(shell uname -p),powerpc)
	arch = ppc
endif
else ifneq ($(findstring MINGW,$(shell uname -a)),)
	system_platform = win
endif

CORE_DIR    += .
TARGET_NAME := onsyuri
LIBM		    = -lm

ifeq ($(ARCHFLAGS),)
ifeq ($(archs),ppc)
   ARCHFLAGS = -arch ppc -arch ppc64
else
   ARCHFLAGS = -arch i386 -arch x86_64
endif
endif

ifeq ($(platform), osx)
ifndef ($(NOUNIVERSAL))
   CXXFLAGS += $(ARCHFLAGS)
   LFLAGS += $(ARCHFLAGS)
endif
endif

ifeq ($(STATIC_LINKING), 1)
EXT := a
endif

ifeq ($(platform), unix)
	EXT ?= so
   TARGET := $(TARGET_NAME)_libretro.$(EXT)
   fpic := -fPIC
#   SHARED := -shared -Wl,--version-script=$(CORE_DIR)/link.T -Wl,--no-undefined
   SHARED := -shared -static-libgcc -static-libstdc++ -s -Wl,--version-script=$(CORE_DIR)/link.T -Wl,--no-undefined
else ifeq ($(platform), linux-portable)
   TARGET := $(TARGET_NAME)_libretro.$(EXT)
   fpic := -fPIC -nostdlib
   SHARED := -shared -Wl,--version-script=$(CORE_DIR)/link.T
	LIBM :=
else ifneq (,$(findstring osx,$(platform)))
   TARGET := $(TARGET_NAME)_libretro.dylib
   fpic := -fPIC
   SHARED := -dynamiclib
else ifneq (,$(findstring ios,$(platform)))
   TARGET := $(TARGET_NAME)_libretro_ios.dylib
	fpic := -fPIC
	SHARED := -dynamiclib

ifeq ($(IOSSDK),)
   IOSSDK := $(shell xcodebuild -version -sdk iphoneos Path)
endif

	DEFINES := -DIOS
	CC = cc -arch armv7 -isysroot $(IOSSDK)
ifeq ($(platform),ios9)
CC     += -miphoneos-version-min=8.0
CXXFLAGS += -miphoneos-version-min=8.0
else
CC     += -miphoneos-version-min=5.0
CXXFLAGS += -miphoneos-version-min=5.0
endif
else ifneq (,$(findstring qnx,$(platform)))
	TARGET := $(TARGET_NAME)_libretro_qnx.so
   fpic := -fPIC
   SHARED := -shared -Wl,--version-script=$(CORE_DIR)/link.T -Wl,--no-undefined
else ifeq ($(platform), emscripten)
   TARGET := $(TARGET_NAME)_libretro_emscripten.bc
   fpic := -fPIC
   SHARED := -shared -Wl,--version-script=$(CORE_DIR)/link.T -Wl,--no-undefined
else ifeq ($(platform), vita)
   TARGET := $(TARGET_NAME)_vita.a
   CC = arm-vita-eabi-gcc
   AR = arm-vita-eabi-ar
   CXXFLAGS += -Wl,-q -Wall -O3
	STATIC_LINKING = 1
else ifeq ($(MIYOO),w32)
   LDFLAGS += -lwinmm
   TARGET := $(TARGET_NAME)_libretro.dll
   SHARED := -shared -Wl,--version-script=$(CORE_DIR)/link.T -Wl,--no-undefined
else ifeq ($(MIYOO),w64)
   LDFLAGS += -lwinmm
   TARGET := $(TARGET_NAME)_libretro.dll
   SHARED := -shared -Wl,--version-script=$(CORE_DIR)/link.T -Wl,--no-undefined	
else
   #CC = gcc
CC  = gcc -m64
CXX = g++ -m64 -std=c++11
AR  = ar   
#CC  = gcc -m32
#CXX = g++ -m32 -std=c++11

#for midiOutPrepareHeader (mmeapi.h)  
LDFLAGS += -lwinmm

#AR  = ar   
   TARGET := $(TARGET_NAME)_libretro.dll
#-static-libgcc -static-libstdc++ -s   
   SHARED := -shared -Wl,--version-script=$(CORE_DIR)/link.T -Wl,--no-undefined
endif

LDFLAGS += $(LIBM)
# "-DFALLTHROUGH=;"
ifeq ($(DEBUG), 1)
   CFLAGS += -O0 -g -DDEBUG
   CXXFLAGS += -O0 -g -DDEBUG
else
   CFLAGS += -O3
   CXXFLAGS += -O3
endif

ifeq ($(JH),1)
include Makefile-jh.common
else ifeq ($(JH),2)
include Makefile-yuri.common
else
include Makefile.common
endif

OBJECTS := $(SOURCES_C:.c=.o) $(SOURCES_CXX:.cpp=.o) $(SOURCES_S:.S=.o)

CFLAGS   += -Wall -D__LIBRETRO__ $(fpic) -DBUILD_ALL_LOG=1
CXXFLAGS += -Wall -D__LIBRETRO__ $(fpic) -DBUILD_ALL_LOG=1
#not good: -DBUILD_TRIMUI_SMART_PRO_AUDIO=1

all: $(TARGET)

$(TARGET): $(OBJECTS)
ifeq ($(STATIC_LINKING), 1)
	$(AR) rcs $@ $(OBJECTS)
else
	@$(if $(Q), $(shell echo echo LD $@),)
	$(Q)$(CXX) $(fpic) $(SHARED) $(INCLUDES) -o $@ $(OBJECTS) $(LDFLAGS)
endif

%.o: %.c
	@$(if $(Q), $(shell echo echo CC $<),)
	$(Q)$(CC) $(CFLAGS) $(fpic) -c -o $@ $<

%.o: %.cpp
	@$(if $(Q), $(shell echo echo CXX $<),)
	$(Q)$(CXX) $(CXXFLAGS) $(fpic) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean

print-%:
	@echo '$*=$($*)'

install:
	cp onsyuri_libretro.so /home/wmt/snap/retroarch/common/.config/retroarch/cores/.
	cp onsyuri_libretro.info /home/wmt/snap/retroarch/common/.config/retroarch/cores/.

install2:
	cp onsyuri_libretro.so /home/wmt/.config/retroarch/cores/.
	cp onsyuri_libretro.info /home/wmt/.config/retroarch/cores/.

