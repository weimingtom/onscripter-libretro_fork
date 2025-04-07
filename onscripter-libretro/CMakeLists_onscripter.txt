cmake_minimum_required(VERSION 3.9)
project(onscripter-libretro C CXX)

option(LIBRETRO_STATIC "Statically link the libretro core" OFF)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

set(SOURCES
  libretro.cpp
  deps/bzip2/blocksort.c
  deps/bzip2/huffman.c
  deps/bzip2/crctable.c
  deps/bzip2/randtable.c
  deps/bzip2/compress.c
  deps/bzip2/decompress.c
  deps/bzip2/bzlib.c
  deps/freetype/src/base/ftbase.c
  deps/freetype/src/base/ftdebug.c
  deps/freetype/src/base/ftinit.c
  deps/freetype/src/base/ftsystem.c
  deps/freetype/src/base/ftbitmap.c
  deps/freetype/src/base/ftglyph.c
  deps/freetype/src/autofit/autofit.c
  deps/freetype/src/psnames/psnames.c
  deps/freetype/src/sfnt/sfnt.c
  deps/freetype/src/truetype/truetype.c
  deps/freetype/src/smooth/smooth.c
  deps/freetype/src/cff/cff.c
  deps/freetype/src/cid/type1cid.c
  deps/freetype/src/gxvalid/gxvalid.c
  deps/freetype/src/otvalid/otvalid.c
  deps/freetype/src/psaux/psaux.c
  deps/freetype/src/pshinter/pshinter.c
  deps/freetype/src/type1/type1.c
  deps/freetype/src/cache/ftcache.c
  deps/libjpeg-turbo/jcapimin.c
  deps/libjpeg-turbo/jcapistd.c
  deps/libjpeg-turbo/jccoefct.c
  deps/libjpeg-turbo/jccolor.c
  deps/libjpeg-turbo/jcdctmgr.c
  deps/libjpeg-turbo/jchuff.c
  deps/libjpeg-turbo/jcicc.c
  deps/libjpeg-turbo/jcinit.c
  deps/libjpeg-turbo/jcmainct.c
  deps/libjpeg-turbo/jcmarker.c
  deps/libjpeg-turbo/jcmaster.c
  deps/libjpeg-turbo/jcomapi.c
  deps/libjpeg-turbo/jcparam.c
  deps/libjpeg-turbo/jcphuff.c
  deps/libjpeg-turbo/jcprepct.c
  deps/libjpeg-turbo/jcsample.c
  deps/libjpeg-turbo/jctrans.c
  deps/libjpeg-turbo/jdapimin.c
  deps/libjpeg-turbo/jdapistd.c
  deps/libjpeg-turbo/jdatadst.c
  deps/libjpeg-turbo/jdatasrc.c
  deps/libjpeg-turbo/jdcoefct.c
  deps/libjpeg-turbo/jdcolor.c
  deps/libjpeg-turbo/jddctmgr.c
  deps/libjpeg-turbo/jdhuff.c
  deps/libjpeg-turbo/jdicc.c
  deps/libjpeg-turbo/jdinput.c
  deps/libjpeg-turbo/jdmainct.c
  deps/libjpeg-turbo/jdmarker.c
  deps/libjpeg-turbo/jdmaster.c
  deps/libjpeg-turbo/jdmerge.c
  deps/libjpeg-turbo/jdphuff.c
  deps/libjpeg-turbo/jdpostct.c
  deps/libjpeg-turbo/jdsample.c
  deps/libjpeg-turbo/jdtrans.c
  deps/libjpeg-turbo/jerror.c
  deps/libjpeg-turbo/jfdctflt.c
  deps/libjpeg-turbo/jfdctfst.c
  deps/libjpeg-turbo/jfdctint.c
  deps/libjpeg-turbo/jidctflt.c
  deps/libjpeg-turbo/jidctfst.c
  deps/libjpeg-turbo/jidctint.c
  deps/libjpeg-turbo/jidctred.c
  deps/libjpeg-turbo/jquant1.c
  deps/libjpeg-turbo/jquant2.c
  deps/libjpeg-turbo/jutils.c
  deps/libjpeg-turbo/jmemmgr.c
  deps/libjpeg-turbo/jmemnobs.c
  deps/libjpeg-turbo/jaricom.c
  deps/libjpeg-turbo/jcarith.c
  deps/libjpeg-turbo/jdarith.c
  deps/libjpeg-turbo/jsimd_none.c
  deps/zlib/adler32.c
  deps/zlib/compress.c
  deps/zlib/crc32.c
  deps/zlib/deflate.c
  deps/zlib/gzclose.c
  deps/zlib/gzlib.c
  deps/zlib/gzread.c
  deps/zlib/gzwrite.c
  deps/zlib/inflate.c
  deps/zlib/infback.c
  deps/zlib/inftrees.c
  deps/zlib/inffast.c
  deps/zlib/trees.c
  deps/zlib/uncompr.c
  deps/zlib/zutil.c
  deps/libpng/png.c
  deps/libpng/pngerror.c
  deps/libpng/pngget.c
  deps/libpng/pngmem.c
  deps/libpng/pngpread.c
  deps/libpng/pngread.c
  deps/libpng/pngrio.c
  deps/libpng/pngrtran.c
  deps/libpng/pngrutil.c
  deps/libpng/pngset.c
  deps/libpng/pngtrans.c
  deps/libpng/pngwio.c
  deps/libpng/pngwrite.c
  deps/libpng/pngwtran.c
  deps/libpng/pngwutil.c
  deps/libogg/src/bitwise.c
  deps/libogg/src/framing.c
  deps/libvorbis/lib/mdct.c
  deps/libvorbis/lib/smallft.c
  deps/libvorbis/lib/block.c
  deps/libvorbis/lib/envelope.c
  deps/libvorbis/lib/window.c
  deps/libvorbis/lib/lsp.c
  deps/libvorbis/lib/lpc.c
  deps/libvorbis/lib/analysis.c
  deps/libvorbis/lib/synthesis.c
  deps/libvorbis/lib/psy.c
  deps/libvorbis/lib/info.c
  deps/libvorbis/lib/floor1.c
  deps/libvorbis/lib/floor0.c
  deps/libvorbis/lib/res0.c
  deps/libvorbis/lib/mapping0.c
  deps/libvorbis/lib/registry.c
  deps/libvorbis/lib/codebook.c
  deps/libvorbis/lib/sharedbook.c
  deps/libvorbis/lib/lookup.c
  deps/libvorbis/lib/bitrate.c
  deps/libvorbis/lib/vorbisfile.c
  deps/libmad/version.c
  deps/libmad/fixed.c
  deps/libmad/bit.c
  deps/libmad/timer.c
  deps/libmad/stream.c
  deps/libmad/frame.c
  deps/libmad/synth.c
  deps/libmad/decoder.c
  deps/libmad/layer12.c
  deps/libmad/layer3.c
  deps/libmad/huffman.c
  deps/sdl/src/SDL.c
  deps/sdl/src/SDL_error.c
  deps/sdl/src/SDL_fatal.c
  deps/sdl/src/audio/SDL_audio.c
  deps/sdl/src/audio/SDL_audiocvt.c
  deps/sdl/src/audio/SDL_audiodev.c
  deps/sdl/src/audio/SDL_mixer.c
  deps/sdl/src/audio/SDL_mixer_m68k.c
  deps/sdl/src/audio/SDL_wave.c
  deps/sdl/src/cdrom/SDL_cdrom.c
  deps/sdl/src/cpuinfo/SDL_cpuinfo.c
  deps/sdl/src/events/SDL_active.c
  deps/sdl/src/events/SDL_events.c
  deps/sdl/src/events/SDL_expose.c
  deps/sdl/src/events/SDL_keyboard.c
  deps/sdl/src/events/SDL_mouse.c
  deps/sdl/src/events/SDL_quit.c
  deps/sdl/src/events/SDL_resize.c
  deps/sdl/src/file/SDL_rwops.c
  deps/sdl/src/joystick/SDL_joystick.c
  deps/sdl/src/stdlib/SDL_getenv.c
  deps/sdl/src/stdlib/SDL_iconv.c
  deps/sdl/src/stdlib/SDL_malloc.c
  deps/sdl/src/stdlib/SDL_qsort.c
  deps/sdl/src/stdlib/SDL_stdlib.c
  deps/sdl/src/stdlib/SDL_string.c
  deps/sdl/src/thread/SDL_thread.c
  deps/sdl/src/thread/pthread/SDL_syscond.c
  deps/sdl/src/thread/pthread/SDL_sysmutex.c
  deps/sdl/src/thread/pthread/SDL_syssem.c
  deps/sdl/src/thread/pthread/SDL_systhread.c
  deps/sdl/src/timer/SDL_timer.c
  deps/sdl/src/timer/unix/SDL_systimer.c
  deps/sdl/src/video/SDL_blit_0.c
  deps/sdl/src/video/SDL_blit_1.c
  deps/sdl/src/video/SDL_blit_A.c
  deps/sdl/src/video/SDL_blit.c
  deps/sdl/src/video/SDL_blit_N.c
  deps/sdl/src/video/SDL_bmp.c
  deps/sdl/src/video/SDL_cursor.c
  deps/sdl/src/video/SDL_gamma.c
  deps/sdl/src/video/SDL_pixels.c
  deps/sdl/src/video/SDL_RLEaccel.c
  deps/sdl/src/video/SDL_stretch.c
  deps/sdl/src/video/SDL_surface.c
  deps/sdl/src/video/SDL_video.c
  deps/sdl/src/video/SDL_yuv.c
  deps/sdl/src/video/SDL_yuv_mmx.c
  deps/sdl/src/video/SDL_yuv_sw.c
  deps/sdl/src/cdrom/dummy/SDL_syscdrom.c
  deps/sdl/src/joystick/dummy/SDL_sysjoystick.c
  deps/sdl/src/loadso/dummy/SDL_sysloadso.c
  sdl-libretro/audio.c
  sdl-libretro/events.c
  sdl-libretro/video.c
  deps/sdl-image/IMG_bmp.c
  deps/sdl-image/IMG.c
  deps/sdl-image/IMG_gif.c
  deps/sdl-image/IMG_jpg.c
  deps/sdl-image/IMG_lbm.c
  deps/sdl-image/IMG_pcx.c
  deps/sdl-image/IMG_png.c
  deps/sdl-image/IMG_pnm.c
  deps/sdl-image/IMG_tga.c
  deps/sdl-image/IMG_tif.c
  deps/sdl-image/IMG_webp.c
  deps/sdl-image/IMG_xcf.c
  deps/sdl-image/IMG_xpm.c
  deps/sdl-image/IMG_xv.c
  deps/sdl-image/IMG_xxx.c
  deps/sdl-mixer/mixer.c
  deps/sdl-mixer/music.c
  deps/sdl-mixer/effects_internal.c
  deps/sdl-mixer/effect_position.c
  deps/sdl-mixer/load_voc.c
  deps/sdl-mixer/load_aiff.c
  deps/sdl-mixer/load_ogg.c
  deps/sdl-mixer/music_ogg.c
  deps/sdl-mixer/dynamic_ogg.c
  deps/sdl-mixer/music_mad.c
  deps/sdl-ttf/SDL_ttf.c
  deps/libretro-common/compat/compat_strl.c
  deps/libretro-common/encodings/encoding_utf.c
  deps/libretro-common/string/stdstring.c
  deps/libretro-common/time/rtime.c
  deps/libretro-common/file/file_path.c
  deps/libretro-common/libco/libco.c
  deps/onscripter/ONScripter.cpp
  deps/onscripter/ONScripter_animation.cpp
  deps/onscripter/ONScripter_command.cpp
  deps/onscripter/ONScripter_effect.cpp
  deps/onscripter/ONScripter_effect_breakup.cpp
  deps/onscripter/ONScripter_effect_cascade.cpp
  deps/onscripter/ONScripter_event.cpp
  deps/onscripter/ONScripter_file.cpp
  deps/onscripter/ONScripter_file2.cpp
  deps/onscripter/ONScripter_image.cpp
  deps/onscripter/ONScripter_lut.cpp
  deps/onscripter/ONScripter_rmenu.cpp
  deps/onscripter/ONScripter_sound.cpp
  deps/onscripter/ONScripter_text.cpp
  deps/onscripter/resize_image.cpp
  deps/onscripter/sjis2utf16.cpp
  deps/onscripter/Encoding.cpp
  deps/onscripter/DirectReader.cpp
  deps/onscripter/SarReader.cpp
  deps/onscripter/NsaReader.cpp
  deps/onscripter/ScriptHandler.cpp
  deps/onscripter/ScriptParser.cpp
  deps/onscripter/ScriptParser_command.cpp
  deps/onscripter/FontInfo.cpp
  deps/onscripter/AnimationInfo.cpp
  deps/onscripter/DirtyRect.cpp
)

if (LIBRETRO_STATIC)
  add_library(onscripter_libretro STATIC ${SOURCES})
else ()
  add_library(onscripter_libretro SHARED ${SOURCES})
  target_link_options(onscripter_libretro PRIVATE
    -Wl,--version-script=${CMAKE_SOURCE_DIR}/link.T
  )
endif ()

target_compile_definitions(onscripter_libretro PRIVATE
  -D_FILE_OFFSET_BITS=64 -DFT2_BUILD_LIBRARY=1
  -DSIZEOF_SIZE_T=__SIZEOF_SIZE_T__
  -DFPM_DEFAULT -DSIZEOF_INT=4
  -DLOAD_JPG -DLOAD_BMP -DLOAD_PNG
  -DOGG_MUSIC -DMP3_MAD_MUSIC
  -D__LIBRETRO__ -DENABLE_1BYTE_CHAR
)
target_include_directories(onscripter_libretro PRIVATE
  deps/onscripter
  deps
  deps/bzip2
  deps/freetype/include
  deps/libjpeg-turbo
  deps/libmad
  deps/libogg/include
  deps/libpng
  deps/libretro-common/include
  deps/libvorbis/include
  deps/sdl-image
  deps/sdl/include
  deps/sdl-mixer
  deps/sdl-ttf
  deps/zlib
  sdl-libretro
)

# Follow naming conventions for libretro cores
set_target_properties(onscripter_libretro PROPERTIES PREFIX "")
if (ANDROID)
  set_target_properties(onscripter_libretro PROPERTIES SUFFIX "_android.so")
elseif (EMSCRIPTEN)
  set_target_properties(onscripter_libretro PROPERTIES SUFFIX "${LIBRETRO_SUFFIX}.bc")
elseif (LIBRETRO_STATIC)
  set_target_properties(onscripter_libretro PROPERTIES SUFFIX "${LIBRETRO_SUFFIX}.a")
endif ()
