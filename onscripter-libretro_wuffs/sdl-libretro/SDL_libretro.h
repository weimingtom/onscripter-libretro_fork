#ifndef _SDL_LIBRETRO_H
#define _SDL_LIBRETRO_H
#include <SDL.h>
#include <libretro.h>

#ifdef __cplusplus
extern "C" {
#endif

extern SDL_AudioSpec       *SDL_libretro_audio_spec;
extern retro_input_state_t  SDL_libretro_input_state_cb;
extern SDL_sem             *SDL_libretro_event_sem;
void                        SDL_libretro_PumpEvents(void);

#ifdef __cplusplus
}
#endif
#endif
