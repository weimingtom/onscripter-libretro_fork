#include <SDL_libretro.h>
#include <sdl/src/events/SDL_events_c.h>
#include <sdl/src/video/dummy/SDL_nullevents_c.h>


static void PumpKeyboardEvents(void)
{
  static int16_t keys[RETROK_LAST] = {0};
  static SDL_keysym sym;
  for (int i = 0; i < RETROK_LAST; ++i) {
    int16_t state = SDL_libretro_input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0, i);
    if (keys[i] != state) {
      keys[i] = state;
      sym.scancode = i;
      sym.sym = i;
      SDL_PrivateKeyboard(state ? SDL_PRESSED : SDL_RELEASED, &sym);
    }
  }
}

static Uint8 to_button(int16_t pressed)
{
  if (pressed == 1)
    return SDL_BUTTON_LEFT;
  if (pressed == 2)
    return SDL_BUTTON_RIGHT;
  return 0;
}

static void PumpMouseEvents(void)
{
  static Sint16 x = 0;
  static Sint16 y = 0;
  static Uint8 btn = 0;
  static int16_t pressed = 0;

  SDL_Surface *screen = SDL_GetVideoSurface();
  int16_t _x = SDL_libretro_input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_X);
  int16_t _y = SDL_libretro_input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_Y);
  int16_t _pressed = 0;

  while (SDL_libretro_input_state_cb(0, RETRO_DEVICE_POINTER, _pressed, RETRO_DEVICE_ID_POINTER_PRESSED)) {
    _pressed += 1;
  }

  if (SDL_libretro_input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_LEFT)) {
    _pressed = 1;
  }
  if (SDL_libretro_input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_RIGHT)) {
    _pressed = 2;
  }

  if (pressed) {
    if (!_pressed) {
      btn = to_button(pressed);
      SDL_PrivateMouseButton(SDL_RELEASED, btn, x, y);
      pressed = 0;
    }
  } else {
    if (_pressed) {
      x = screen->w * (_x + 0x7fff) / 0xffff;
      y = screen->h * (_y + 0x7fff) / 0xffff;
      btn = to_button(_pressed);
      SDL_WarpMouse(x, y);
      SDL_PrivateMouseButton(SDL_PRESSED, btn, 0, 0);
      pressed = _pressed;
    }
  }
}

void DUMMY_PumpEvents(_THIS)
{
  PumpKeyboardEvents();
  PumpMouseEvents();
  SDL_libretro_co_yield();
}

void DUMMY_InitOSKeymap(_THIS)
{
}
