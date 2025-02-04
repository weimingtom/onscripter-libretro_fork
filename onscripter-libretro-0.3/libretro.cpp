#include <SDL_libretro.h>
#include <retro_miscellaneous.h>
#include <file/file_path.h>
#include <onscripter/ONScripter.h>

static void                        fallback_log(enum retro_log_level level, const char *fmt, ...);
static retro_log_printf_t          log_cb = fallback_log;
static retro_video_refresh_t       video_cb;
static retro_input_state_t         input_state_cb;
static retro_input_poll_t          input_poll_cb;
static retro_audio_sample_batch_t  audio_batch_cb;
static retro_environment_t         environ_cb;
static ONScripter                  ons;
static SDL_Thread                 *ons_thread;
static uint32_t                    delta;


static void fallback_log(enum retro_log_level level, const char *fmt, ...)
{
  (void)level;
  va_list va;
  va_start(va, fmt);
  vfprintf(stderr, fmt, va);
  va_end(va);
}

unsigned retro_api_version(void)
{
  return RETRO_API_VERSION;
}

void retro_set_environment(retro_environment_t cb)
{
  static struct retro_log_callback log;
  environ_cb = cb;
  if (environ_cb(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &log))
    log_cb = log.log;
}

void retro_set_video_refresh(retro_video_refresh_t cb)
{
  video_cb = cb;
}

void retro_set_audio_sample(retro_audio_sample_t cb)
{
}

void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb)
{
  audio_batch_cb = cb;
}

void retro_set_input_poll(retro_input_poll_t cb)
{
  input_poll_cb = cb;
}

void retro_set_input_state(retro_input_state_t cb)
{
  input_state_cb = cb;
}

void retro_get_system_info(struct retro_system_info *info)
{
  info->need_fullpath = true;
  info->valid_extensions = "txt|dat|___|ons";
  info->library_version = "0.3";
  info->library_name = "onscripter";
  info->block_extract = false;
}

void retro_get_system_av_info(struct retro_system_av_info *info)
{
  int width = ons.getWidth();
  int height = ons.getHeight();
  info->geometry.base_width = width;
  info->geometry.base_height = height;
  info->geometry.max_width = width;
  info->geometry.max_height = height;
  info->geometry.aspect_ratio = 0.0;
  info->timing.fps = 60.0;
  info->timing.sample_rate = 44100.0;
}

static void frame_cb(retro_usec_t usec)
{
  delta = usec / 1000;
}

void retro_init(void)
{
  enum retro_pixel_format pixfmt = RETRO_PIXEL_FORMAT_XRGB8888;
  struct retro_frame_time_callback frametime = {
    .callback = frame_cb,
    .reference = 1000000 / 60,
  };
  environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &pixfmt);
  environ_cb(RETRO_ENVIRONMENT_SET_FRAME_TIME_CALLBACK, &frametime);
}

static int ons_main(void *data)
{
  if (ons.init()) {
    log_cb(RETRO_LOG_ERROR, "Failed to initialize ONScripter\n");
    return -1;
  }

  SDL_ShowCursor(SDL_DISABLE);
  ons.executeLabel();
  return 0;
}

bool retro_load_game(const struct retro_game_info *game)
{
  if (!game)
    return false;

  char archive_path[PATH_MAX_LENGTH];
  fill_pathname_basedir(archive_path, game->path, sizeof(archive_path));
  ons.setArchivePath(archive_path);

  if (ons.openScript() != 0) {
    return false;
  }
  ons_thread = SDL_CreateThread(ons_main, NULL);

  struct retro_keyboard_callback keyboard = {
    .callback = SDL_libretro_KeyboardCallback,
  };
  environ_cb(RETRO_ENVIRONMENT_SET_KEYBOARD_CALLBACK, &keyboard);

  return true;
}

void retro_set_controller_port_device(unsigned port, unsigned device)
{
}

void retro_deinit(void)
{
}

void retro_reset(void)
{
  ons.resetCommand();
}

static void pump_joypad_events(void)
{
  static SDL_keysym sym;
  static int16_t buttons[16] = {0};
  static const SDLKey bkeys[16] = {
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
    int16_t state = input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i);
    SDLKey k = bkeys[i];
    if (k && buttons[i] != state) {
      buttons[i] = state;
      sym.scancode = k;
      sym.sym = k;
      SDL_PrivateKeyboard(state ? SDL_PRESSED : SDL_RELEASED, &sym);
    }
  }
}

static Uint8 pressed_to_button(int16_t pressed)
{
  if (pressed == 1)
    return SDL_BUTTON_LEFT;
  if (pressed == 2)
    return SDL_BUTTON_RIGHT;
  return 0;
}

static void pump_mouse_events(void)
{
  static Sint16 x = 0;
  static Sint16 y = 0;
  static Uint8 btn = 0;
  static int16_t pressed = 0;

  SDL_Surface *screen = SDL_GetVideoSurface();
  int16_t _x = input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_X);
  int16_t _y = input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_Y);
  int16_t _pressed = 0;

  _x = screen->w * (_x + 0x7fff) / 0xffff;
  _y = screen->h * (_y + 0x7fff) / 0xffff;
  if (x != _x || y != _y) {
    x = _x;
    y = _y;
    SDL_PrivateMouseMotion(0, 0, x, y);
  }

  while (input_state_cb(0, RETRO_DEVICE_POINTER, _pressed, RETRO_DEVICE_ID_POINTER_PRESSED)) {
    _pressed += 1;
  }

  if (input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_LEFT)) {
    _pressed = 1;
  }
  if (input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_RIGHT)) {
    _pressed = 2;
  }

  if (pressed) {
    if (!_pressed) {
      btn = pressed_to_button(pressed);
      SDL_PrivateMouseButton(SDL_RELEASED, btn, x, y);
      pressed = 0;
    }
  } else {
    if (_pressed) {
      btn = pressed_to_button(_pressed);
      SDL_PrivateMouseButton(SDL_PRESSED, btn, x, y);
      pressed = _pressed;
    }
  }
}

void retro_run(void)
{
  if (SDL_GetVideoSurface() == NULL)
    return;

  input_poll_cb();
  pump_joypad_events();
  pump_mouse_events();
  SDL_libretro_RefreshVideo(video_cb);
  SDL_libretro_ProduceAudio(audio_batch_cb);
}

size_t retro_serialize_size(void)
{
  return 0;
}

bool retro_serialize(void *data, size_t size)
{
  return false;
}

bool retro_unserialize(const void *data, size_t size)
{
  return false;
}

void retro_cheat_reset(void) {}
void retro_cheat_set(unsigned index, bool enabled, const char *code) {}

bool retro_load_game_special(unsigned game_type, const struct retro_game_info *info, size_t num_info)
{
  return false;
}

void retro_unload_game(void)
{
  SDL_Event event;
  event.type = SDL_QUIT;
  SDL_PushEvent(&event);
  SDL_WaitThread(ons_thread, NULL);
}

unsigned retro_get_region(void)
{
  return RETRO_REGION_NTSC;
}

void *retro_get_memory_data(unsigned id)
{
  return 0;
}

size_t retro_get_memory_size(unsigned id)
{
  return 0;
}


#ifdef ANDROID
extern "C" {
#undef fseek
int fseek_ons(FILE *stream, long offset, int whence) {
  return fseek(stream, offset, whence);
}

#undef ftell
long ftell_ons(FILE *stream) {
  return ftell(stream);
}

#undef fgetc
int fgetc_ons(FILE *stream) {
  return fgetc(stream);
}

#undef fgets
char *fgets_ons(char *s, int size, FILE *stream) {
  return fgets(s, size, stream);
}

#undef fread
size_t fread_ons(void *ptr, size_t size, size_t nmemb, FILE *stream) {
  return fread(ptr, size, nmemb, stream);
}

#undef fopen
FILE *fopen_ons(const char *str, const char *mode) {
  return fopen(str, mode);
}

#undef mkdir
extern int mkdir(const char *pathname, mode_t mode);
int mkdir_ons(const char *pathname, mode_t mode) {
  return mkdir(pathname, mode);
}

void playVideoAndroid(const char *filename) {}
int __android_log_print(int prio, const char *tag, const char *fmt, ...) {
  va_list va;
  va_start(va, fmt);
  log_cb(RETRO_LOG_INFO, fmt, va);
  va_end(va);
  return 0;
}
}
#endif
