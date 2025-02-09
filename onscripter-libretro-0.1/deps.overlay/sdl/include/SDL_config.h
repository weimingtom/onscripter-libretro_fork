#ifndef _SDL_config_h
#define _SDL_config_h
#include "SDL_platform.h"

/* C datatypes */
#define SDL_HAS_64BIT_TYPE 1

/* Endianness */
#define SDL_BYTEORDER 1234

/* Useful headers */
#define HAVE_STDIO_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STDARG_H 1
#define HAVE_STRING_H 1
#define HAVE_STDINT_H 1

/* C library functions */
#define HAVE_MALLOC
#define HAVE_CALLOC
#define HAVE_REALLOC
#define HAVE_FREE
#define HAVE_ALLOCA
#define HAVE_MEMSET
#define HAVE_MEMCPY
#define HAVE_MEMMOVE
#define HAVE_MEMCMP

/* Other functions */
#define HAVE_SEM_TIMEDWAIT 1
#define HAVE_CLOCK_GETTIME 1
#define HAVE_NANOSLEEP 1

/* Enable various drivers */
#define SDL_AUDIO_DRIVER_DUMMY 1
#define SDL_CDROM_DISABLED 1
#define SDL_JOYSTICK_DISABLED 1
#define SDL_LOADSO_DISABLED 1
#define SDL_THREAD_PTHREAD 1
#define SDL_THREAD_PTHREAD_RECURSIVE_MUTEX 1
#define SDL_TIMER_UNIX 1
#define SDL_VIDEO_DRIVER_DUMMY 1

#ifdef ANDROID
#define SDL_BLENDMODE_NONE 0
#define SDL_SetSurfaceBlendMode(surface, blendMode) 0
#endif

#endif /* _SDL_config_h */
