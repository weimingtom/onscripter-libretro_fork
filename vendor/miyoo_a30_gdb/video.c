#include <SDL_libretro.h>
#include <sdl/src/video/SDL_pixels_c.h>
#include <sdl/src/video/dummy/SDL_nullvideo.h>
#include <sdl/src/video/dummy/SDL_nullevents_c.h>
#include <sdl/src/video/dummy/SDL_nullmouse_c.h>


#define DUMMYVID_DRIVER_NAME "dummy"

/* Initialization/Query functions */
static int DUMMY_VideoInit(_THIS, SDL_PixelFormat *vformat);
static SDL_Rect **DUMMY_ListModes(_THIS, SDL_PixelFormat *format, Uint32 flags);
static SDL_Surface *DUMMY_SetVideoMode(_THIS, SDL_Surface *current, int width, int height, int bpp, Uint32 flags);
static int DUMMY_SetColors(_THIS, int firstcolor, int ncolors, SDL_Color *colors);
static void DUMMY_VideoQuit(_THIS);

/* Hardware surface functions */
static int DUMMY_AllocHWSurface(_THIS, SDL_Surface *surface);
static int DUMMY_LockHWSurface(_THIS, SDL_Surface *surface);
static void DUMMY_UnlockHWSurface(_THIS, SDL_Surface *surface);
static void DUMMY_FreeHWSurface(_THIS, SDL_Surface *surface);

/* etc. */
static void DUMMY_UpdateRects(_THIS, int numrects, SDL_Rect *rects);

/* DUMMY driver bootstrap functions */

static int DUMMY_Available(void)
{
fprintf(stderr, "DUMMY_Available 1\n");
  return 1;
}

static void DUMMY_DeleteDevice(SDL_VideoDevice *device)
{
fprintf(stderr, "DUMMY_DeleteDevice 1\n");
  SDL_free(device->hidden);
fprintf(stderr, "DUMMY_DeleteDevice 2\n");
  SDL_free(device);
fprintf(stderr, "DUMMY_DeleteDevice 3\n");
}

static SDL_VideoDevice *DUMMY_CreateDevice(int devindex)
{
  SDL_VideoDevice *device;

fprintf(stderr, "DUMMY_CreateDevice 1\n");
  /* Initialize all variables that we clean on shutdown */
  device = (SDL_VideoDevice *)SDL_malloc(sizeof(SDL_VideoDevice));
  if (device) {
    SDL_memset(device, 0, (sizeof *device));
    device->hidden = (struct SDL_PrivateVideoData *)
      SDL_malloc(sizeof(*device->hidden));
  }
fprintf(stderr, "DUMMY_CreateDevice 2\n");
  if (device == NULL || device->hidden == NULL) {
fprintf(stderr, "DUMMY_CreateDevice 3\n");
    SDL_OutOfMemory();
fprintf(stderr, "DUMMY_CreateDevice 4\n");
    if (device) {
fprintf(stderr, "DUMMY_CreateDevice 5\n");
      SDL_free(device);
    }
fprintf(stderr, "DUMMY_CreateDevice 6\n");
    return 0;
  }
  SDL_memset(device->hidden, 0, sizeof(*device->hidden));
fprintf(stderr, "DUMMY_CreateDevice 7\n");
  /* Set the function pointers */
  device->VideoInit = DUMMY_VideoInit;
  device->ListModes = DUMMY_ListModes;
  device->SetVideoMode = DUMMY_SetVideoMode;
  device->CreateYUVOverlay = NULL;
  device->SetColors = DUMMY_SetColors;
  device->UpdateRects = DUMMY_UpdateRects;
  device->VideoQuit = DUMMY_VideoQuit;
  device->AllocHWSurface = DUMMY_AllocHWSurface;
  device->CheckHWBlit = NULL;
  device->FillHWRect = NULL;
  device->SetHWColorKey = NULL;
  device->SetHWAlpha = NULL;
  device->LockHWSurface = DUMMY_LockHWSurface;
  device->UnlockHWSurface = DUMMY_UnlockHWSurface;
  device->FlipHWSurface = NULL;
  device->FreeHWSurface = DUMMY_FreeHWSurface;
  device->SetCaption = NULL;
  device->SetIcon = NULL;
  device->IconifyWindow = NULL;
  device->GrabInput = NULL;
  device->GetWMInfo = NULL;
  device->InitOSKeymap = DUMMY_InitOSKeymap;
  device->PumpEvents = DUMMY_PumpEvents;

  device->free = DUMMY_DeleteDevice;
fprintf(stderr, "DUMMY_CreateDevice 8\n");
  return device;
}

VideoBootStrap DUMMY_bootstrap = {
  DUMMYVID_DRIVER_NAME, "SDL dummy video driver",
  DUMMY_Available, DUMMY_CreateDevice
};


int DUMMY_VideoInit(_THIS, SDL_PixelFormat *vformat)
{
fprintf(stderr, "DUMMY_VideoInit 1\n");
  /*
    fprintf(stderr, "WARNING: You are using the SDL dummy video driver!\n");
  */

  /* Determine the screen depth (use default 8-bit depth) */
  /* we change this during the SDL_SetVideoMode implementation... */
  vformat->BitsPerPixel = 8;
  vformat->BytesPerPixel = 1;
fprintf(stderr, "DUMMY_VideoInit 2\n");
  /* We're done! */
  return 0;
}

SDL_Rect **DUMMY_ListModes(_THIS, SDL_PixelFormat *format, Uint32 flags)
{
fprintf(stderr, "DUMMY_ListModes 1\n");
  return (SDL_Rect **) -1;
}

SDL_Surface *DUMMY_SetVideoMode(_THIS, SDL_Surface *current,
				int width, int height, int bpp, Uint32 flags)
{
fprintf(stderr, "DUMMY_SetVideoMode 1\n");
  if (this->hidden->buffer) {
    SDL_free(this->hidden->buffer);
  }
fprintf(stderr, "DUMMY_SetVideoMode 2\n");
  this->hidden->buffer = SDL_malloc(width * height * (bpp / 8));
  if (!this->hidden->buffer) {
    SDL_SetError("Couldn't allocate buffer for requested mode");
    return(NULL);
  }
fprintf(stderr, "DUMMY_SetVideoMode 3\n");
  /* 	printf("Setting mode %dx%d\n", width, height); */

  SDL_memset(this->hidden->buffer, 0, width * height * (bpp / 8));
fprintf(stderr, "DUMMY_SetVideoMode 4\n");
  /* Allocate the new pixel format for the screen */
  if (!SDL_ReallocFormat(current, bpp, 0, 0, 0, 0)) {
    SDL_free(this->hidden->buffer);
    this->hidden->buffer = NULL;
    SDL_SetError("Couldn't allocate new pixel format for requested mode");
    return(NULL);
  }
fprintf(stderr, "DUMMY_SetVideoMode 5\n");
  /* Set up the new mode framebuffer */
  current->flags = flags & SDL_FULLSCREEN;
  this->hidden->w = current->w = width;
  this->hidden->h = current->h = height;
  current->pitch = current->w * (bpp / 8);
  current->pixels = this->hidden->buffer;
fprintf(stderr, "DUMMY_SetVideoMode 6\n");
  /* We're done */
  return current;
}

/* We don't actually allow hardware surfaces other than the main one */
static int DUMMY_AllocHWSurface(_THIS, SDL_Surface *surface)
{
fprintf(stderr, "DUMMY_AllocHWSurface\n");
  return -1;
}
static void DUMMY_FreeHWSurface(_THIS, SDL_Surface *surface)
{
fprintf(stderr, "DUMMY_FreeHWSurface\n");
  return;
}

/* We need to wait for vertical retrace on page flipped displays */
static int DUMMY_LockHWSurface(_THIS, SDL_Surface *surface)
{
fprintf(stderr, "DUMMY_LockHWSurface\n");
  return 0;
}

static void DUMMY_UnlockHWSurface(_THIS, SDL_Surface *surface)
{
fprintf(stderr, "DUMMY_UnlockHWSurface\n");
  return;
}

static void DUMMY_UpdateRects(_THIS, int numrects, SDL_Rect *rects)
{
fprintf(stderr, "DUMMY_UpdateRects\n");
}

int DUMMY_SetColors(_THIS, int firstcolor, int ncolors, SDL_Color *colors)
{
fprintf(stderr, "DUMMY_SetColors\n");
  /* do nothing of note. */
  return 1;
}

/* Note:  If we are terminated, this could be called in the middle of
   another SDL video routine -- notably UpdateRects.
*/
void DUMMY_VideoQuit(_THIS)
{
fprintf(stderr, "DUMMY_VideoQuit 1\n");
  if (this->screen->pixels != NULL) {
fprintf(stderr, "DUMMY_VideoQuit 2\n");
      SDL_free(this->screen->pixels);
      this->screen->pixels = NULL;
  }
fprintf(stderr, "DUMMY_VideoQuit 3\n");
}
