Undefined symbols for architecture x86_64:
  "_AUGraphGetIndNode", referenced from:
      _GetSequenceAudioUnitMatching in native_midi_macosx.o
  "_AUGraphGetNodeCount", referenced from:
      _GetSequenceAudioUnitMatching in native_midi_macosx.o
  "_AUGraphNodeInfo", referenced from:
      _GetSequenceAudioUnitMatching in native_midi_macosx.o
  "_AudioUnitSetParameter", referenced from:
      _native_midi_start in native_midi_macosx.o
      _native_midi_setvolume in native_midi_macosx.o
  "_AudioUnitSetProperty", referenced from:
      _macosx_load_soundfont in native_midi_macosx.o
  "_CFBundleCopyResourceURL", referenced from:
      _native_midi_start in native_midi_macosx.o
  "_CFBundleGetBundleWithIdentifier", referenced from:
      _native_midi_start in native_midi_macosx.o
  "_CFDataCreate", referenced from:
      _native_midi_loadsong_RW in native_midi_macosx.o
  "_CFRelease", referenced from:
      _native_midi_loadsong_RW in native_midi_macosx.o
      _native_midi_start in native_midi_macosx.o
      _macosx_load_soundfont in native_midi_macosx.o
  "_CFURLCreateFromFileSystemRepresentation", referenced from:
      _macosx_load_soundfont in native_midi_macosx.o
  "_DisposeMusicPlayer", referenced from:
      _native_midi_loadsong_RW in native_midi_macosx.o
      _native_midi_freesong in native_midi_macosx.o
  "_DisposeMusicSequence", referenced from:
      _native_midi_loadsong_RW in native_midi_macosx.o
      _native_midi_freesong in native_midi_macosx.o
  "_IMG_InitTIF", referenced from:
      _IMG_Init in IMG.o
  "_IMG_Load", referenced from:
      _IMG_LoadTexture in IMG.o
     (maybe you meant: _IMG_LoadGIFAnimation_RW, _IMG_LoadSTB_RW , _IMG_LoadWEBPAnimation_RW , _IMG_LoadCUR_RW , _IMG_LoadICO_RW , _IMG_LoadBMP_RW , _IMG_LoadJXL_RW , _IMG_LoadPNG_RW , _IMG_LoadXV_RW , _IMG_LoadQOI_RW , _IMG_LoadTextureTyped_RW , _IMG_LoadAnimation , _IMG_LoadXCF_RW , _IMG_LoadXPM_RW , _IMG_LoadWEBP_RW , _IMG_LoadJPG_RW , _IMG_LoadTexture , _IMG_LoadTexture_RW , _IMG_Load_RW , _IMG_LoadLBM_RW , _IMG_LoadAnimation_RW , _IMG_LoadSizedSVG_RW , _IMG_LoadPCX_RW , _IMG_LoadAVIF_RW , _IMG_LoadXXX_RW , _IMG_LoadSVG_RW , _IMG_LoadTyped_RW , _IMG_LoadAnimationTyped_RW , _IMG_LoadPNM_RW )
  "_IMG_LoadGIF_RW", referenced from:
      _supported in IMG.o
  "_IMG_LoadTGA_RW", referenced from:
      _supported in IMG.o
  "_IMG_LoadTIF_RW", referenced from:
      _supported in IMG.o
  "_IMG_QuitTIF", referenced from:
      _IMG_Quit in IMG.o
  "_IMG_isGIF", referenced from:
      _IMG_LoadTyped_RW in IMG.o
      _IMG_LoadAnimationTyped_RW in IMG.o
      _supported in IMG.o
      _supported_anims in IMG.o
  "_IMG_isTIF", referenced from:
      _IMG_LoadTyped_RW in IMG.o
      _supported in IMG.o
  "_MusicPlayerGetTime", referenced from:
      _native_midi_active in native_midi_macosx.o
  "_MusicPlayerPreroll", referenced from:
      _native_midi_start in native_midi_macosx.o
  "_MusicPlayerSetSequence", referenced from:
      _native_midi_loadsong_RW in native_midi_macosx.o
      _native_midi_freesong in native_midi_macosx.o
  "_MusicPlayerSetTime", referenced from:
      _native_midi_start in native_midi_macosx.o
      _native_midi_active in native_midi_macosx.o
  "_MusicPlayerStart", referenced from:
      _native_midi_start in native_midi_macosx.o
  "_MusicPlayerStop", referenced from:
      _native_midi_freesong in native_midi_macosx.o
      _native_midi_start in native_midi_macosx.o
      _native_midi_stop in native_midi_macosx.o
  "_MusicSequenceFileLoadData", referenced from:
      _native_midi_loadsong_RW in native_midi_macosx.o
  "_MusicSequenceGetAUGraph", referenced from:
      _GetSequenceAudioUnitMatching in native_midi_macosx.o
  "_MusicSequenceGetIndTrack", referenced from:
      _native_midi_loadsong_RW in native_midi_macosx.o
  "_MusicSequenceGetTrackCount", referenced from:
      _native_midi_loadsong_RW in native_midi_macosx.o
  "_MusicTrackGetProperty", referenced from:
      _native_midi_loadsong_RW in native_midi_macosx.o
  "_NewMusicPlayer", referenced from:
      _native_midi_loadsong_RW in native_midi_macosx.o
  "_NewMusicSequence", referenced from:
      _native_midi_loadsong_RW in native_midi_macosx.o
  "_SDL_IOS_JoystickDriver", referenced from:
      _SDL_JoystickInit in SDL_joystick.o
      _SDL_JoystickQuit in SDL_joystick.o
      _SDL_NumJoysticks in SDL_joystick.o
      _SDL_GetJoystickInstanceVirtualGamepadInfo in SDL_joystick.o
      _SDL_JoystickNameForIndex in SDL_joystick.o
      _SDL_JoystickGetDeviceInstanceID in SDL_joystick.o
      _SDL_JoystickPathForIndex in SDL_joystick.o
      ...
  "_SDL_OpenFPFromBundleOrFallback", referenced from:
      _SDL_RWFromFile in SDL_rwops.o
  "___CFConstantStringClassReference", referenced from:
      CFString in native_midi_macosx.o
      CFString in native_midi_macosx.o
      CFString in native_midi_macosx.o
  "_kCFAllocatorDefault", referenced from:
      _macosx_load_soundfont in native_midi_macosx.o
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
make: *** [onsyuri_libretro.dylib] Error 1
macmini@MacminideMac-mini onsyuri_libretro % 



-----------
-Wl,-framework,AudioToolbox -Wl,-framework,AudioUnit -Wl,-framework,CoreServices

-framework CoreFoundation？？？

CMakeLists.txt
    if(WIN32)
	elseif(APPLE)
        target_sources(SDL2_mixer PRIVATE src/codecs/native_midi/native_midi_macosx.c)
        target_link_libraries(SDL2_mixer PRIVATE -Wl,-framework,AudioToolbox -Wl,-framework,AudioUnit -Wl,-framework,CoreServices)
	endf()	

Makefile
else ifneq (,$(findstring osx,$(platform)))
   TARGET := $(TARGET_NAME)_libretro.dylib
   fpic := -fPIC
--->   SHARED := -dynamiclib



"_IMG_InitTIF", referenced from:
  _IMG_Init in IMG.o
C:\work\onscripter-libretro_fork\onsyuri_libretro\deps\SDL_image\src\IMG_tif.c:
#if !(defined(__APPLE__) || defined(SDL_IMAGE_USE_WIC_BACKEND)) || defined(SDL_IMAGE_USE_COMMON_BACKEND)

SDL_IMAGE_USE_COMMON_BACKEND

------------------------


SDL_IOS_JoystickDriver,
if MACOS
SDL_JOYSTICK_DISABLED

---------------

SDL_OpenFPFromBundleOrFallback
if MACOS
SDL_FILE_DISABLED


/* #undef SDL_FILE_DISABLED */
/* #undef SDL_JOYSTICK_DISABLED */
#ifdef __APPLE__
#define SDL_FILE_DISABLED
#define SDL_JOYSTICK_DISABLED
#endif

----
  "___CFConstantStringClassReference", referenced from:
  "_kCFAllocatorDefault", referenced from:

-framework CoreFoundation

-----


