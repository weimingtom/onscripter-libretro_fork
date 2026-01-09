/*
  SDL_ttf:  A companion library to SDL for working with TrueType (tm) fonts
  Copyright (C) 2001-2012 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
  claim that you wrote the original software. If you use this software
  in a product, an acknowledgment in the product documentation would be
  appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
  misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include <string.h>
#include "SDL_ttf.h"
#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_STATIC
#define STBTT_STREAM_TYPE SDL_RWops *
#define STBTT_STREAM_READ(s,x,y)  s->read(s, x, 1, y)
#define STBTT_STREAM_SEEK(s,x)    s->seek(s, x, RW_SEEK_SET);
#include "stb_truetype.h"

#define NUM_GRAYS       256

struct _TTF_Font {
    stbtt_fontinfo info;
    float scale;
    int ascent, descent, height;

    /* We are responsible for closing the font stream */
    SDL_RWops *src;
    int freesrc;
};

const SDL_version *TTF_Linked_Version(void)
{
    static SDL_version linked_version;
    SDL_TTF_VERSION(&linked_version);
    return(&linked_version);
}

int TTF_Init(void)
{
    return 0;
}

TTF_Font* TTF_OpenFontIndexDPIRW(SDL_RWops *src, int freesrc, int ptsize, long index, unsigned int hdpi, unsigned int vdpi)
{
    TTF_Font *font;

    if (!src) {
        TTF_SetError("Passed a NULL font source");
        return NULL;
    }

    if (SDL_RWtell(src) < 0) {
        TTF_SetError("Can't seek in stream");
        if (freesrc)
            SDL_RWclose(src);
        return NULL;
    }

    font = (TTF_Font *)malloc(sizeof *font);
    if (font == NULL) {
        TTF_SetError("Out of memory");
        if (freesrc)
            SDL_RWclose( src );
        return NULL;
    }
    memset(font, 0, sizeof(*font));

    stbtt_InitFont(&font->info, src, stbtt_GetFontOffsetForIndex(src, index));
    stbtt_GetFontVMetrics(&font->info, &font->ascent, &font->descent, NULL);
    font->src = src;
    font->freesrc = freesrc;
    font->height = STBTT_iceil(ptsize) + 2;
    font->scale = stbtt_ScaleForPixelHeight(&font->info, font->height);
    font->ascent = STBTT_iceil(font->ascent * font->scale);
    font->descent = STBTT_iceil(font->descent * font->scale);

    return font;
}


TTF_Font* TTF_OpenFontDPIRW(SDL_RWops *src, int freesrc, int ptsize, unsigned int hdpi, unsigned int vdpi)
{
    return TTF_OpenFontIndexDPIRW(src, freesrc, ptsize, 0, hdpi, vdpi);
}

TTF_Font* TTF_OpenFontIndexRW(SDL_RWops *src, int freesrc, int ptsize, long index)
{
    return TTF_OpenFontIndexDPIRW(src, freesrc, ptsize, index, 0, 0);
}

TTF_Font* TTF_OpenFontRW(SDL_RWops *src, int freesrc, int ptsize)
{
    return TTF_OpenFontIndexRW(src, freesrc, ptsize, 0);
}

TTF_Font* TTF_OpenFontIndexDPI(const char *file, int ptsize, long index, unsigned int hdpi, unsigned int vdpi)
{
    SDL_RWops *rw = SDL_RWFromFile(file, "rb");
    if (rw == NULL) {
        TTF_SetError(SDL_GetError());
        return NULL;
    }
    return TTF_OpenFontIndexDPIRW(rw, 1, ptsize, index, hdpi, vdpi);
}

TTF_Font* TTF_OpenFontIndex(const char *file, int ptsize, long index)
{
    return TTF_OpenFontIndexDPI(file, ptsize, index, 0, 0);
}

TTF_Font* TTF_OpenFontDPI(const char *file, int ptsize, unsigned int hdpi, unsigned int vdpi)
{
    return TTF_OpenFontIndexDPI(file, ptsize, 0, hdpi, vdpi);
}

TTF_Font* TTF_OpenFont(const char *file, int ptsize)
{
    return TTF_OpenFontIndex(file, ptsize, 0);
}

void TTF_CloseFont(TTF_Font* font)
{
    if (font) {
        if (font->freesrc)
            SDL_RWclose(font->src);
        free(font);
    }
}

int TTF_FontHeight(const TTF_Font *font)
{
    return font->height;
}

int TTF_FontAscent(const TTF_Font *font)
{
    return font->ascent;
}

int TTF_FontDescent(const TTF_Font *font)
{
    return font->descent;
}

int TTF_FontLineSkip(const TTF_Font *font)
{
    return font->height;
}

int TTF_GlyphMetrics(TTF_Font *font, Uint16 ch,
                     int *minx, int *maxx, int *miny, int *maxy, int *advance)
{
    int x0, y0, x1, y1;
    int advance_width;
    int glyph = stbtt_FindGlyphIndex(&font->info, ch);
    if (glyph == 0) {
        TTF_SetError("Couldn't find glyph");
        return -1;
    }

    stbtt_GetGlyphBox(&font->info, glyph, &x0, &y0, &x1, &y1);
    stbtt_GetGlyphHMetrics(&font->info, glyph, &advance_width, 0);
    if (minx)
        *minx = STBTT_ifloor(x0 * font->scale);
    if (miny)
        *miny = STBTT_ifloor(y0 * font->scale);
    if (maxx)
        *maxx = STBTT_iceil(x1 * font->scale);
    if (maxy)
        *maxy = STBTT_iceil(y1 * font->scale);
    if (advance)
        *advance = STBTT_iceil(advance_width * font->scale);
    return 0;
}

void TTF_SetFontStyle(TTF_Font* font, int style)
{
}

int TTF_GetFontStyle(const TTF_Font* font)
{
    return 0;
}

void TTF_SetFontOutline(TTF_Font* font, int outline)
{
}

int TTF_GetFontOutline(const TTF_Font* font)
{
    return 0;
}

SDL_Surface* TTF_RenderGlyph_Shaded(TTF_Font* font,
                                    Uint16 ch,
                                    SDL_Color fg,
                                    SDL_Color bg)
{
    SDL_Surface *surface;
    SDL_Palette *palette;
    int rdiff, gdiff, bdiff;
    int width = 0, height = 0;

    int glyph = stbtt_FindGlyphIndex(&font->info, ch);
    if (glyph == 0) {
        TTF_SetError("Couldn't find glyph");
        return NULL;
    }

    surface = SDL_CreateRGBSurface(SDL_SWSURFACE, 0, 0, 8, 0, 0, 0, 0);
    if (surface == NULL)
        return NULL;
    surface->pixels = stbtt_GetGlyphBitmap(&font->info, 0.0, font->scale, glyph, &width, &height, 0, 0);
    surface->w = width;
    surface->h = height;
    surface->pitch = width;
    SDL_SetClipRect(surface, NULL);

    /* Fill the palette with NUM_GRAYS levels of shading from bg to fg */
    palette = surface->format->palette;
    rdiff = fg.r - bg.r;
    gdiff = fg.g - bg.g;
    bdiff = fg.b - bg.b;
    for (int index = 0; index < NUM_GRAYS; ++index) {
        palette->colors[index].r = bg.r + (index*rdiff) / (NUM_GRAYS-1);
        palette->colors[index].g = bg.g + (index*gdiff) / (NUM_GRAYS-1);
        palette->colors[index].b = bg.b + (index*bdiff) / (NUM_GRAYS-1);
    }
    return surface;
}

void TTF_Quit( void )
{
}
