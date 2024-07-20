#include <SDL_libretro.h>
#include <retro_miscellaneous.h>
#include <file/file_path.h>
#include <libco.h>
#define USE_ONS 1
#if USE_ONS
#include <onscripter/ONScripter.h>
#endif

retro_usec_t SDL_libretro_now = 0;
retro_audio_sample_batch_t SDL_libretro_audio_batch_cb = 0;
retro_input_state_t SDL_libretro_input_state_cb = 0;

static void fallback_log(enum retro_log_level level, const char *fmt, ...);
static retro_video_refresh_t video_cb = 0;
static retro_input_poll_t input_poll_cb = 0;

static retro_log_printf_t log_cb = fallback_log;
static retro_environment_t environ_cb = 0;
#if USE_ONS
static ONScripter ons;
#endif
static cothread_t retro_ct, ons_ct;


void SDL_libretro_co_yield(void)
{
fprintf(stderr, "SDL_libretro_co_yield\n");
  co_switch(retro_ct);
}

void SDL_libretro_video_refresh()
{
fprintf(stderr, "SDL_libretro_video_refresh -1\n");
  static SDL_Surface *screen = SDL_GetVideoSurface();
fprintf(stderr, "SDL_libretro_video_refresh -2\n");
if (video_cb && screen && screen->pixels) {
fprintf(stderr, "SDL_libretro_video_refresh -3\n");
  video_cb(screen->pixels, screen->w, screen->h, screen->pitch);
fprintf(stderr, "SDL_libretro_video_refresh -4\n");
}
fprintf(stderr, "SDL_libretro_video_refresh\n");
}

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
fprintf(stderr, "retro_api_version\n");
  return RETRO_API_VERSION;
}

static void on_frame_time(retro_usec_t usec)
{
fprintf(stderr, "on_frame_time\n");
  SDL_libretro_now += usec;
}

void retro_set_environment(retro_environment_t cb)
{
  static struct retro_log_callback log;
  environ_cb = cb;
  if (environ_cb && environ_cb(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &log))
    log_cb = log.log;

  static struct retro_frame_time_callback frame_time = {
    .callback = on_frame_time,
    .reference = 1000000 / 60,
  };
  environ_cb(RETRO_ENVIRONMENT_SET_FRAME_TIME_CALLBACK, &frame_time);
fprintf(stderr, "retro_set_environment\n");
}

void retro_set_video_refresh(retro_video_refresh_t cb)
{
  video_cb = cb;
fprintf(stderr, "retro_set_video_refresh\n");
}

void retro_set_audio_sample(retro_audio_sample_t cb)
{
fprintf(stderr, "retro_set_audio_sample\n");
}

void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb)
{
  SDL_libretro_audio_batch_cb = cb;
printf("retro_set_audio_sample_batch\n");
}

void retro_set_input_poll(retro_input_poll_t cb)
{
  input_poll_cb = cb;
fprintf(stderr, "retro_set_input_poll\n");
}

void retro_set_input_state(retro_input_state_t cb)
{
  SDL_libretro_input_state_cb = cb;
fprintf(stderr, "retro_set_input_state\n");
}

void retro_get_system_info(struct retro_system_info *info)
{
  info->need_fullpath = true;
  info->valid_extensions = "txt|dat|___";
  info->library_version = "0.1";
  info->library_name = "onscripter";
  info->block_extract = false;
fprintf(stderr, "retro_get_system_info\n");
}

void retro_get_system_av_info(struct retro_system_av_info *info)
{
fprintf(stderr, "retro_get_system_av_info 0\n");
#if USE_ONS
  int width = ons.getWidth();
  int height = ons.getHeight();
#else
  int width = 480;
  int height = 640;
#endif
  info->geometry.base_width = width;
  info->geometry.base_height = height;
  info->geometry.max_width = width;
  info->geometry.max_height = height;
  info->timing.fps = 60.0;
  info->timing.sample_rate = 44100.0;
fprintf(stderr, "retro_get_system_av_info\n");
}

static void ons_main(void)
{
fprintf(stderr, "ons_main 1\n");
#if USE_ONS
  if (ons.init()) {
    if (log_cb) log_cb(RETRO_LOG_ERROR, "Failed to initialize ONScripter\n");
    return;
  }
fprintf(stderr, "ons_main 2\n");
  SDL_ShowCursor(SDL_DISABLE);
fprintf(stderr, "ons_main 3\n");
  ons.executeLabel();
#endif
fprintf(stderr, "ons_main 4\n");
}

void retro_init(void)
{
  enum retro_pixel_format pixfmt = RETRO_PIXEL_FORMAT_XRGB8888;
  environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &pixfmt);
  retro_ct = co_active();
  ons_ct = co_create(65536*8, ons_main);
fprintf(stderr, "retro_init\n");
}

bool retro_load_game(const struct retro_game_info *game)
{
fprintf(stderr, "retro_load_game\n");
  if (!game)
    return false;

  char archive_path[PATH_MAX_LENGTH];
  fill_pathname_basedir(archive_path, game->path, sizeof(archive_path));
#if USE_ONS
  ons.setArchivePath(archive_path);

  if (ons.openScript() != 0) {
    return false;
  }
#endif
fprintf(stderr, "retro_load_game 2\n");
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
fprintf(stderr, "retro_reset 1\n");
#if USE_ONS
  ons.resetCommand();
#endif
fprintf(stderr, "retro_reset 2\n");
}

void retro_run(void)
{
fprintf(stderr, "retro_run 1\n");
  co_switch(ons_ct);
fprintf(stderr, "retro_run 2\n");
if (input_poll_cb) {
  input_poll_cb();
}
fprintf(stderr, "retro_run 3\n");
  SDL_libretro_video_refresh();
fprintf(stderr, "retro_run 4\n");
}

size_t retro_serialize_size(void)
{
fprintf(stderr, "retro_serialize_size\n");
  return 0;
}

bool retro_serialize(void *data, size_t size)
{
fprintf(stderr, "retro_serialize\n");
  return false;
}

bool retro_unserialize(const void *data, size_t size)
{
fprintf(stderr, "retro_unserialize\n");
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
fprintf(stderr, "retro_unload_game\n");
  SDL_Quit();
}

unsigned retro_get_region(void)
{
fprintf(stderr, "retro_get_region\n");
  return RETRO_REGION_NTSC;
}

void *retro_get_memory_data(unsigned id)
{
fprintf(stderr, "retro_get_memory_data\n");
  return 0;
}

size_t retro_get_memory_size(unsigned id)
{
fprintf(stderr, "retro_get_memory_size\n");
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
  if (log_cb) log_cb(RETRO_LOG_INFO, fmt, va);
  va_end(va);
  return 0;
}
}
#endif
