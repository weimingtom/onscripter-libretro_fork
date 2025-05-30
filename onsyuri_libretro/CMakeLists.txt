cmake_minimum_required(VERSION 3.14)
project(onsyuri-libretro C CXX)
option(LIBRETRO_STATIC "Statically link the libretro core" OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

include(CheckSymbolExists)
check_symbol_exists(__ARM_NEON "stdint.h" HAVE_NEON)

set(SOURCES
  libretro.cpp
  deps/onscripter-yuri/AnimationInfo.cpp
  deps/onscripter-yuri/coding2utf16.cpp
  deps/onscripter-yuri/DirectReader.cpp
  deps/onscripter-yuri/DirtyRect.cpp
  deps/onscripter-yuri/FontInfo.cpp
  deps/onscripter-yuri/gbk2utf16.cpp
  deps/onscripter-yuri/LUAHandler.cpp
  deps/onscripter-yuri/NsaReader.cpp
  deps/onscripter-yuri/ONScripter.cpp
  deps/onscripter-yuri/ONScripter_animation.cpp
  deps/onscripter-yuri/ONScripter_command.cpp
  deps/onscripter-yuri/ONScripter_effect.cpp
  deps/onscripter-yuri/ONScripter_effect_breakup.cpp
  deps/onscripter-yuri/ONScripter_event.cpp
  deps/onscripter-yuri/ONScripter_file.cpp
  deps/onscripter-yuri/ONScripter_file2.cpp
  deps/onscripter-yuri/ONScripter_image.cpp
  deps/onscripter-yuri/ONScripter_lut.cpp
  deps/onscripter-yuri/ONScripter_rmenu.cpp
  deps/onscripter-yuri/ONScripter_sound.cpp
  deps/onscripter-yuri/ONScripter_text.cpp
  deps/onscripter-yuri/Parallel.cpp
  deps/onscripter-yuri/resize_image.cpp
  deps/onscripter-yuri/SarReader.cpp
  deps/onscripter-yuri/ScriptHandler.cpp
  deps/onscripter-yuri/ScriptParser.cpp
  deps/onscripter-yuri/ScriptParser_command.cpp
  deps/onscripter-yuri/sjis2utf16.cpp
  deps/onscripter-yuri/renderer/gles_renderer.cpp
  deps/onscripter-yuri/builtin_dll/layer_oldmovie.cpp
  deps/onscripter-yuri/builtin_dll/layer_snow.cpp
  deps/onscripter-yuri/builtin_dll/ONScripter_effect_cascade.cpp
  deps/onscripter-yuri/builtin_dll/ONScripter_effect_trig.cpp
)

# configure SDL2 for libretro
#file(COPY deps/SDL_config.h DESTINATION ${CMAKE_SOURCE_DIR}/deps/SDL/include)
#file(COPY deps/SDL_dynapi.h DESTINATION ${CMAKE_SOURCE_DIR}/deps/SDL/src/dynapi)
#file(COPY deps/close_code.h DESTINATION ${CMAKE_SOURCE_DIR}/deps/SDL/include)

# prepare <SDL2/*.h> headers directory for onsyuri
file(CREATE_LINK ${CMAKE_SOURCE_DIR}/deps/SDL/include
  ${CMAKE_SOURCE_DIR}/deps/SDL/include/SDL2 SYMBOLIC)
file(CREATE_LINK ${CMAKE_SOURCE_DIR}/deps/SDL_image/include/SDL_image.h
  ${CMAKE_SOURCE_DIR}/deps/SDL/include/SDL2/SDL_image.h SYMBOLIC)
file(CREATE_LINK ${CMAKE_SOURCE_DIR}/deps/SDL_mixer/include/SDL_mixer.h
  ${CMAKE_SOURCE_DIR}/deps/SDL/include/SDL2/SDL_mixer.h SYMBOLIC)
file(CREATE_LINK ${CMAKE_SOURCE_DIR}/deps/SDL_ttf/SDL_ttf.h
  ${CMAKE_SOURCE_DIR}/deps/SDL/include/SDL2/SDL_ttf.h SYMBOLIC)

add_library(sdl2 STATIC
  SDL_libretro.c
  deps/SDL/src/SDL.c
  deps/SDL/src/SDL_assert.c
  deps/SDL/src/SDL_dataqueue.c
  deps/SDL/src/SDL_error.c
  deps/SDL/src/SDL_guid.c
  deps/SDL/src/SDL_hints.c
  deps/SDL/src/SDL_list.c
  deps/SDL/src/SDL_log.c
  deps/SDL/src/SDL_utils.c
  deps/SDL/src/atomic/SDL_atomic.c
  deps/SDL/src/atomic/SDL_spinlock.c
  deps/SDL/src/audio/SDL_audio.c
  deps/SDL/src/audio/SDL_audiocvt.c
  deps/SDL/src/audio/SDL_audiodev.c
  deps/SDL/src/audio/SDL_audiotypecvt.c
  deps/SDL/src/audio/SDL_mixer.c
  deps/SDL/src/audio/SDL_wave.c
  deps/SDL/src/core/linux/SDL_threadprio.c
  deps/SDL/src/cpuinfo/SDL_cpuinfo.c
  deps/SDL/src/dynapi/SDL_dynapi.c
  deps/SDL/src/events/SDL_clipboardevents.c
  deps/SDL/src/events/SDL_displayevents.c
  deps/SDL/src/events/SDL_dropevents.c
  deps/SDL/src/events/SDL_events.c
  deps/SDL/src/events/SDL_gesture.c
  deps/SDL/src/events/SDL_keyboard.c
  deps/SDL/src/events/SDL_keysym_to_scancode.c
  deps/SDL/src/events/SDL_mouse.c
  deps/SDL/src/events/SDL_quit.c
  deps/SDL/src/events/SDL_scancode_tables.c
  deps/SDL/src/events/SDL_touch.c
  deps/SDL/src/events/SDL_windowevents.c
  deps/SDL/src/events/imKStoUCS.c
  deps/SDL/src/file/SDL_rwops.c
  deps/SDL/src/joystick/SDL_gamecontroller.c
  deps/SDL/src/joystick/SDL_joystick.c
  deps/SDL/src/joystick/SDL_steam_virtual_gamepad.c
  deps/SDL/src/joystick/controller_type.c
  deps/SDL/src/joystick/dummy/SDL_sysjoystick.c
  deps/SDL/src/haptic/SDL_haptic.c
  deps/SDL/src/haptic/dummy/SDL_syshaptic.c
  deps/SDL/src/render/SDL_d3dmath.c
  deps/SDL/src/render/SDL_render.c
  deps/SDL/src/render/SDL_yuv_sw.c
  deps/SDL/src/render/opengl/SDL_render_gl.c
  deps/SDL/src/render/opengl/SDL_shaders_gl.c
  deps/SDL/src/render/opengles/SDL_render_gles.c
  deps/SDL/src/render/opengles2/SDL_render_gles2.c
  deps/SDL/src/render/opengles2/SDL_shaders_gles2.c
  deps/SDL/src/render/software/SDL_blendfillrect.c
  deps/SDL/src/render/software/SDL_blendline.c
  deps/SDL/src/render/software/SDL_blendpoint.c
  deps/SDL/src/render/software/SDL_drawline.c
  deps/SDL/src/render/software/SDL_drawpoint.c
  deps/SDL/src/render/software/SDL_render_sw.c
  deps/SDL/src/render/software/SDL_rotate.c
  deps/SDL/src/render/software/SDL_triangle.c
  deps/SDL/src/stdlib/SDL_crc16.c
  deps/SDL/src/stdlib/SDL_crc32.c
  deps/SDL/src/stdlib/SDL_getenv.c
  deps/SDL/src/stdlib/SDL_iconv.c
  deps/SDL/src/stdlib/SDL_malloc.c
  deps/SDL/src/stdlib/SDL_mslibc.c
  deps/SDL/src/stdlib/SDL_qsort.c
  deps/SDL/src/stdlib/SDL_stdlib.c
  deps/SDL/src/stdlib/SDL_string.c
  deps/SDL/src/stdlib/SDL_strtokr.c
  deps/SDL/src/thread/SDL_thread.c
  deps/SDL/src/thread/pthread/SDL_syscond.c
  deps/SDL/src/thread/pthread/SDL_sysmutex.c
  deps/SDL/src/thread/pthread/SDL_syssem.c
  deps/SDL/src/thread/pthread/SDL_systhread.c
  deps/SDL/src/thread/pthread/SDL_systls.c
  deps/SDL/src/timer/SDL_timer.c
  deps/SDL/src/timer/unix/SDL_systimer.c
  deps/SDL/src/video/SDL_RLEaccel.c
  deps/SDL/src/video/SDL_blit.c
  deps/SDL/src/video/SDL_blit_0.c
  deps/SDL/src/video/SDL_blit_1.c
  deps/SDL/src/video/SDL_blit_A.c
  deps/SDL/src/video/SDL_blit_N.c
  deps/SDL/src/video/SDL_blit_auto.c
  deps/SDL/src/video/SDL_blit_copy.c
  deps/SDL/src/video/SDL_blit_slow.c
  deps/SDL/src/video/SDL_bmp.c
  deps/SDL/src/video/SDL_clipboard.c
  deps/SDL/src/video/SDL_egl.c
  deps/SDL/src/video/SDL_fillrect.c
  deps/SDL/src/video/SDL_pixels.c
  deps/SDL/src/video/SDL_rect.c
  deps/SDL/src/video/SDL_shape.c
  deps/SDL/src/video/SDL_stretch.c
  deps/SDL/src/video/SDL_surface.c
  deps/SDL/src/video/SDL_video.c
  deps/SDL/src/video/SDL_vulkan_utils.c
  deps/SDL/src/video/SDL_yuv.c
  deps/SDL/src/video/yuv2rgb/yuv_rgb_lsx.c
  deps/SDL/src/video/yuv2rgb/yuv_rgb_sse.c
  deps/SDL/src/video/yuv2rgb/yuv_rgb_std.c
)
target_include_directories(sdl2 PUBLIC
  deps
  deps/SDL/include
)
target_compile_definitions(sdl2 PRIVATE
  -DSDL_DYNAMIC_API=0
)
# -DSDL_TIMER_UNIX=1 -DHAVE_ATAN -DHAVE_ATAN2 -DHAVE_COPYSIGN -DHAVE_COS -DHAVE_EXP -DHAVE_FABS -DHAVE_FLOOR -DHAVE_FMOD -DHAVE_LOG -DHAVE_LOG10 -DHAVE_POW -DHAVE_SCALBN -DHAVE_SIN -DHAVE_SQRT -DHAVE_TAN

add_library(sdl2_image STATIC
  deps/SDL_image/src/IMG.c
  deps/SDL_image/src/IMG_WIC.c
  deps/SDL_image/src/IMG_avif.c
  deps/SDL_image/src/IMG_bmp.c
  deps/SDL_image/src/IMG_gif.c
  deps/SDL_image/src/IMG_jpg.c
  deps/SDL_image/src/IMG_jxl.c
  deps/SDL_image/src/IMG_lbm.c
  deps/SDL_image/src/IMG_pcx.c
  deps/SDL_image/src/IMG_png.c
  deps/SDL_image/src/IMG_pnm.c
  deps/SDL_image/src/IMG_qoi.c
  deps/SDL_image/src/IMG_stb.c
  deps/SDL_image/src/IMG_svg.c
  deps/SDL_image/src/IMG_tga.c
  deps/SDL_image/src/IMG_tif.c
  deps/SDL_image/src/IMG_webp.c
  deps/SDL_image/src/IMG_xcf.c
  deps/SDL_image/src/IMG_xpm.c
  deps/SDL_image/src/IMG_xv.c
)
target_include_directories(sdl2_image PUBLIC
  deps/SDL_image/include
)
target_compile_definitions(sdl2_image PRIVATE
  -DUSE_STBIMAGE -DLOAD_PNG -DLOAD_JPG -DLOAD_BMP
)
target_link_libraries(sdl2_image sdl2)


add_library(sdl2_mixer STATIC
  deps/SDL_mixer/src/codecs/load_aiff.c
  deps/SDL_mixer/src/codecs/load_voc.c
  deps/SDL_mixer/src/codecs/mp3utils.c
  deps/SDL_mixer/src/codecs/music_cmd.c
  deps/SDL_mixer/src/codecs/music_drflac.c
  deps/SDL_mixer/src/codecs/music_flac.c
  deps/SDL_mixer/src/codecs/music_fluidsynth.c
  deps/SDL_mixer/src/codecs/music_gme.c
  deps/SDL_mixer/src/codecs/music_minimp3.c
  deps/SDL_mixer/src/codecs/music_modplug.c
  deps/SDL_mixer/src/codecs/music_mpg123.c
  deps/SDL_mixer/src/codecs/music_nativemidi.c
  deps/SDL_mixer/src/codecs/music_ogg.c
  deps/SDL_mixer/src/codecs/music_ogg_stb.c
  deps/SDL_mixer/src/codecs/music_opus.c
  deps/SDL_mixer/src/codecs/music_timidity.c
  deps/SDL_mixer/src/codecs/music_wav.c
  deps/SDL_mixer/src/codecs/music_wavpack.c
  deps/SDL_mixer/src/codecs/music_xmp.c
  deps/SDL_mixer/src/codecs/native_midi/native_midi_common.c
  deps/SDL_mixer/src/codecs/native_midi/native_midi_macosx.c
  deps/SDL_mixer/src/codecs/native_midi/native_midi_win32.c
  deps/SDL_mixer/src/codecs/timidity/common.c
  deps/SDL_mixer/src/codecs/timidity/instrum.c
  deps/SDL_mixer/src/codecs/timidity/mix.c
  deps/SDL_mixer/src/codecs/timidity/output.c
  deps/SDL_mixer/src/codecs/timidity/playmidi.c
  deps/SDL_mixer/src/codecs/timidity/readmidi.c
  deps/SDL_mixer/src/codecs/timidity/resample.c
  deps/SDL_mixer/src/codecs/timidity/tables.c
  deps/SDL_mixer/src/codecs/timidity/timidity.c
  deps/SDL_mixer/src/effect_position.c
  deps/SDL_mixer/src/effect_stereoreverse.c
  deps/SDL_mixer/src/effects_internal.c
  deps/SDL_mixer/src/mixer.c
  deps/SDL_mixer/src/music.c
  deps/SDL_mixer/src/utils.c
)
target_include_directories(sdl2_mixer PUBLIC
  deps/SDL_mixer/include
)
target_include_directories(sdl2_mixer PRIVATE
  deps/SDL_mixer/src
  deps/SDL_mixer/src/codecs
)
target_compile_definitions(sdl2_mixer PRIVATE
  -DMUSIC_WAV -DMUSIC_MP3_MINIMP3
  -DMUSIC_OGG -DOGG_USE_STB
)
target_link_libraries(sdl2_mixer sdl2)


set(FT_DISABLE_ZLIB ON CACHE BOOL "freetype zlib option")
set(FT_DISABLE_BZIP2 ON CACHE BOOL "freetype bzip2 option")
set(FT_DISABLE_PNG ON CACHE BOOL "freetype png option")
set(FT_DISABLE_BROTLI ON CACHE BOOL "freetype brotli option")
set(FT_DISABLE_HARFBUZZ ON CACHE BOOL "freetype harfbuzz option")
#add_subdirectory(deps/SDL_ttf/external/freetype)
add_subdirectory(deps/freetype)

add_library(sdl2_ttf STATIC
  deps/SDL_ttf/SDL_ttf.c
)
target_include_directories(sdl2_ttf PUBLIC
  deps/SDL_ttf
)
target_link_libraries(sdl2_ttf sdl2 freetype)

set(BZ_VERSION 1.1.0)
configure_file(
  ${CMAKE_SOURCE_DIR}/deps/bzip2/bz_version.h.in
  ${CMAKE_SOURCE_DIR}/deps/bzip2/bz_version.h
)
add_library(bzip2 STATIC
  deps/bzip2/blocksort.c
  deps/bzip2/huffman.c
  deps/bzip2/crctable.c
  deps/bzip2/randtable.c
  deps/bzip2/compress.c
  deps/bzip2/decompress.c
  deps/bzip2/bzlib.c
)
target_include_directories(bzip2 PUBLIC
  deps/bzip2
)

add_library(lua STATIC
  deps/lua/lapi.c
  deps/lua/lcode.c
  deps/lua/lctype.c
  deps/lua/ldebug.c
  deps/lua/ldo.c
  deps/lua/ldump.c
  deps/lua/lfunc.c
  deps/lua/lgc.c
  deps/lua/llex.c
  deps/lua/lmem.c
  deps/lua/lobject.c
  deps/lua/lopcodes.c
  deps/lua/lparser.c
  deps/lua/lstate.c
  deps/lua/lstring.c
  deps/lua/ltable.c
  deps/lua/ltm.c
  deps/lua/lundump.c
  deps/lua/lvm.c
  deps/lua/lzio.c
  deps/lua/ltests.c
  deps/lua/lauxlib.c
  deps/lua/lbaselib.c
  deps/lua/ldblib.c
  deps/lua/liolib.c
  deps/lua/lmathlib.c
  deps/lua/loslib.c
  deps/lua/ltablib.c
  deps/lua/lstrlib.c
  deps/lua/lutf8lib.c
  deps/lua/lbitlib.c
  deps/lua/loadlib.c
  deps/lua/lcorolib.c
  deps/lua/linit.c
)
target_compile_definitions(lua PRIVATE
  LUA_COMPAT_5_2
)
target_include_directories(lua PUBLIC
  deps/lua
)
target_link_libraries(lua PUBLIC m)

if (LIBRETRO_STATIC)
  add_library(onsyuri_libretro STATIC ${SOURCES})
else ()
  add_library(onsyuri_libretro SHARED ${SOURCES})

  target_link_options(onsyuri_libretro PRIVATE
    -Wl,--version-script=${CMAKE_SOURCE_DIR}/link.T
    -Wl,--no-undefined
    -lm -pthread
  )
endif ()

target_link_libraries(onsyuri_libretro
  bzip2 sdl2 sdl2_image sdl2_mixer sdl2_ttf lua
)

target_include_directories(onsyuri_libretro PRIVATE
  deps/onscripter-yuri
  deps
)
target_compile_definitions(onsyuri_libretro PRIVATE
   __LIBRETRO__
   USE_BUILTIN_LAYER_EFFECTS ENABLE_1BYTE_CHAR
   USE_LUA
   BUILD_ALL_LOG
)
if (HAVE_NEON)
  target_compile_definitions(onsyuri_libretro PRIVATE USE_SIMD USE_SIMD_ARM_NEON)
endif ()

# Follow naming conventions for libretro cores
set_target_properties(onsyuri_libretro PROPERTIES PREFIX "")
if (ANDROID)
  set_target_properties(onsyuri_libretro PROPERTIES SUFFIX "_android.so")
elseif (EMSCRIPTEN)
  set_target_properties(onsyuri_libretro PROPERTIES SUFFIX "${LIBRETRO_SUFFIX}.bc")
elseif (LIBRETRO_STATIC)
  set_target_properties(onsyuri_libretro PROPERTIES SUFFIX "${LIBRETRO_SUFFIX}.a")
endif ()
