#include <SDL_libretro.h>
#include <sdl/src/audio/SDL_audiomem.h>
#include <sdl/src/audio/SDL_audio_c.h>
#include <sdl/src/audio/SDL_audiodev_c.h>
#include <sdl/src/audio/dummy/SDL_dummyaudio.h>
#include <queues/fifo_queue.h>

/* The tag name used by DUMMY audio */
#define DUMMYAUD_DRIVER_NAME         "dummy"

/* Audio driver functions */
static int DUMMYAUD_OpenAudio(_THIS, SDL_AudioSpec *spec);
static void DUMMYAUD_WaitAudio(_THIS);
static void DUMMYAUD_PlayAudio(_THIS);
static Uint8 *DUMMYAUD_GetAudioBuf(_THIS);
static void DUMMYAUD_CloseAudio(_THIS);

static SDL_AudioSpec *_spec = NULL;
static Uint8 *_mixbuf = NULL;
static fifo_buffer_t *_stream = NULL;
static SDL_mutex *_stream_lock = NULL;


/* Audio driver bootstrap functions */
static int DUMMYAUD_Available(void)
{
  return 1;
}

static void DUMMYAUD_DeleteDevice(SDL_AudioDevice *device)
{
  SDL_free(device->hidden);
  SDL_free(device);
}

static SDL_AudioDevice *DUMMYAUD_CreateDevice(int devindex)
{
  SDL_AudioDevice *this;

  /* Initialize all variables that we clean on shutdown */
  this = (SDL_AudioDevice *)SDL_malloc(sizeof(SDL_AudioDevice));
  if (this) {
    SDL_memset(this, 0, (sizeof *this));
    this->hidden = (struct SDL_PrivateAudioData *)
      SDL_malloc((sizeof *this->hidden));
  }
  if (this == NULL || this->hidden == NULL) {
    SDL_OutOfMemory();
    if (this) {
      SDL_free(this);
    }
    return 0;
  }
  SDL_memset(this->hidden, 0, (sizeof *this->hidden));

  /* Set the function pointers */
  this->OpenAudio = DUMMYAUD_OpenAudio;
  this->WaitAudio = DUMMYAUD_WaitAudio;
  this->PlayAudio = DUMMYAUD_PlayAudio;
  this->GetAudioBuf = DUMMYAUD_GetAudioBuf;
  this->CloseAudio = DUMMYAUD_CloseAudio;

  this->free = DUMMYAUD_DeleteDevice;

  return this;
}

AudioBootStrap DUMMYAUD_bootstrap = {
  DUMMYAUD_DRIVER_NAME, "SDL dummy audio driver",
  DUMMYAUD_Available, DUMMYAUD_CreateDevice
};


static void DUMMYAUD_WaitAudio(_THIS)
{
  SDL_mutexP(_stream_lock);
  while (this->enabled && FIFO_WRITE_AVAIL(_stream) < _spec->size) {
    SDL_mutexV(_stream_lock);
    SDL_Delay(50);
    SDL_mutexP(_stream_lock);
  }
  SDL_mutexV(_stream_lock);
}

static void DUMMYAUD_PlayAudio(_THIS)
{
  SDL_mutexP(_stream_lock);
  fifo_write(_stream, _mixbuf, _spec->size);
  SDL_mutexV(_stream_lock);
}

static Uint8 *DUMMYAUD_GetAudioBuf(_THIS)
{
  return _mixbuf;
}

static void DUMMYAUD_CloseAudio(_THIS)
{
  if (_mixbuf != NULL) {
    SDL_FreeAudioMem(_mixbuf);
    _mixbuf = NULL;
  }
  if (_stream != NULL) {
    fifo_free(_stream);
    _stream = NULL;
  };
  if (_stream_lock != NULL) {
    SDL_DestroyMutex(_stream_lock);
    _stream_lock = NULL;
  }
}

static int DUMMYAUD_OpenAudio(_THIS, SDL_AudioSpec *spec)
{
  _mixbuf = SDL_AllocAudioMem(spec->size);
  if (_mixbuf == NULL)
    return -1;

  _stream = fifo_new(spec->size * 2);
  if (_stream == NULL)
    return -1;

  _stream_lock = SDL_CreateMutex();
  if (_stream_lock == NULL)
    return -1;

  _spec = spec;

  return 0;
}

void SDL_libretro_ProduceAudio(retro_audio_sample_batch_t audio_batch_cb)
{
  static int16_t buffer[2048];
  static const size_t samples = 44100 / 60;

  if (SDL_GetAudioStatus() != SDL_AUDIO_PLAYING)
    return;

  SDL_mutexP(_stream_lock);
  if (FIFO_READ_AVAIL(_stream) < samples * 4) {
    // XXX: underrun!
    SDL_mutexV(_stream_lock);
    return;
  }
  fifo_read(_stream, buffer, samples * 4);
  SDL_mutexV(_stream_lock);
  audio_batch_cb(buffer, samples);
}
