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

  static int16_t buttons[16] = {0};
  static const int bkeys[16] = {
    [RETRO_DEVICE_ID_JOYPAD_B]      = SDLK_SPACE,
    [RETRO_DEVICE_ID_JOYPAD_Y]      = SDLK_RCTRL,
    [RETRO_DEVICE_ID_JOYPAD_SELECT] = SDLK_0,
    [RETRO_DEVICE_ID_JOYPAD_START]  = SDLK_a,
    [RETRO_DEVICE_ID_JOYPAD_UP]     = SDLK_UP,
    [RETRO_DEVICE_ID_JOYPAD_DOWN]   = SDLK_DOWN,
    [RETRO_DEVICE_ID_JOYPAD_LEFT]   = SDLK_LEFT,
    [RETRO_DEVICE_ID_JOYPAD_RIGHT]  = SDLK_RIGHT,
    [RETRO_DEVICE_ID_JOYPAD_A]      = SDLK_RETURN,
    [RETRO_DEVICE_ID_JOYPAD_X]      = SDLK_ESCAPE,
    [RETRO_DEVICE_ID_JOYPAD_L]      = SDLK_o,
    [RETRO_DEVICE_ID_JOYPAD_R]      = SDLK_s,
    [RETRO_DEVICE_ID_JOYPAD_L2]     = SDLK_PAGEUP,
    [RETRO_DEVICE_ID_JOYPAD_R2]     = SDLK_PAGEDOWN,
    [RETRO_DEVICE_ID_JOYPAD_L3]     = SDLK_TAB,
    [RETRO_DEVICE_ID_JOYPAD_R3]     = SDLK_q,
  };
  for (int i = 0; i < 16; ++i) {
    int16_t state = SDL_libretro_input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i);
    int k = bkeys[i];
    if (k && buttons[i] != state) {
      buttons[i] = state;
      sym.scancode = k;
      sym.sym = k;
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
#if 0
//no mouse move
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
#else
//with mouse move
//see github.com/madcock/libretro-onscripter
  static Sint16 x = 0;
  static Sint16 y = 0;
  static Uint8 btn = 0;
  static int16_t pressed = 0;

  SDL_Surface *screen = SDL_GetVideoSurface();
  int16_t _x = SDL_libretro_input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_X);
  int16_t _y = SDL_libretro_input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_Y);
  int16_t _pressed = 0;

  _x = screen->w * (_x + 0x7fff) / 0xffff;
  _y = screen->h * (_y + 0x7fff) / 0xffff;
  if (x != _x || y != _y) {
    x = _x;
    y = _y;
    SDL_PrivateMouseMotion(0, 0, x, y);
  }

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
      btn = to_button(_pressed);
      SDL_PrivateMouseButton(SDL_PRESSED, btn, x, y);
      pressed = _pressed;
    }
  }
#endif
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
