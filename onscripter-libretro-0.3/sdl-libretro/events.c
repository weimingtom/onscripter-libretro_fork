#include <SDL_libretro.h>
#include <sdl/src/events/SDL_events_c.h>
#include <sdl/src/video/dummy/SDL_nullevents_c.h>

void DUMMY_PumpEvents(_THIS)
{
}

void DUMMY_InitOSKeymap(_THIS)
{
}

void SDL_libretro_KeyboardCallback(bool down,
                                   unsigned keycode,
                                   uint32_t character,
                                   uint16_t key_modifiers)
{
  SDL_keysym sym;
  sym.sym = keycode;
  sym.mod = key_modifiers;
  sym.unicode = character;
  SDL_PrivateKeyboard(down ? SDL_PRESSED : SDL_RELEASED, &sym);
}
