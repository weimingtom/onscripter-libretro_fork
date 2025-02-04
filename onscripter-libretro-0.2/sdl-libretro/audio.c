#include <SDL_libretro.h>
#include <sdl/src/audio/SDL_audiomem.h>
#include <sdl/src/audio/SDL_audio_c.h>
#include <sdl/src/audio/SDL_audiodev_c.h>
#include <sdl/src/audio/dummy/SDL_dummyaudio.h>

/* The tag name used by DUMMY audio */
#define DUMMYAUD_DRIVER_NAME         "dummy"

/* Audio driver functions */
static int DUMMYAUD_OpenAudio(_THIS, SDL_AudioSpec *spec);
static void DUMMYAUD_WaitAudio(_THIS);
static void DUMMYAUD_PlayAudio(_THIS);
static Uint8 *DUMMYAUD_GetAudioBuf(_THIS);
static void DUMMYAUD_CloseAudio(_THIS);

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
  SDL_Delay(10);
}

static void DUMMYAUD_PlayAudio(_THIS)
{
  SDL_AudioSpec *spec = &this->spec;
  Sint16 *ptr=(Sint16*)this->hidden->mixbuf;
  SDL_libretro_audio_batch_cb(ptr, spec->samples);
}

static Uint8 *DUMMYAUD_GetAudioBuf(_THIS)
{
  return(this->hidden->mixbuf);
}

static void DUMMYAUD_CloseAudio(_THIS)
{
  if (this->hidden->mixbuf != NULL) {
    SDL_FreeAudioMem(this->hidden->mixbuf);
    this->hidden->mixbuf = NULL;
  }
}


static int DUMMYAUD_OpenAudio(_THIS, SDL_AudioSpec *spec)
{
  spec->samples = 512;
  SDL_CalculateAudioSpec(spec);
  this->hidden->mixlen = spec->size;
  this->hidden->mixbuf = (Uint8 *)SDL_AllocAudioMem(this->hidden->mixlen);
  if (this->hidden->mixbuf == NULL) {
    return -1;
  }
  SDL_memset(this->hidden->mixbuf, spec->silence, spec->size);

  /* We're ready to rock and roll. :-) */
  return 0;
}
