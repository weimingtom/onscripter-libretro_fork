#ifndef _SDL_LIBRETRO_H
#define _SDL_LIBRETRO_H
#include <SDL.h>
#include <libretro.h>

#ifdef __cplusplus
extern "C" {
#endif

#if USE_TINYCO
void SDL_libretro_co_spawn(void (*fn)(void *), void *data, void *stack, size_t stack_size);
void SDL_libretro_video_refresh();
#endif

void SDL_libretro_co_yield(void);

#if USE_NOW
extern retro_usec_t SDL_libretro_now;
#endif

extern retro_audio_sample_batch_t SDL_libretro_audio_batch_cb;
extern retro_input_state_t SDL_libretro_input_state_cb;

#ifdef __cplusplus
}
#endif
#endif
