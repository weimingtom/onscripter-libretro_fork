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
fprintf(stderr, "DUMMYAUD_Available\n");
  return 1;
}

static void DUMMYAUD_DeleteDevice(SDL_AudioDevice *device)
{
fprintf(stderr, "DUMMYAUD_DeleteDevice 1\n");
  SDL_free(device->hidden);
fprintf(stderr, "DUMMYAUD_DeleteDevice 2\n");
  SDL_free(device);
fprintf(stderr, "DUMMYAUD_DeleteDevice 3\n");
}

static SDL_AudioDevice *DUMMYAUD_CreateDevice(int devindex)
{
  SDL_AudioDevice *this;
fprintf(stderr, "DUMMYAUD_CreateDevice 1\n");
  /* Initialize all variables that we clean on shutdown */
  this = (SDL_AudioDevice *)SDL_malloc(sizeof(SDL_AudioDevice));
  if (this) {
    SDL_memset(this, 0, (sizeof *this));
    this->hidden = (struct SDL_PrivateAudioData *)
      SDL_malloc((sizeof *this->hidden));
  }
fprintf(stderr, "DUMMYAUD_CreateDevice 2\n");
  if (this == NULL || this->hidden == NULL) {
    SDL_OutOfMemory();
fprintf(stderr, "DUMMYAUD_CreateDevice 3\n");
    if (this) {
fprintf(stderr, "DUMMYAUD_CreateDevice 4\n");
      SDL_free(this);
fprintf(stderr, "DUMMYAUD_CreateDevice 5\n");
    }
fprintf(stderr, "DUMMYAUD_CreateDevice 6\n");
    return 0;
  }
fprintf(stderr, "DUMMYAUD_CreateDevice 7\n");
  SDL_memset(this->hidden, 0, (sizeof *this->hidden));
fprintf(stderr, "DUMMYAUD_CreateDevice 8\n");
  /* Set the function pointers */
  this->OpenAudio = DUMMYAUD_OpenAudio;
  this->WaitAudio = DUMMYAUD_WaitAudio;
  this->PlayAudio = DUMMYAUD_PlayAudio;
  this->GetAudioBuf = DUMMYAUD_GetAudioBuf;
  this->CloseAudio = DUMMYAUD_CloseAudio;

  this->free = DUMMYAUD_DeleteDevice;
fprintf(stderr, "DUMMYAUD_CreateDevice 9\n");
  return this;
}

AudioBootStrap DUMMYAUD_bootstrap = {
  DUMMYAUD_DRIVER_NAME, "SDL dummy audio driver",
  DUMMYAUD_Available, DUMMYAUD_CreateDevice
};


static void DUMMYAUD_WaitAudio(_THIS)
{
fprintf(stderr, "DUMMYAUD_WaitAudio 1\n");
}

static void DUMMYAUD_PlayAudio(_THIS)
{
fprintf(stderr, "DUMMYAUD_PlayAudio 1\n");
  SDL_AudioSpec *spec = &this->spec;
fprintf(stderr, "DUMMYAUD_PlayAudio 2\n");
  Sint16 *ptr=(Sint16*)this->hidden->mixbuf;
fprintf(stderr, "DUMMYAUD_PlayAudio 3\n");
if (SDL_libretro_audio_batch_cb && ptr && spec && spec->samples) { 
  SDL_libretro_audio_batch_cb(ptr, spec->samples);
}
fprintf(stderr, "DUMMYAUD_PlayAudio 4\n");

}

static Uint8 *DUMMYAUD_GetAudioBuf(_THIS)
{
fprintf(stderr, "DUMMYAUD_GetAudioBuf 1\n");

  return(this->hidden->mixbuf);
}

static void DUMMYAUD_CloseAudio(_THIS)
{
fprintf(stderr, "DUMMYAUD_CloseAudio 1\n");

  if (this->hidden->mixbuf != NULL) {
fprintf(stderr, "DUMMYAUD_CloseAudio 2\n");
    SDL_FreeAudioMem(this->hidden->mixbuf);
fprintf(stderr, "DUMMYAUD_CloseAudio 3\n");
    this->hidden->mixbuf = NULL;
  }
}


static int DUMMYAUD_OpenAudio(_THIS, SDL_AudioSpec *spec)
{
fprintf(stderr, "DUMMYAUD_OpenAudio 1\n");
  spec->samples = 512;
  SDL_CalculateAudioSpec(spec);
  this->hidden->mixlen = spec->size;
  this->hidden->mixbuf = (Uint8 *)SDL_AllocAudioMem(this->hidden->mixlen);
fprintf(stderr, "DUMMYAUD_OpenAudio 2\n");
  if (this->hidden->mixbuf == NULL) {
fprintf(stderr, "DUMMYAUD_OpenAudio 3\n");
    return -1;
  }
fprintf(stderr, "DUMMYAUD_OpenAudio 4\n");
  SDL_memset(this->hidden->mixbuf, spec->silence, spec->size);
fprintf(stderr, "DUMMYAUD_OpenAudio 5\n");
  /* We're ready to rock and roll. :-) */
  return 0;
}
