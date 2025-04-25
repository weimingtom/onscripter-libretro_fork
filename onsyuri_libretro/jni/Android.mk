LOCAL_PATH := $(call my-dir)

#####################

include $(CLEAR_VARS)

#LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE    := SDL2

# put ../deps toppest

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps \
  -I$(LOCAL_PATH)/../deps/lua \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad/ \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/SDL/include \
  -I$(LOCAL_PATH)/../deps/SDL_image/include \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/include \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/src \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/src/codecs \
  -I$(LOCAL_PATH)/../deps/SDL_ttf \
  -I$(LOCAL_PATH)/../deps/onscripter-yuri \
  -I$(LOCAL_PATH)/..

# SDL2
# FIXME:need to modify src/dynapi/SDL_dynapi.h to comment #error
LOCAL_CFLAGS += -DSDL_DYNAMIC_API=0
LOCAL_CFLAGS += -DDECLSPEC=

#FIXME: TODO: need to be removed, see close_code.h
LOCAL_CFLAGS += -UANDROID -U__ANDROID__

# FIXME:dlopen, dlsym, dlclose need -ldl
#-ldl
LOCAL_LDFLAGS += -lpthread
LOCAL_SRC_FILES += $(addprefix $(LOCAL_PATH)/../deps/sdl/src/,\
  SDL.c \
  SDL_assert.c \
  SDL_dataqueue.c \
  SDL_error.c \
  SDL_guid.c \
  SDL_hints.c \
  SDL_list.c \
  SDL_log.c \
  SDL_utils.c \
  atomic/SDL_atomic.c \
  atomic/SDL_spinlock.c \
  audio/SDL_audio.c \
  audio/SDL_audiocvt.c \
  audio/SDL_audiodev.c \
  audio/SDL_audiotypecvt.c \
  audio/SDL_mixer.c \
  audio/SDL_wave.c \
  core/linux/SDL_threadprio.c \
  cpuinfo/SDL_cpuinfo.c \
  dynapi/SDL_dynapi.c \
  events/SDL_clipboardevents.c \
  events/SDL_displayevents.c \
  events/SDL_dropevents.c \
  events/SDL_events.c \
  events/SDL_gesture.c \
  events/SDL_keyboard.c \
  events/SDL_keysym_to_scancode.c \
  events/SDL_mouse.c \
  events/SDL_quit.c \
  events/SDL_scancode_tables.c \
  events/SDL_touch.c \
  events/SDL_windowevents.c \
  events/imKStoUCS.c \
  file/SDL_rwops.c \
  joystick/SDL_gamecontroller.c \
  joystick/SDL_joystick.c \
  joystick/SDL_steam_virtual_gamepad.c \
  joystick/controller_type.c \
  joystick/dummy/SDL_sysjoystick.c \
  haptic/SDL_haptic.c \
  haptic/dummy/SDL_syshaptic.c \
  render/SDL_d3dmath.c \
  render/SDL_render.c \
  render/SDL_yuv_sw.c \
  render/opengl/SDL_render_gl.c \
  render/opengl/SDL_shaders_gl.c \
  render/opengles/SDL_render_gles.c \
  render/opengles2/SDL_render_gles2.c \
  render/opengles2/SDL_shaders_gles2.c \
  render/software/SDL_blendfillrect.c \
  render/software/SDL_blendline.c \
  render/software/SDL_blendpoint.c \
  render/software/SDL_drawline.c \
  render/software/SDL_drawpoint.c \
  render/software/SDL_render_sw.c \
  render/software/SDL_rotate.c \
  render/software/SDL_triangle.c \
  stdlib/SDL_crc16.c \
  stdlib/SDL_crc32.c \
  stdlib/SDL_getenv.c \
  stdlib/SDL_iconv.c \
  stdlib/SDL_malloc.c \
  stdlib/SDL_mslibc.c \
  stdlib/SDL_qsort.c \
  stdlib/SDL_stdlib.c \
  stdlib/SDL_string.c \
  stdlib/SDL_strtokr.c \
  thread/SDL_thread.c \
  thread/pthread/SDL_syscond.c \
  thread/pthread/SDL_sysmutex.c \
  thread/pthread/SDL_syssem.c \
  thread/pthread/SDL_systhread.c \
  thread/pthread/SDL_systls.c \
  timer/SDL_timer.c \
  timer/unix/SDL_systimer.c \
  video/SDL_RLEaccel.c \
  video/SDL_blit.c \
  video/SDL_blit_0.c \
  video/SDL_blit_1.c \
  video/SDL_blit_A.c \
  video/SDL_blit_N.c \
  video/SDL_blit_auto.c \
  video/SDL_blit_copy.c \
  video/SDL_blit_slow.c \
  video/SDL_bmp.c \
  video/SDL_clipboard.c \
  video/SDL_egl.c \
  video/SDL_fillrect.c \
  video/SDL_pixels.c \
  video/SDL_rect.c \
  video/SDL_shape.c \
  video/SDL_stretch.c \
  video/SDL_surface.c \
  video/SDL_video.c \
  video/SDL_vulkan_utils.c \
  video/SDL_yuv.c \
  video/yuv2rgb/yuv_rgb_lsx.c \
  video/yuv2rgb/yuv_rgb_sse.c \
  video/yuv2rgb/yuv_rgb_std.c \
)

LOCAL_STATIC_LIBRARIES := cpufeatures

#LOCAL_SRC_FILES := foo/foo.c
#LOCAL_CFLAGS := -DFOO=2
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/foo
#LOCAL_EXPORT_CFLAGS := -DFOO=1
#LOCAL_EXPORT_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)

#####################

include $(CLEAR_VARS)

#LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE    := sdl_libretro

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps \
  -I$(LOCAL_PATH)/../deps/lua \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad/ \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/SDL/include \
  -I$(LOCAL_PATH)/../deps/SDL_image/include \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/include \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/src \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/src/codecs \
  -I$(LOCAL_PATH)/../deps/SDL_ttf \
  -I$(LOCAL_PATH)/../deps/onscripter-yuri \
  -I$(LOCAL_PATH)/..

# don't use LOCAL_CFLAGS :=, use LOCAL_CFLAGS +=
LOCAL_CFLAGS += -std=c99

# sdl_libretro
LOCAL_SRC_FILES += $(addprefix $(LOCAL_PATH)/../,\
  SDL_libretro.c \
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
LOCAL_MODULE    := bzip2

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps \
  -I$(LOCAL_PATH)/../deps/lua \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad/ \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/SDL/include \
  -I$(LOCAL_PATH)/../deps/SDL_image/include \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/include \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/src \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/src/codecs \
  -I$(LOCAL_PATH)/../deps/SDL_ttf \
  -I$(LOCAL_PATH)/../deps/onscripter-yuri \
  -I$(LOCAL_PATH)/..
  
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
LOCAL_MODULE    := lua

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps \
  -I$(LOCAL_PATH)/../deps/lua \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad/ \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/SDL/include \
  -I$(LOCAL_PATH)/../deps/SDL_image/include \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/include \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/src \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/src/codecs \
  -I$(LOCAL_PATH)/../deps/SDL_ttf \
  -I$(LOCAL_PATH)/../deps/onscripter-yuri \
  -I$(LOCAL_PATH)/..
  
# lua
LOCAL_CFLAGS += -DLUA_COMPAT_5_2
LOCAL_SRC_FILES += \
  $(LOCAL_PATH)/../deps/lua/lapi.c \
  $(LOCAL_PATH)/../deps/lua/lcode.c \
  $(LOCAL_PATH)/../deps/lua/lctype.c \
  $(LOCAL_PATH)/../deps/lua/ldebug.c \
  $(LOCAL_PATH)/../deps/lua/ldo.c \
  $(LOCAL_PATH)/../deps/lua/ldump.c \
  $(LOCAL_PATH)/../deps/lua/lfunc.c \
  $(LOCAL_PATH)/../deps/lua/lgc.c \
  $(LOCAL_PATH)/../deps/lua/llex.c \
  $(LOCAL_PATH)/../deps/lua/lmem.c \
  $(LOCAL_PATH)/../deps/lua/lobject.c \
  $(LOCAL_PATH)/../deps/lua/lopcodes.c \
  $(LOCAL_PATH)/../deps/lua/lparser.c \
  $(LOCAL_PATH)/../deps/lua/lstate.c \
  $(LOCAL_PATH)/../deps/lua/lstring.c \
  $(LOCAL_PATH)/../deps/lua/ltable.c \
  $(LOCAL_PATH)/../deps/lua/ltm.c \
  $(LOCAL_PATH)/../deps/lua/lundump.c \
  $(LOCAL_PATH)/../deps/lua/lvm.c \
  $(LOCAL_PATH)/../deps/lua/lzio.c \
  $(LOCAL_PATH)/../deps/lua/ltests.c \
  $(LOCAL_PATH)/../deps/lua/lauxlib.c \
  $(LOCAL_PATH)/../deps/lua/lbaselib.c \
  $(LOCAL_PATH)/../deps/lua/ldblib.c \
  $(LOCAL_PATH)/../deps/lua/liolib.c \
  $(LOCAL_PATH)/../deps/lua/lmathlib.c \
  $(LOCAL_PATH)/../deps/lua/loslib.c \
  $(LOCAL_PATH)/../deps/lua/ltablib.c \
  $(LOCAL_PATH)/../deps/lua/lstrlib.c \
  $(LOCAL_PATH)/../deps/lua/lutf8lib.c \
  $(LOCAL_PATH)/../deps/lua/lbitlib.c \
  $(LOCAL_PATH)/../deps/lua/loadlib.c \
  $(LOCAL_PATH)/../deps/lua/lcorolib.c \
  $(LOCAL_PATH)/../deps/lua/linit.c

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
  -I$(LOCAL_PATH)/../deps \
  -I$(LOCAL_PATH)/../deps/lua \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad/ \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/SDL/include \
  -I$(LOCAL_PATH)/../deps/SDL_image/include \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/include \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/src \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/src/codecs \
  -I$(LOCAL_PATH)/../deps/SDL_ttf \
  -I$(LOCAL_PATH)/../deps/onscripter-yuri \
  -I$(LOCAL_PATH)/..

# freetype
LOCAL_CFLAGS += -DFT2_BUILD_LIBRARY=1
LOCAL_SRC_FILES += $(addprefix $(LOCAL_PATH)/../deps/freetype/src/,\
  autofit/autofit.c \
  base/ftbase.c \
  base/ftbbox.c \
  base/ftbdf.c \
  base/ftbitmap.c \
  base/ftcid.c \
  base/ftdebug.c \
  base/ftfstype.c \
  base/ftgasp.c \
  base/ftglyph.c \
  base/ftgxval.c \
  base/ftinit.c \
  base/ftmm.c \
  base/ftotval.c \
  base/ftpatent.c \
  base/ftpfr.c \
  base/ftstroke.c \
  base/ftsynth.c \
  base/ftsystem.c \
  base/fttype1.c \
  base/ftwinfnt.c \
  bdf/bdf.c \
  bzip2/ftbzip2.c \
  cache/ftcache.c \
  cff/cff.c \
  cid/type1cid.c \
  gzip/ftgzip.c \
  lzw/ftlzw.c \
  pcf/pcf.c \
  pfr/pfr.c \
  psaux/psaux.c \
  pshinter/pshinter.c \
  psnames/psmodule.c \
  raster/raster.c \
  sdf/sdf.c \
  sfnt/sfnt.c \
  svg/svg.c \
  smooth/smooth.c \
  truetype/truetype.c \
  type1/type1.c \
  type42/type42.c \
  winfonts/winfnt.c \
)

#LOCAL_SRC_FILES := foo/foo.c
#LOCAL_CFLAGS := -DFOO=2
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/foo
#LOCAL_EXPORT_CFLAGS := -DFOO=1
#LOCAL_EXPORT_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)

#####################

#####################

#####################

#####################

#####################

#####################

#####################

include $(CLEAR_VARS)

#LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE    := SDL2_image

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps \
  -I$(LOCAL_PATH)/../deps/lua \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad/ \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/SDL/include \
  -I$(LOCAL_PATH)/../deps/SDL_image/include \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/include \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/src \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/src/codecs \
  -I$(LOCAL_PATH)/../deps/SDL_ttf \
  -I$(LOCAL_PATH)/../deps/onscripter-yuri \
  -I$(LOCAL_PATH)/..

# SDL2_image
LOCAL_CFLAGS += -DSIZEOF_SIZE_T=__SIZEOF_SIZE_T__ 
LOCAL_CFLAGS += -DUSE_STBIMAGE -DLOAD_PNG -DLOAD_JPG -DLOAD_BMP
LOCAL_SRC_FILES += $(filter-out %/showimage.c, $(wildcard $(LOCAL_PATH)/../deps/SDL_image/src/*.c))

#LOCAL_SRC_FILES := foo/foo.c
#LOCAL_CFLAGS := -DFOO=2
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/foo
#LOCAL_EXPORT_CFLAGS := -DFOO=1
#LOCAL_EXPORT_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)

#####################

include $(CLEAR_VARS)

#LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE    := SDL2_mixer

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps \
  -I$(LOCAL_PATH)/../deps/lua \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad/ \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/SDL/include \
  -I$(LOCAL_PATH)/../deps/SDL_image/include \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/include \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/src \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/src/codecs \
  -I$(LOCAL_PATH)/../deps/SDL_ttf \
  -I$(LOCAL_PATH)/../deps/onscripter-yuri \
  -I$(LOCAL_PATH)/..

# SDL2_mixer
LOCAL_CFLAGS += -DMUSIC_MP3_MINIMP3 -DMUSIC_OGG -DOGG_USE_STB
LOCAL_SRC_FILES += $(addprefix $(LOCAL_PATH)/../deps/SDL_mixer/src/,\
  codecs/load_aiff.c \
  codecs/load_voc.c \
  codecs/mp3utils.c \
  codecs/music_cmd.c \
  codecs/music_drflac.c \
  codecs/music_flac.c \
  codecs/music_fluidsynth.c \
  codecs/music_gme.c \
  codecs/music_minimp3.c \
  codecs/music_modplug.c \
  codecs/music_mpg123.c \
  codecs/music_nativemidi.c \
  codecs/music_ogg.c \
  codecs/music_ogg_stb.c \
  codecs/music_opus.c \
  codecs/music_timidity.c \
  codecs/music_wav.c \
  codecs/music_wavpack.c \
  codecs/music_xmp.c \
  codecs/native_midi/native_midi_common.c \
  codecs/native_midi/native_midi_macosx.c \
  codecs/native_midi/native_midi_win32.c \
  codecs/timidity/common.c \
  codecs/timidity/instrum.c \
  codecs/timidity/mix.c \
  codecs/timidity/output.c \
  codecs/timidity/playmidi.c \
  codecs/timidity/readmidi.c \
  codecs/timidity/resample.c \
  codecs/timidity/tables.c \
  codecs/timidity/timidity.c \
  effect_position.c \
  effect_stereoreverse.c \
  effects_internal.c \
  mixer.c \
  music.c \
  utils.c \
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
LOCAL_MODULE    := SDL2_ttf

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps \
  -I$(LOCAL_PATH)/../deps/lua \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad/ \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/SDL/include \
  -I$(LOCAL_PATH)/../deps/SDL_image/include \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/include \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/src \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/src/codecs \
  -I$(LOCAL_PATH)/../deps/SDL_ttf \
  -I$(LOCAL_PATH)/../deps/onscripter-yuri \
  -I$(LOCAL_PATH)/..

# SDL2_ttf
LOCAL_SRC_FILES += $(LOCAL_PATH)/../deps/SDL_ttf/SDL_ttf.c

#LOCAL_SRC_FILES := foo/foo.c
#LOCAL_CFLAGS := -DFOO=2
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/foo
#LOCAL_EXPORT_CFLAGS := -DFOO=1
#LOCAL_EXPORT_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)

#####################

#####################

include $(CLEAR_VARS)

#LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE    := onscripter

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps \
  -I$(LOCAL_PATH)/../deps/lua \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad/ \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/SDL/include \
  -I$(LOCAL_PATH)/../deps/SDL_image/include \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/include \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/src \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/src/codecs \
  -I$(LOCAL_PATH)/../deps/SDL_ttf \
  -I$(LOCAL_PATH)/../deps/onscripter-yuri \
  -I$(LOCAL_PATH)/..

LOCAL_SRC_FILES += $(addprefix $(LOCAL_PATH)/../deps/onscripter-yuri/,\
  AnimationInfo.cpp \
  coding2utf16.cpp \
  DirectReader.cpp \
  DirtyRect.cpp \
  FontInfo.cpp \
  gbk2utf16.cpp \
  LUAHandler.cpp \
  NsaReader.cpp \
  ONScripter.cpp \
  ONScripter_animation.cpp \
  ONScripter_command.cpp \
  ONScripter_effect.cpp \
  ONScripter_effect_breakup.cpp \
  ONScripter_event.cpp \
  ONScripter_file.cpp \
  ONScripter_file2.cpp \
  ONScripter_image.cpp \
  ONScripter_lut.cpp \
  ONScripter_rmenu.cpp \
  ONScripter_sound.cpp \
  ONScripter_text.cpp \
  Parallel.cpp \
  resize_image.cpp \
  SarReader.cpp \
  ScriptHandler.cpp \
  ScriptParser.cpp \
  ScriptParser_command.cpp \
  sjis2utf16.cpp \
  renderer/gles_renderer.cpp \
  builtin_dll/layer_oldmovie.cpp \
  builtin_dll/layer_snow.cpp \
  builtin_dll/ONScripter_effect_cascade.cpp \
  builtin_dll/ONScripter_effect_trig.cpp \
)

#TODO: remove this switch
#LOCAL_CXXFLAGS  += -fpermissive 

LOCAL_CXXFLAGS  += -DUSE_BUILTIN_LAYER_EFFECTS -DENABLE_1BYTE_CHAR -DUSE_LUA

#LOCAL_SRC_FILES := foo/foo.c
#LOCAL_CFLAGS := -DFOO=2
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/foo
#LOCAL_EXPORT_CFLAGS := -DFOO=1
#LOCAL_EXPORT_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)

#####################

#####################

include $(CLEAR_VARS)

#LOCAL_SHORT_COMMANDS := true
LOCAL_MODULE    := retro

LOCAL_CFLAGS += \
  -I$(LOCAL_PATH)/../deps \
  -I$(LOCAL_PATH)/../deps/lua \
  -I$(LOCAL_PATH)/../deps/bzip2 \
  -I$(LOCAL_PATH)/../deps/zlib \
  -I$(LOCAL_PATH)/../deps/freetype/include \
  -I$(LOCAL_PATH)/../deps/libjpeg-turbo \
  -I$(LOCAL_PATH)/../deps/libpng \
  -I$(LOCAL_PATH)/../deps/libogg/include \
  -I$(LOCAL_PATH)/../deps/libvorbis/include \
  -I$(LOCAL_PATH)/../deps/libmad/ \
  -I$(LOCAL_PATH)/../sdl-libretro \
  -I$(LOCAL_PATH)/../deps/SDL/include \
  -I$(LOCAL_PATH)/../deps/SDL_image/include \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/include \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/src \
  -I$(LOCAL_PATH)/../deps/SDL_mixer/src/codecs \
  -I$(LOCAL_PATH)/../deps/SDL_ttf \
  -I$(LOCAL_PATH)/../deps/onscripter-yuri \
  -I$(LOCAL_PATH)/..

LOCAL_SRC_FILES += $(LOCAL_PATH)/../libretro.cpp

LOCAL_LDFLAGS   += -Wl,-version-script=$(LOCAL_PATH)/../link.T

LOCAL_CXXFLAGS += -DUSE_BUILTIN_LAYER_EFFECTS -DENABLE_1BYTE_CHAR -DUSE_LUA
LOCAL_CPPFLAGS += -std=c++11

LOCAL_WHOLE_STATIC_LIBRARIES += SDL2 bzip2 lua freetype SDL2_image SDL2_mixer SDL2_ttf sdl_libretro onscripter

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
$(call import-module,android/cpufeatures)
#$(call import-module,android/native_app_glue)
#$(call import-module,android/ndk_helper)
