#ifndef _SDL_LIBRETRO_H
#define _SDL_LIBRETRO_H
#include <SDL.h>
#include <libretro.h>

#ifdef __cplusplus
extern "C" {
#endif

void    SDL_libretro_RefreshVideo(retro_video_refresh_t video_cb);
void    SDL_libretro_ProduceAudio(retro_audio_sample_batch_t audio_batch_cb);
void    SDL_libretro_KeyboardCallback(bool down, unsigned keycode, uint32_t character, uint16_t key_modifiers);
int     SDL_PrivateKeyboard(Uint8 state, SDL_keysym *key);
int     SDL_PrivateMouseMotion(Uint8 buttonstate, int relative, Sint16 x, Sint16 y);
int     SDL_PrivateMouseButton(Uint8 state, Uint8 button, Sint16 x, Sint16 y);


#ifdef __cplusplus
}
#endif
#endif
