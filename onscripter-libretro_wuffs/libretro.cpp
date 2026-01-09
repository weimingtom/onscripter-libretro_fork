#include <SDL_libretro.h>
#include <retro_miscellaneous.h>
#include <file/file_path.h>
//don't use #include <onscripter/ONScripter.h>, use #include <ONScripter.h> instead (stop including wrong header file)  
#include <ONScripter.h>

retro_input_state_t  SDL_libretro_input_state_cb;
SDL_AudioSpec       *SDL_libretro_audio_spec = NULL;
SDL_sem             *SDL_libretro_event_sem  = NULL;

static void                        fallback_log(enum retro_log_level level, const char *fmt, ...);
static retro_log_printf_t          log_cb = fallback_log;
static retro_video_refresh_t       video_cb;
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
  SDL_libretro_input_state_cb = cb;
}

void retro_get_system_info(struct retro_system_info *info)
{
  info->need_fullpath = true;
  info->valid_extensions = "txt|dat|___|ons";
  info->library_version = "0.2";
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

  SDL_libretro_event_sem = SDL_CreateSemaphore(0);

  if (ons.openScript() != 0) {
    return false;
  }
  ons_thread = SDL_CreateThread(ons_main, NULL);

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

void retro_run(void)
{
  SDL_Surface *screen = SDL_GetVideoSurface();
  SDL_AudioSpec *spec = SDL_libretro_audio_spec;
  static const size_t max_frames = 2048;
  static int16_t stream[max_frames * 2];
  size_t frames = delta * 44100 / 1000;
  frames = (frames / 32 + 1) * 32;

  input_poll_cb();
  SDL_libretro_PumpEvents();
  video_cb(screen->pixels, screen->w, screen->h, screen->pitch);

  // XXX: convert audio format?
  if (spec && SDL_GetAudioStatus() == SDL_AUDIO_PLAYING && frames <= max_frames) {
    SDL_LockAudio();
    memset(stream, 0, frames * 4);
    spec->callback(NULL, (uint8_t *)stream, frames * 4);
    audio_batch_cb(stream, frames);
    SDL_UnlockAudio();
  }
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
  SDL_KillThread(ons_thread);
  SDL_DestroySemaphore(SDL_libretro_event_sem);
  SDL_Quit();
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
