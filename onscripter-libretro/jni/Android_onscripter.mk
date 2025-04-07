LOCAL_PATH := $(call my-dir)


#####################

include $(CLEAR_VARS)

#LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE    := bzip2

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps/libretro-common/include \
  -I$(LOCAL_PATH)/../deps/onscripter \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/sdl/include \
  -I$(LOCAL_PATH)/../deps/sdl-image \
  -I$(LOCAL_PATH)/../deps/sdl-mixer \
  -I$(LOCAL_PATH)/../deps/sdl-ttf \
  -I$(LOCAL_PATH)/../deps/tinycoroutine \
  -I$(LOCAL_PATH)/.. \
  -I$(LOCAL_PATH)/../deps

# bzip2
LOCAL_CFLAGS += -D_FILE_OFFSET_BITS=64
LOCAL_SRC_FILES += \
  $(LOCAL_PATH)/../deps/bzip2/blocksort.c \
  $(LOCAL_PATH)/../deps/bzip2/huffman.c \
  $(LOCAL_PATH)/../deps/bzip2/crctable.c \
  $(LOCAL_PATH)/../deps/bzip2/randtable.c \
  $(LOCAL_PATH)/../deps/bzip2/compress.c \
  $(LOCAL_PATH)/../deps/bzip2/decompress.c \
  $(LOCAL_PATH)/../deps/bzip2/bzlib.c

#LOCAL_SRC_FILES := foo/foo.c
#LOCAL_CFLAGS := -DFOO=2
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/foo
#LOCAL_EXPORT_CFLAGS := -DFOO=1
#LOCAL_EXPORT_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)

#####################

include $(CLEAR_VARS)

#LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE    := freetype

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps/libretro-common/include \
  -I$(LOCAL_PATH)/../deps/onscripter \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/sdl/include \
  -I$(LOCAL_PATH)/../deps/sdl-image \
  -I$(LOCAL_PATH)/../deps/sdl-mixer \
  -I$(LOCAL_PATH)/../deps/sdl-ttf \
  -I$(LOCAL_PATH)/../deps/tinycoroutine \
  -I$(LOCAL_PATH)/.. \
  -I$(LOCAL_PATH)/../deps

# freetype
LOCAL_CFLAGS += -DFT2_BUILD_LIBRARY=1
LOCAL_SRC_FILES += $(addprefix $(LOCAL_PATH)/../deps/freetype/src/,\
  base/ftbase.c \
  base/ftdebug.c \
  base/ftinit.c \
  base/ftsystem.c \
  base/ftbitmap.c \
  base/ftglyph.c \
  \
  autofit/autofit.c \
  psnames/psnames.c \
  sfnt/sfnt.c \
  truetype/truetype.c \
  \
  smooth/smooth.c \
  \
  cff/cff.c \
  cid/type1cid.c \
  gxvalid/gxvalid.c \
  otvalid/otvalid.c \
  psaux/psaux.c \
  pshinter/pshinter.c \
  type1/type1.c \
  cache/ftcache.c \
)

#base/ftstroke.c 
#raster/raster.c 

#LOCAL_SRC_FILES := foo/foo.c
#LOCAL_CFLAGS := -DFOO=2
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/foo
#LOCAL_EXPORT_CFLAGS := -DFOO=1
#LOCAL_EXPORT_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)

#####################

include $(CLEAR_VARS)

#LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE    := libjpeg-turbo

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps/libretro-common/include \
  -I$(LOCAL_PATH)/../deps/onscripter \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/sdl/include \
  -I$(LOCAL_PATH)/../deps/sdl-image \
  -I$(LOCAL_PATH)/../deps/sdl-mixer \
  -I$(LOCAL_PATH)/../deps/sdl-ttf \
  -I$(LOCAL_PATH)/../deps/tinycoroutine \
  -I$(LOCAL_PATH)/.. \
  -I$(LOCAL_PATH)/../deps

# libjpeg-turbo
LOCAL_SRC_FILES += $(addprefix $(LOCAL_PATH)/../deps/libjpeg-turbo/,\
  jcapimin.c jcapistd.c jccoefct.c jccolor.c jcdctmgr.c jchuff.c \
  jcicc.c jcinit.c jcmainct.c jcmarker.c jcmaster.c jcomapi.c jcparam.c \
  jcphuff.c jcprepct.c jcsample.c jctrans.c jdapimin.c jdapistd.c jdatadst.c \
  jdatasrc.c jdcoefct.c jdcolor.c jddctmgr.c jdhuff.c jdicc.c jdinput.c \
  jdmainct.c jdmarker.c jdmaster.c jdmerge.c jdphuff.c jdpostct.c jdsample.c \
  jdtrans.c jerror.c jfdctflt.c jfdctfst.c jfdctint.c jidctflt.c jidctfst.c \
  jidctint.c jidctred.c jquant1.c jquant2.c jutils.c jmemmgr.c jmemnobs.c \
  jaricom.c jcarith.c jdarith.c \
  jsimd_none.c \
)
LOCAL_CFLAGS += -DSIZEOF_SIZE_T=__SIZEOF_SIZE_T__

#LOCAL_SRC_FILES := foo/foo.c
#LOCAL_CFLAGS := -DFOO=2
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/foo
#LOCAL_EXPORT_CFLAGS := -DFOO=1
#LOCAL_EXPORT_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)

#####################

include $(CLEAR_VARS)

#LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE    := zlib

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps/libretro-common/include \
  -I$(LOCAL_PATH)/../deps/onscripter \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/sdl/include \
  -I$(LOCAL_PATH)/../deps/sdl-image \
  -I$(LOCAL_PATH)/../deps/sdl-mixer \
  -I$(LOCAL_PATH)/../deps/sdl-ttf \
  -I$(LOCAL_PATH)/../deps/tinycoroutine \
  -I$(LOCAL_PATH)/.. \
  -I$(LOCAL_PATH)/../deps

# zlib
LOCAL_SRC_FILES += $(addprefix $(LOCAL_PATH)/../deps/zlib/,\
  adler32.c compress.c crc32.c deflate.c gzclose.c gzlib.c \
  gzread.c gzwrite.c inflate.c infback.c inftrees.c inffast.c \
  trees.c uncompr.c zutil.c \
)

#LOCAL_SRC_FILES := foo/foo.c
#LOCAL_CFLAGS := -DFOO=2
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/foo
#LOCAL_EXPORT_CFLAGS := -DFOO=1
#LOCAL_EXPORT_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)

#####################

include $(CLEAR_VARS)

#LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE    := libpng

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps/libretro-common/include \
  -I$(LOCAL_PATH)/../deps/onscripter \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/sdl/include \
  -I$(LOCAL_PATH)/../deps/sdl-image \
  -I$(LOCAL_PATH)/../deps/sdl-mixer \
  -I$(LOCAL_PATH)/../deps/sdl-ttf \
  -I$(LOCAL_PATH)/../deps/tinycoroutine \
  -I$(LOCAL_PATH)/.. \
  -I$(LOCAL_PATH)/../deps

# libpng
LOCAL_SRC_FILES += $(addprefix $(LOCAL_PATH)/../deps/libpng/,\
  png.c pngerror.c pngget.c pngmem.c pngpread.c \
  pngread.c pngrio.c pngrtran.c pngrutil.c \
  pngset.c pngtrans.c pngwio.c pngwrite.c pngwtran.c pngwutil.c \
  arm/arm_init.c arm/filter_neon_intrinsics.c arm/palette_neon_intrinsics.c \
)
LOCAL_SRC_FILES += $(addprefix $(LOCAL_PATH)/../deps/libpng/,\
  arm/filter_neon.S \
)

#LOCAL_SRC_FILES := foo/foo.c
#LOCAL_CFLAGS := -DFOO=2
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/foo
#LOCAL_EXPORT_CFLAGS := -DFOO=1
#LOCAL_EXPORT_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)

#####################

include $(CLEAR_VARS)

#LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE    := libogg

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps/libretro-common/include \
  -I$(LOCAL_PATH)/../deps/onscripter \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/sdl/include \
  -I$(LOCAL_PATH)/../deps/sdl-image \
  -I$(LOCAL_PATH)/../deps/sdl-mixer \
  -I$(LOCAL_PATH)/../deps/sdl-ttf \
  -I$(LOCAL_PATH)/../deps/tinycoroutine \
  -I$(LOCAL_PATH)/.. \
  -I$(LOCAL_PATH)/../deps

# libogg
LOCAL_SRC_FILES += $(addprefix $(LOCAL_PATH)/../deps/libogg/src/,\
  bitwise.c framing.c \
)

#LOCAL_SRC_FILES := foo/foo.c
#LOCAL_CFLAGS := -DFOO=2
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/foo
#LOCAL_EXPORT_CFLAGS := -DFOO=1
#LOCAL_EXPORT_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)

#####################

include $(CLEAR_VARS)

#LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE    := libvorbis

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps/libretro-common/include \
  -I$(LOCAL_PATH)/../deps/onscripter \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/sdl/include \
  -I$(LOCAL_PATH)/../deps/sdl-image \
  -I$(LOCAL_PATH)/../deps/sdl-mixer \
  -I$(LOCAL_PATH)/../deps/sdl-ttf \
  -I$(LOCAL_PATH)/../deps/tinycoroutine \
  -I$(LOCAL_PATH)/.. \
  -I$(LOCAL_PATH)/../deps

# libvorbis
LOCAL_SRC_FILES += $(addprefix $(LOCAL_PATH)/../deps/libvorbis/lib/,\
  mdct.c smallft.c block.c envelope.c window.c lsp.c \
  lpc.c analysis.c synthesis.c psy.c info.c \
  floor1.c floor0.c \
  res0.c mapping0.c registry.c codebook.c sharedbook.c \
  lookup.c bitrate.c vorbisfile.c \
)

#LOCAL_SRC_FILES := foo/foo.c
#LOCAL_CFLAGS := -DFOO=2
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/foo
#LOCAL_EXPORT_CFLAGS := -DFOO=1
#LOCAL_EXPORT_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)

#####################

include $(CLEAR_VARS)

#LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE    := libmad

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps/libretro-common/include \
  -I$(LOCAL_PATH)/../deps/onscripter \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/sdl/include \
  -I$(LOCAL_PATH)/../deps/sdl-image \
  -I$(LOCAL_PATH)/../deps/sdl-mixer \
  -I$(LOCAL_PATH)/../deps/sdl-ttf \
  -I$(LOCAL_PATH)/../deps/tinycoroutine \
  -I$(LOCAL_PATH)/.. \
  -I$(LOCAL_PATH)/../deps

# libmad
LOCAL_CFLAGS += -DFPM_DEFAULT -DSIZEOF_INT=4
LOCAL_SRC_FILES += $(addprefix $(LOCAL_PATH)/../deps/libmad/,\
  version.c fixed.c bit.c timer.c stream.c frame.c \
  synth.c decoder.c layer12.c layer3.c huffman.c \
)

#LOCAL_SRC_FILES := foo/foo.c
#LOCAL_CFLAGS := -DFOO=2
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/foo
#LOCAL_EXPORT_CFLAGS := -DFOO=1
#LOCAL_EXPORT_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)

#####################

include $(CLEAR_VARS)

#LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE    := sdl

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps/libretro-common/include \
  -I$(LOCAL_PATH)/../deps/onscripter \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/sdl/include \
  -I$(LOCAL_PATH)/../deps/sdl-image \
  -I$(LOCAL_PATH)/../deps/sdl-mixer \
  -I$(LOCAL_PATH)/../deps/sdl-ttf \
  -I$(LOCAL_PATH)/../deps/tinycoroutine \
  -I$(LOCAL_PATH)/.. \
  -I$(LOCAL_PATH)/../deps

# sdl
LDFLAGS += -lpthread
LOCAL_SRC_FILES += $(addprefix $(LOCAL_PATH)/../deps/sdl/src/,\
  SDL.c SDL_error.c SDL_fatal.c \
  audio/SDL_audio.c audio/SDL_audiocvt.c audio/SDL_audiodev.c \
  audio/SDL_mixer.c audio/SDL_mixer_m68k.c audio/SDL_wave.c \
  cdrom/SDL_cdrom.c cpuinfo/SDL_cpuinfo.c \
  events/SDL_active.c events/SDL_events.c events/SDL_expose.c \
  events/SDL_keyboard.c events/SDL_mouse.c events/SDL_quit.c \
  events/SDL_resize.c \
  file/SDL_rwops.c \
  joystick/SDL_joystick.c \
  stdlib/SDL_getenv.c stdlib/SDL_iconv.c \
  stdlib/SDL_malloc.c stdlib/SDL_qsort.c \
  stdlib/SDL_stdlib.c stdlib/SDL_string.c \
  thread/SDL_thread.c thread/pthread/SDL_syscond.c thread/pthread/SDL_sysmutex.c \
  thread/pthread/SDL_syssem.c thread/pthread/SDL_systhread.c \
  timer/SDL_timer.c timer/unix/SDL_systimer.c \
  video/SDL_blit_0.c video/SDL_blit_1.c video/SDL_blit_A.c \
  video/SDL_blit.c video/SDL_blit_N.c video/SDL_bmp.c video/SDL_cursor.c \
  video/SDL_gamma.c video/SDL_pixels.c video/SDL_RLEaccel.c \
  video/SDL_stretch.c video/SDL_surface.c video/SDL_video.c \
  video/SDL_yuv.c video/SDL_yuv_mmx.c video/SDL_yuv_sw.c \
  cdrom/dummy/SDL_syscdrom.c \
  joystick/dummy/SDL_sysjoystick.c \
  loadso/dummy/SDL_sysloadso.c \
)

#LOCAL_SRC_FILES := foo/foo.c
#LOCAL_CFLAGS := -DFOO=2
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/foo
#LOCAL_EXPORT_CFLAGS := -DFOO=1
#LOCAL_EXPORT_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)

#####################

include $(CLEAR_VARS)

#LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE    := sdl-libretro

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps/libretro-common/include \
  -I$(LOCAL_PATH)/../deps/onscripter \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/sdl/include \
  -I$(LOCAL_PATH)/../deps/sdl-image \
  -I$(LOCAL_PATH)/../deps/sdl-mixer \
  -I$(LOCAL_PATH)/../deps/sdl-ttf \
  -I$(LOCAL_PATH)/../deps/tinycoroutine \
  -I$(LOCAL_PATH)/.. \
  -I$(LOCAL_PATH)/../deps

# sdl-libretro
LOCAL_SRC_FILES += $(addprefix $(LOCAL_PATH)/../sdl-libretro/, \
  audio.c events.c video.c \
)

LOCAL_CFLAGS += -std=c99

#LOCAL_SRC_FILES := foo/foo.c
#LOCAL_CFLAGS := -DFOO=2
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/foo
#LOCAL_EXPORT_CFLAGS := -DFOO=1
#LOCAL_EXPORT_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)

#####################

include $(CLEAR_VARS)

#LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE    := sdl-image

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps/libretro-common/include \
  -I$(LOCAL_PATH)/../deps/onscripter \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/sdl/include \
  -I$(LOCAL_PATH)/../deps/sdl-image \
  -I$(LOCAL_PATH)/../deps/sdl-mixer \
  -I$(LOCAL_PATH)/../deps/sdl-ttf \
  -I$(LOCAL_PATH)/../deps/tinycoroutine \
  -I$(LOCAL_PATH)/.. \
  -I$(LOCAL_PATH)/../deps

# sdl-image
LOCAL_CFLAGS += -DSIZEOF_SIZE_T=__SIZEOF_SIZE_T__ -DLOAD_JPG -DLOAD_BMP -DLOAD_PNG
LOCAL_SRC_FILES += $(filter-out %/showimage.c, $(wildcard $(LOCAL_PATH)/../deps/sdl-image/*.c))

#LOCAL_SRC_FILES := foo/foo.c
#LOCAL_CFLAGS := -DFOO=2
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/foo
#LOCAL_EXPORT_CFLAGS := -DFOO=1
#LOCAL_EXPORT_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)

#####################

include $(CLEAR_VARS)

#LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE    := sdl-mixer

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps/libretro-common/include \
  -I$(LOCAL_PATH)/../deps/onscripter \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/sdl/include \
  -I$(LOCAL_PATH)/../deps/sdl-image \
  -I$(LOCAL_PATH)/../deps/sdl-mixer \
  -I$(LOCAL_PATH)/../deps/sdl-ttf \
  -I$(LOCAL_PATH)/../deps/tinycoroutine \
  -I$(LOCAL_PATH)/.. \
  -I$(LOCAL_PATH)/../deps

# sdl-mixer
LOCAL_CFLAGS += -DOGG_MUSIC -DMP3_MAD_MUSIC
LOCAL_SRC_FILES += $(addprefix $(LOCAL_PATH)/../deps/sdl-mixer/,\
  mixer.c \
  music.c \
  effects_internal.c \
  effect_position.c \
  load_voc.c \
  load_aiff.c \
  load_ogg.c \
  music_ogg.c \
  dynamic_ogg.c \
  music_mad.c \
)

#LOCAL_SRC_FILES := foo/foo.c
#LOCAL_CFLAGS := -DFOO=2
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/foo
#LOCAL_EXPORT_CFLAGS := -DFOO=1
#LOCAL_EXPORT_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)

#####################

include $(CLEAR_VARS)

#LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE    := sdl-ttf

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps/libretro-common/include \
  -I$(LOCAL_PATH)/../deps/onscripter \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/sdl/include \
  -I$(LOCAL_PATH)/../deps/sdl-image \
  -I$(LOCAL_PATH)/../deps/sdl-mixer \
  -I$(LOCAL_PATH)/../deps/sdl-ttf \
  -I$(LOCAL_PATH)/../deps/tinycoroutine \
  -I$(LOCAL_PATH)/.. \
  -I$(LOCAL_PATH)/../deps

# sdl-ttf
LOCAL_SRC_FILES += $(LOCAL_PATH)/../deps/sdl-ttf/SDL_ttf.c

#LOCAL_SRC_FILES := foo/foo.c
#LOCAL_CFLAGS := -DFOO=2
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/foo
#LOCAL_EXPORT_CFLAGS := -DFOO=1
#LOCAL_EXPORT_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)

#####################

include $(CLEAR_VARS)

#LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE    := libretro-common

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps/libretro-common/include \
  -I$(LOCAL_PATH)/../deps/onscripter \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/sdl/include \
  -I$(LOCAL_PATH)/../deps/sdl-image \
  -I$(LOCAL_PATH)/../deps/sdl-mixer \
  -I$(LOCAL_PATH)/../deps/sdl-ttf \
  -I$(LOCAL_PATH)/../deps/tinycoroutine \
  -I$(LOCAL_PATH)/.. \
  -I$(LOCAL_PATH)/../deps

# libretro-common
LOCAL_SRC_FILES += $(addprefix $(LOCAL_PATH)/../deps/libretro-common/,\
  compat/compat_strl.c \
  encodings/encoding_utf.c \
  string/stdstring.c \
  time/rtime.c \
  file/file_path.c \
  libco/libco.c \
  queues/fifo_queue.c \
)

#LOCAL_SRC_FILES := foo/foo.c
#LOCAL_CFLAGS := -DFOO=2
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/foo
#LOCAL_EXPORT_CFLAGS := -DFOO=1
#LOCAL_EXPORT_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)

#####################

include $(CLEAR_VARS)

#LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE    := onscripter

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps/libretro-common/include \
  -I$(LOCAL_PATH)/../deps/onscripter \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/sdl/include \
  -I$(LOCAL_PATH)/../deps/sdl-image \
  -I$(LOCAL_PATH)/../deps/sdl-mixer \
  -I$(LOCAL_PATH)/../deps/sdl-ttf \
  -I$(LOCAL_PATH)/../deps/tinycoroutine \
  -I$(LOCAL_PATH)/.. \
  -I$(LOCAL_PATH)/../deps

LOCAL_SRC_FILES += $(addprefix $(LOCAL_PATH)/../deps/onscripter/,\
  ONScripter.cpp \
  ONScripter_animation.cpp \
  ONScripter_command.cpp \
  ONScripter_effect.cpp \
  ONScripter_effect_breakup.cpp \
  ONScripter_effect_cascade.cpp \
  ONScripter_event.cpp \
  ONScripter_file.cpp \
  ONScripter_file2.cpp \
  ONScripter_image.cpp \
  ONScripter_lut.cpp \
  ONScripter_rmenu.cpp \
  ONScripter_sound.cpp \
  ONScripter_text.cpp \
  resize_image.cpp \
  sjis2utf16.cpp \
  Encoding.cpp \
  DirectReader.cpp \
  SarReader.cpp \
  NsaReader.cpp \
  ScriptHandler.cpp \
  ScriptParser.cpp \
  ScriptParser_command.cpp \
  FontInfo.cpp \
  AnimationInfo.cpp \
  DirtyRect.cpp \
)

#TODO: remove this switch
LOCAL_CXXFLAGS  += -fpermissive 

LOCAL_CXXFLAGS  += -DENABLE_1BYTE_CHAR

#LOCAL_SRC_FILES := foo/foo.c
#LOCAL_CFLAGS := -DFOO=2
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/foo
#LOCAL_EXPORT_CFLAGS := -DFOO=1
#LOCAL_EXPORT_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)

#####################

include $(CLEAR_VARS)

#LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE    := retro

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps/libretro-common/include \
  -I$(LOCAL_PATH)/../deps/onscripter \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/sdl/include \
  -I$(LOCAL_PATH)/../deps/sdl-image \
  -I$(LOCAL_PATH)/../deps/sdl-mixer \
  -I$(LOCAL_PATH)/../deps/sdl-ttf \
  -I$(LOCAL_PATH)/../deps/tinycoroutine \
  -I$(LOCAL_PATH)/.. \
  -I$(LOCAL_PATH)/../deps

LOCAL_SRC_FILES += $(LOCAL_PATH)/../libretro.cpp

LOCAL_LDFLAGS   += -Wl,-version-script=$(LOCAL_PATH)/../link.T

LOCAL_CPPFLAGS += -std=c++11

LOCAL_WHOLE_STATIC_LIBRARIES += bzip2 freetype libjpeg-turbo zlib libpng libogg libvorbis libmad sdl sdl-libretro sdl-image sdl-mixer sdl-ttf libretro-common  onscripter

#LOCAL_CPP_FEATURES += exceptions
#LOCAL_C_INCLUDES += \
#$(LOCAL_PATH)/.. \
#$(NDK)/source/cpufeatures
#ifneq ($(filter $(TARGET_ARCH_ABI), x86_64 x86),)
#endif
#LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv1_CM -lGLESv2 -lOpenSLES -lz -latomic
#LOCAL_WHOLE_STATIC_LIBRARIES += libonig libpng libfreetype libjpeg-turbo libopusfile libopus libogg
#LOCAL_STATIC_LIBRARIES := android_native_app_glue cpufeatures ndk_helper

include $(BUILD_SHARED_LIBRARY)

#$(call import-module,external/freetype)
#$(call import-module,android/cpufeatures)
#$(call import-module,android/native_app_glue)
#$(call import-module,android/ndk_helper)
