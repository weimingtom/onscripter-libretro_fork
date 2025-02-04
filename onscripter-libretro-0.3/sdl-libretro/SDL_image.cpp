#define WUFFS_IMPLEMENTATION
#define WUFFS_CONFIG__STATIC_FUNCTIONS
#include "wuffs.c"
#include "SDL_image.h"


class DecodeImageCallbacks: public wuffs_aux::DecodeImageCallbacks {
public:
  DecodeImageCallbacks(): surface(NULL), transparency(false) {}
  ~DecodeImageCallbacks() {
    if (surface) {
      SDL_FreeSurface(surface);
      surface = NULL;
    }
  }

  SDL_Surface *TakeSurface() {
    SDL_Surface *ret = surface;
    surface = NULL;
    return ret;
  }
private:
  SDL_Surface *surface;
  bool transparency;

  wuffs_base__pixel_format SelectPixfmt(const wuffs_base__image_config &ic) override {
    transparency = ic.pixcfg.pixel_format().transparency();
    return wuffs_base__make_pixel_format(WUFFS_BASE__PIXEL_FORMAT__BGRA_NONPREMUL);
  }

  AllocPixbufResult AllocPixbuf(const wuffs_base__image_config &ic,
                                bool allow_uninitialized_memory) override {
    if (surface) {
      SDL_FreeSurface(surface);
      surface = NULL;
    }
    int width = ic.pixcfg.width();
    int height = ic.pixcfg.height();
    Uint32 Rmask = 0, Gmask = 0, Bmask = 0, Amask = 0;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Rmask = 0x0000ff00;
    Gmask = 0x00ff0000;
    Bmask = 0xff000000;
    Amask = 0x000000ff;
#else
    Rmask = 0x00ff0000;
    Gmask = 0x0000ff00;
    Bmask = 0x000000ff;
    Amask = 0xff000000;
#endif
    if (!transparency)
      Amask = 0x00000000;

    surface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32,
                                   Rmask, Gmask, Bmask, Amask);
    if (!surface)
      return AllocPixbufResult("Callbacks: SDL_CreateRGBSurface failed");

    wuffs_base__pixel_buffer pixbuf;
    wuffs_base__status status =
      pixbuf.set_interleaved(&ic.pixcfg,
                             wuffs_base__make_table_u8(static_cast<uint8_t *>(surface->pixels),
                                                       surface->w * 4, surface->h, surface->pitch),
                             wuffs_base__empty_slice_u8());
    if (!status.is_ok()) {
      SDL_FreeSurface(surface);
      surface = NULL;
      return AllocPixbufResult(status.message());
    }
    return AllocPixbufResult(wuffs_aux::MemOwner(NULL, &free), pixbuf);
  }
};

class DecodeImageInput: public wuffs_aux::sync_io::Input {
public:
  DecodeImageInput(SDL_RWops *src): src(src) {}

private:
  SDL_RWops *src;

  std::string CopyIn(wuffs_aux::IOBuffer *dst) override {
    if (!src) {
      return "Input: NULL SDL_RWops";
    } else if (!dst) {
      return "Input: NULL IOBuffer";
    } else if (dst->meta.closed) {
      return "Input: end of file";
    }
    dst->compact();
    if (dst->writer_length() == 0) {
      return "Input: full IOBuffer";
    }
    size_t n = SDL_RWread(src, dst->writer_pointer(), 1, dst->writer_length());
    dst->meta.wi += n;
    return "";
  }
};



static SDL_Surface *IMG_LoadANY_RW(SDL_RWops *src)
{
  DecodeImageInput input(src);
  DecodeImageCallbacks callbacks;
  wuffs_aux::DecodeImageResult res = wuffs_aux::DecodeImage(callbacks, input);
  if (!res.error_message.empty()) {
    IMG_SetError("wuffs_aux::DecodeImage: %s", res.error_message.c_str());
    return NULL;
  }
  return callbacks.TakeSurface();
}

int IMG_InitPNG()
{
  return 0;
}

void IMG_QuitPNG()
{
}

int IMG_isPNG(SDL_RWops *src)
{
  int start;
  int is_PNG;
  Uint8 magic[4];

  if (!src)
    return 0;
  start = SDL_RWtell(src);
  is_PNG = 0;
  if (SDL_RWread(src, magic, 1, sizeof(magic)) == sizeof(magic)) {
    if (magic[0] == 0x89 &&
        magic[1] == 'P' &&
        magic[2] == 'N' &&
        magic[3] == 'G') {
      is_PNG = 1;
    }
  }
  SDL_RWseek(src, start, RW_SEEK_SET);
  return is_PNG;
}

SDL_Surface *IMG_LoadPNG_RW(SDL_RWops *src)
{
  return IMG_LoadANY_RW(src);
}

int IMG_InitJPG()
{
  return 0;
}

void IMG_QuitJPG()
{
}

int IMG_isJPG(SDL_RWops *src)
{
  return 1;
}

SDL_Surface *IMG_LoadJPG_RW(SDL_RWops *src)
{
  return IMG_LoadANY_RW(src);
}

SDL_Surface *IMG_Load_RW(SDL_RWops *src, int freesrc)
{
  SDL_Surface *surface = IMG_LoadANY_RW(src);
  if (freesrc)
    SDL_RWclose(src);
  return surface;
}
