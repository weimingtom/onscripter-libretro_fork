cmake_minimum_required(VERSION 3.9)
project(onscripter-libretro C CXX)

option(LIBRETRO_STATIC "Statically link the libretro core" OFF)

set(SOURCES
  libretro.cpp
  deps/bzip2/blocksort.c
  deps/bzip2/huffman.c
  deps/bzip2/crctable.c
  deps/bzip2/randtable.c
  deps/bzip2/compress.c
  deps/bzip2/decompress.c
  deps/bzip2/bzlib.c
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
  sdl-libretro/SDL_ttf.c
  sdl-libretro/SDL_image.cpp
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
    -Wl,--no-undefined -lpthread
  )
endif ()

target_compile_definitions(onscripter_libretro PRIVATE
  -D_FILE_OFFSET_BITS=64 -DFT2_BUILD_LIBRARY=1
  -DSIZEOF_SIZE_T=__SIZEOF_SIZE_T__
  -DFPM_DEFAULT -DSIZEOF_INT=4
  -DLOAD_JPG -DLOAD_BMP -DLOAD_PNG
  -DOGG_MUSIC -DMP3_MAD_MUSIC
)
target_include_directories(onscripter_libretro PRIVATE
  deps
  deps/onscripter
  deps/bzip2
  deps/libmad
  deps/libogg/include
  deps/libretro-common/include
  deps/libvorbis/include
  deps/sdl-image
  deps/sdl/include
  deps/sdl-mixer
  sdl-libretro
)

target_link_libraries(onscripter_libretro PRIVATE pthread)

# Follow naming conventions for libretro cores
set_target_properties(onscripter_libretro PROPERTIES PREFIX "")
if (ANDROID)
  set_target_properties(onscripter_libretro PROPERTIES SUFFIX "_android.so")
elseif (EMSCRIPTEN)
  set_target_properties(onscripter_libretro PROPERTIES SUFFIX "${LIBRETRO_SUFFIX}.bc")
elseif (LIBRETRO_STATIC)
  set_target_properties(onscripter_libretro PROPERTIES SUFFIX "${LIBRETRO_SUFFIX}.a")
endif ()
