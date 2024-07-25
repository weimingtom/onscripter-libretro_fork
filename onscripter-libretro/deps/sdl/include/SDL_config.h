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
#if !defined(__MINGW32__)
#define HAVE_CLOCK_GETTIME 1
#define HAVE_NANOSLEEP 1
#endif

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

//#ifdef _POSIX
#if defined(__MINGW32__) && !defined(SIGHUP)
#define	SIGHUP	1	/* hangup */
#define	SIGQUIT	3	/* quit */
#define	SIGTRAP	5	/* trace trap (not reset when caught) */
#define SIGIOT  6       /* IOT instruction */
#define	SIGEMT	7	/* EMT instruction */
#define	SIGKILL	9	/* kill (cannot be caught or ignored) */
#define	SIGBUS	10	/* bus error */
#define	SIGSYS	12	/* bad argument to system call */
#define	SIGPIPE	13	/* write on a pipe with no one to read it */
#define	SIGALRM	14	/* alarm clock */

#define SIGCHLD 15
#define SIGWINCH 16
#define SIGVTALRM 17
#define SIGPROF 18

#endif

#endif /* _SDL_config_h */
