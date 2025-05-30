/* -*- C++ -*-
 *
 *  ONScripter_image.cpp - Image processing in ONScripter
 *
 *  Copyright (c) 2001-2023 Ogapee. All rights reserved.
 *
 *  ogapee@aqua.dti2.ne.jp
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ONScripter.h"
#include <new>
#include "resize_image.h"

SDL_Surface* ONScripter::loadImage(char* filename, bool is_flipped, bool* has_alpha, int* location, unsigned char* alpha)
{
    if (!filename) return NULL;

    SDL_Surface* tmp = NULL;
    if (location) *location = BaseReader::ARCHIVE_TYPE_NONE;

//printf("<<<<<<<<<<< ONScripter::loadImage filename == %s\n", filename);

    if (filename[0] == '>')
        tmp = createRectangleSurface(filename, has_alpha, alpha);
    else
        tmp = createSurfaceFromFile(filename, has_alpha, location);
    if (tmp == NULL) return NULL;

    if (is_flipped) {
        SDL_PixelFormat* fmt = tmp->format;
        SDL_Surface* tmp2 = SDL_CreateRGBSurface(SDL_SWSURFACE, tmp->w, tmp->h,
                                                 fmt->BitsPerPixel, fmt->Rmask, fmt->Gmask, fmt->Bmask, fmt->Amask);
        for (int y = 0; y < tmp->h; ++y) {
            Uint32* src = (Uint32*)tmp->pixels + tmp->w * y;
            Uint32* dst = (Uint32*)tmp2->pixels + tmp2->w * (y + 1) - 1;
            for (int x = 0; x < tmp->w; x++)
                *dst-- = *src++;
        }
        SDL_FreeSurface(tmp);
        tmp = tmp2;
    }






//added, another code see below
#define FIX_TACHI_IMAGE_PNG_MASK_BUG 1
int DEBUG = 0;
#if FIX_TACHI_IMAGE_PNG_MASK_BUG
#if 0
    bool has_colorkey = false;
    Uint32 colorkey = 0;

    if ( has_alpha ){
        *has_alpha = (tmp->format->Amask != 0);
if (DEBUG) printf("<<<<<<<<<<< *has_alpha == %d\n", *has_alpha);
        if (!(*has_alpha) && (tmp->flags & SDL_SRCCOLORKEY)){
            has_colorkey = true;
            colorkey = tmp->format->colorkey;
            if (tmp->format->palette){
                //palette will be converted to RGBA, so don't do colorkey check
                has_colorkey = false;
            }
            *has_alpha = true;
        }
    }
#else
    bool has_colorkey = false;
    Uint32 colorkey = 0;
if (DEBUG) printf("<<<<<<<<<<< init *has_alpha == %d, %s\n", *has_alpha, filename);
	if (!(*has_alpha) && (tmp->flags & SDL_SRCCOLORKEY)){
	    has_colorkey = true;
	    colorkey = tmp->format->colorkey;
	    if (tmp->format->palette){
		//palette will be converted to RGBA, so don't do colorkey check
		has_colorkey = false;
	    }
	    *has_alpha = true;
	}
if (DEBUG) printf("<<<<<<<<<<< init2 *has_alpha == %d, %s, has_colorkey == %d\n", *has_alpha, filename, has_colorkey);
#endif
#endif






    SDL_Surface* ret;
    if ((tmp->w * tmp->format->BytesPerPixel == tmp->pitch) &&
        (tmp->format->BitsPerPixel == image_surface->format->BitsPerPixel) &&
        (tmp->format->Rmask == image_surface->format->Rmask) &&
        (tmp->format->Gmask == image_surface->format->Gmask) &&
        (tmp->format->Bmask == image_surface->format->Bmask) &&
        (tmp->format->Amask == image_surface->format->Amask)) {
        ret = tmp;
    }
    else {
        ret = SDL_ConvertSurface(tmp, image_surface->format, SDL_SWSURFACE);
        SDL_FreeSurface(tmp);
    }








    //*has_alpha = true; //monv de huayuan
//added, another code see upper
#if FIX_TACHI_IMAGE_PNG_MASK_BUG
    //  A PNG image may contain an alpha channel, which complicates
    // handling loaded images when the ":a" alphablend tag is used,
    // since the standard method was to assume the right half of the image
    // contains an alpha data mask for the left half.
    //  The current default behavior is to use the PNG image's alpha
    // channel if available, and only process for an old-style mask
    // when no alpha channel was provided.
    // However, this could cause problems running older NScr games
    // which have PNG images containing old-style masks but also an
    // opaque alpha channel.
    //  Therefore, we provide a hack, set with the --detect-png-nscmask
    // command-line option, to auto-detect if a PNG image is likely to
    // have an old-style mask.  We assume that an old-style mask is intended
    // if the image either has no alpha channel, or the alpha channel it has
    // is completely opaque.  (Note that this used to be the default
    // behavior for onscripter-en.)
    //  Note that using the --force-png-nscmask option will always assume
    // old-style masks, while --force-png-alpha will produce the current
    // default behavior.
#if 0
    if ((png_mask_type != PNG_MASK_USE_ALPHA) &&
#else
    if (1 &&
#endif
        has_alpha && *has_alpha) {
#if 0
        if (png_mask_type == PNG_MASK_USE_NSCRIPTER)
            *has_alpha = false;
        else if (png_mask_type == PNG_MASK_AUTODETECT) {
#else
	if (1) {
#endif
            SDL_LockSurface(ret);
            const Uint32 aval = *(Uint32*)ret->pixels & ret->format->Amask;
            if (aval != ret->format->Amask) goto breakalpha;
if (DEBUG) printf("<<<<<<<<<< alpha channel is 0xff, %X, %s\n", aval, filename);
            *has_alpha = false;
            for (int y=0; y<ret->h; ++y) {
                Uint32* pixbuf = (Uint32*)((char*)ret->pixels + y * ret->pitch);
                for (int x=ret->w; x>0; --x, ++pixbuf) {
                    // Resolving ambiguity per Tatu's patch, 20081118.
                    // I note that this technically changes the meaning of the
                    // code, since != is higher-precedence than &, but this
                    // version is obviously what I intended when I wrote this.
                    // Has this been broken all along?  :/  -- Haeleth
                    if ((*pixbuf & ret->format->Amask) != aval) {
                        *has_alpha = true;
                        goto breakalpha;
                    }
                }
            }
          breakalpha:
if (DEBUG) printf("<<<<<<<<<<<breakalpha *has_alpha == %d, %s, has_colorkey == %d\n", *has_alpha, filename, has_colorkey);
#if 1
            if (!*has_alpha && has_colorkey) {
                // has a colorkey, so run a match against rgb values
                const Uint32 aval = colorkey & ~(ret->format->Amask);
                if (aval == (*(Uint32*)ret->pixels & ~(ret->format->Amask)))
                    goto breakkey;
                *has_alpha = false;
                for (int y=0; y<ret->h; ++y) {
                    Uint32* pixbuf = (Uint32*)((char*)ret->pixels + y * ret->pitch);
                    for (int x=ret->w; x>0; --x, ++pixbuf) {
                        if ((*pixbuf & ~(ret->format->Amask)) == aval) {
                            *has_alpha = true;
                            goto breakkey;
                        }
                    }
                }
            } else {
bool isHaimao = true; //FIXME: if the image left half (why not right half ?) is not gray or black or white, I think it is not haimao
                for (int y=0; y<ret->h; ++y) {
                    Uint32* pixbuf = (Uint32*)((char*)ret->pixels + y * ret->pitch);
                    for (int x=ret->w; x>0; --x, ++pixbuf) {
//&& *pixbuf != 0xFF050200
                        if (/*strstr(filename, "TA") &&*/ x<ret->w/2 && *pixbuf != 0xFF000000 && *pixbuf != 0xFFFFFFFF) { //not black and not white
				int r = (*pixbuf >> 16) & 0xff;
				int g = (*pixbuf >>  8) & 0xff;
				int b = (*pixbuf >>  8) & 0xff;
				if (r != g || r != b) { //and not gray
                        		isHaimao = false;
if (DEBUG) printf("<<<<<<<<<<<isHaimao is false, %X, xy == %d, %d\n", *pixbuf, x, y);
					goto endCheckHaimao;
				}
			}
                    }
                }
endCheckHaimao:
if (isHaimao) { //strstr(filename, "TA")) { //filename contains 'TA' may mean tachi, it can be used to check if it is Haimao game temporarily
	//skip
} else {
		*has_alpha = true; //FIXME:added, monv de huayuan
}		
            }
#endif
          breakkey:
            SDL_UnlockSurface(ret);
        }
    } else {
    	//*has_alpha = true; //monv de huayuan
    }
#endif

//monv de huayuan, image2/TITLE.png, *has_alpha from 1 to 0 is wrong  
if (DEBUG) printf("<<<<<<<<<<<final *has_alpha == %d, %s\n", *has_alpha, filename);


    return ret;
}

SDL_Surface* ONScripter::createRectangleSurface(char* filename, bool* has_alpha, unsigned char* alpha)
{
    int c = 1, w = 0, h = 0;
    bool decimal_flag = false;
    while (filename[c] != 0x0a && filename[c] != 0x00) {
        if (!decimal_flag && filename[c] >= '0' && filename[c] <= '9')
            w = w * 10 + filename[c] - '0';
        if (filename[c] == '.') decimal_flag = true;
        if (filename[c] == ',') {
            c++;
            break;
        }
        c++;
    }

    decimal_flag = false;
    while (filename[c] != 0x0a && filename[c] != 0x00) {
        if (!decimal_flag && filename[c] >= '0' && filename[c] <= '9')
            h = h * 10 + filename[c] - '0';
        if (filename[c] == '.') decimal_flag = true;
        if (filename[c] == ',') {
            c++;
            break;
        }
        c++;
    }

    while (filename[c] == ' ' || filename[c] == '\t') c++;
    int n = 0, c2 = c;
    while (filename[c] == '#') {
        uchar3 col;
        readColor(&col, filename + c);
        n++;
        c += 7;
        while (filename[c] == ' ' || filename[c] == '\t') c++;
    }

    SDL_PixelFormat* fmt = image_surface->format;
    SDL_Surface* tmp = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h,
                                            fmt->BitsPerPixel, fmt->Rmask, fmt->Gmask, fmt->Bmask, fmt->Amask);

    c = c2;
    for (int i = 0; i < n; i++) {
        uchar3 col;
        readColor(&col, filename + c);
        c += 7;
        while (filename[c] == ' ' || filename[c] == '\t') c++;

        SDL_Rect rect;
        rect.x = w * i / n;
        rect.y = 0;
        rect.w = w * (i + 1) / n - rect.x;
        if (i == n - 1) rect.w = w - rect.x;
        rect.h = h;
        SDL_FillRect(tmp, &rect, SDL_MapRGBA(tmp->format, col[0], col[1], col[2], alpha ? *alpha : 0xff));
    }

    if (has_alpha) {
        if (fmt->Amask)
            *has_alpha = true;
        else
            *has_alpha = false;
    }

    return tmp;
}

SDL_Surface* ONScripter::createSurfaceFromFile(char* filename, bool* has_alpha, int* location)
{
    unsigned long length = script_h.cBR->getFileLength(filename);

    if (length == 0) {
        fprintf(stderr, " *** can't find file [%s] ***\n", filename);
        return NULL;
    }

    if (filelog_flag)
        script_h.findAndAddLog(script_h.log_info[ScriptHandler::FILE_LOG], filename, true);
    // printf(" ... loading %s length %ld\n", filename, length );

    mean_size_of_loaded_images += length * 6 / 5; // reserve 20% larger size
    num_loaded_images++;
    if (tmp_image_buf_length < mean_size_of_loaded_images / num_loaded_images) {
        tmp_image_buf_length = mean_size_of_loaded_images / num_loaded_images;
        if (tmp_image_buf) delete[] tmp_image_buf;
        tmp_image_buf = NULL;
    }

#define FIX_MEMORIES_OFF_2ND_SYS_BMP_BUG 1
#if FIX_MEMORIES_OFF_2ND_SYS_BMP_BUG
//if (fopen("MOV_OP03.mp4", "")
bool isMO2 = false;
if (filename && strstr(filename, "sys/") && strstr(filename, "-") && strstr(filename, ".bmp")) 
{ //"186-1.bmp"
	isMO2 = true;
	if (length < 0xB9C4) {
		length = 0xB9C4;
	}
}
#endif

    unsigned char* buffer = NULL;
    if (length > tmp_image_buf_length) {
        buffer = new (std::nothrow) unsigned char[length];
        if (buffer == NULL) {
            fprintf(stderr, "failed to load [%s] because file size [%lu] is too large.\n", filename, length);
            return NULL;
        }
    }
    else {
        if (!tmp_image_buf) tmp_image_buf = new unsigned char[tmp_image_buf_length];
        buffer = tmp_image_buf;
    }

    script_h.cBR->getFile(filename, buffer, location);
    char* ext = strrchr(filename, '.');

#if FIX_MEMORIES_OFF_2ND_SYS_BMP_BUG
if (isMO2 && length > 0x1C && tmp_image_buf_length > 0x1C) {		
	printf("<<<<<<<<<FIX_MO2_SYS_BMP_BUG %s, 0x1C == %X, %X, %X\n", filename, buffer[0x1C], buffer[0x00], buffer[0x01]);
	if (buffer[0x00] == 0x42 && buffer[0x01] == 0x4D && //magic is BM 
		buffer[0x1C] == 0x18 &&  //24bit depth color
		buffer[0x02] == 0xBE && buffer[0x03] == 0x8B) //file size 8BBE
	{
		buffer[0x1C] = 0x20; //24 -> 32 bit depth color
		for (int k = 0x8BBE; k < 0xB9C4; k++) { //if
			buffer[k] = 0xff;//0x00; //change from 0x00 black to 0xff white, NOTE current is 32bit
		}
	}
}
#endif


    SDL_RWops* src = SDL_RWFromMem(buffer, length);
    int is_png = IMG_isPNG(src);

    SDL_Surface* tmp = IMG_Load_RW(src, 0);
    if (!tmp && ext && (!strcmp(ext + 1, "JPG") || !strcmp(ext + 1, "jpg"))) {
        fprintf(stderr, " *** force-loading a JPG image [%s]\n", filename);
        tmp = IMG_LoadJPG_RW(src);
    }

    if (tmp && has_alpha) {
        if (tmp->format->Amask || is_png)
            *has_alpha = true;
        else
            *has_alpha = false;
    }

    SDL_RWclose(src);

    if (buffer != tmp_image_buf) delete[] buffer;

    if (!tmp)
        fprintf(stderr, " *** can't load file [%s] %s ***\n", filename, IMG_GetError());

    return tmp;
}

// resize 32bit surface to 32bit surface
int ONScripter::resizeSurface(SDL_Surface* src, SDL_Surface* dst)
{
    SDL_LockSurface(dst);
    SDL_LockSurface(src);
    Uint32* src_buffer = (Uint32*)src->pixels;
    Uint32* dst_buffer = (Uint32*)dst->pixels;

    /* size of tmp_buffer must be larger than 16 bytes */
    size_t len = src->w * (src->h + 1) * 4 + 4;
    if (resize_buffer_size < len) {
        delete[] resize_buffer;
        resize_buffer = new unsigned char[len];
        resize_buffer_size = len;
    }
    resizeImage((unsigned char*)dst_buffer, dst->w, dst->h, dst->w * 4,
                (unsigned char*)src_buffer, src->w, src->h, src->w * 4,
                4, resize_buffer, src->w * 4, false);

    SDL_UnlockSurface(src);
    SDL_UnlockSurface(dst);

    return 0;
}

#if defined(BPP16)
#define BLEND_PIXEL_MASK()                                            \
    {                                                                 \
        Uint32 s1 = (*src1_buffer | *src1_buffer << 16) & 0x07e0f81f; \
        Uint32 s2 = (*src2_buffer | *src2_buffer << 16) & 0x07e0f81f; \
        Uint32 d = (s1 + ((s2 - s1) * alpha >> 5)) & 0x07e0f81f;      \
        *dst_buffer = d | d >> 16;                                    \
    }
#else
#define BLEND_PIXEL_MASK()                                                    \
    {                                                                         \
        Uint32 s1 = *src1_buffer & 0xff00ff;                                  \
        Uint32 d1 = (s1 + ((((*src2_buffer & 0xff00ff) - s1) * alpha) >> 8)); \
        s1 = *src1_buffer & 0x00ff00;                                         \
        Uint32 d2 = (s1 + ((((*src2_buffer & 0x00ff00) - s1) * alpha) >> 8)); \
        *dst_buffer = (d1 & 0xff00ff) | (d2 & 0x00ff00);                      \
    }
// Originally, the above looks like this.
//    mask1 = mask2 ^ 0xff;
//    Uint32 mask_rb = (((*src1_buffer & 0xff00ff) * mask1 +
//                       (*src2_buffer & 0xff00ff) * mask2) >> 8) & 0xff00ff;
//    Uint32 mask_g  = (((*src1_buffer & 0x00ff00) * mask1 +
//                       (*src2_buffer & 0x00ff00) * mask2) >> 8) & 0x00ff00;
#endif

// alphaBlend
// dst: accumulation_surface
// src1: effect_src_surface
// src2: effect_dst_surface
void ONScripter::alphaBlend(SDL_Surface* mask_surface,
                            int trans_mode, Uint32 mask_value, SDL_Rect* clip)
{
    SDL_Rect rect = screen_rect;

    /* ---------------------------------------- */
    /* clipping */
    if (clip) {
        if (AnimationInfo::doClipping(&rect, clip)) return;
    }

    /* ---------------------------------------- */

    SDL_LockSurface(effect_src_surface);
    SDL_LockSurface(effect_dst_surface);
    if (accumulation_surface != effect_dst_surface)
        SDL_LockSurface(accumulation_surface);
    if (mask_surface) SDL_LockSurface(mask_surface);

    ONSBuf* src1_buffer = (ONSBuf*)effect_src_surface->pixels + effect_src_surface->w * rect.y + rect.x;
    ONSBuf* src2_buffer = (ONSBuf*)effect_dst_surface->pixels + effect_dst_surface->w * rect.y + rect.x;
    ONSBuf* dst_buffer = (ONSBuf*)accumulation_surface->pixels + accumulation_surface->w * rect.y + rect.x;

    SDL_PixelFormat* fmt = accumulation_surface->format;
    Uint32 lowest_mask;
    Uint8 lowest_loss;
    if (fmt->Rmask < fmt->Bmask) {
        lowest_mask = fmt->Rmask; // ABGR8888
        lowest_loss = fmt->Rloss;
    }
    else {
        lowest_mask = fmt->Bmask; // ARGB8888 or RGB565
        lowest_loss = fmt->Bloss;
    }

    Uint32 overflow_mask;
    if (trans_mode == ALPHA_BLEND_FADE_MASK)
        overflow_mask = 0xffffffff;
    else
        overflow_mask = ~lowest_mask;

    mask_value >>= lowest_loss;

    if ((trans_mode == ALPHA_BLEND_FADE_MASK ||
         trans_mode == ALPHA_BLEND_CROSSFADE_MASK) &&
        mask_surface) {
        for (int i = 0; i < rect.h; i++) {
            ONSBuf* mask_buffer = (ONSBuf*)mask_surface->pixels + mask_surface->w * ((rect.y + i) % mask_surface->h);

            for (int j = 0; j < rect.w; j++) {
                int j2 = (rect.x + j) % mask_surface->w;
                Uint32 alpha = 0;
                Uint32 mask = *(mask_buffer + j2) & lowest_mask;
                if (mask_value > mask) {
                    alpha = mask_value - mask;
                    if (alpha & overflow_mask) alpha = lowest_mask;
                }
                alpha++;
                BLEND_PIXEL_MASK();
                src1_buffer++;
                src2_buffer++;
                dst_buffer++;
            }
            src1_buffer += screen_width - rect.w;
            src2_buffer += screen_width - rect.w;
            dst_buffer += screen_width - rect.w;
        }
    }
    else { // ALPHA_BLEND_CONST
        Uint32 alpha = (mask_value & lowest_mask) + 1;

        for (int i = 0; i < rect.h; i++) {
            for (int j = 0; j < rect.w; j++) {
                BLEND_PIXEL_MASK();
                src1_buffer++;
                src2_buffer++;
                dst_buffer++;
            }
            src1_buffer += screen_width - rect.w;
            src2_buffer += screen_width - rect.w;
            dst_buffer += screen_width - rect.w;
        }
    }

    if (mask_surface) SDL_UnlockSurface(mask_surface);
    if (accumulation_surface != effect_dst_surface)
        SDL_UnlockSurface(accumulation_surface);
    SDL_UnlockSurface(effect_dst_surface);
    SDL_UnlockSurface(effect_src_surface);
}

#define BLEND_PIXEL_TEXT_BPP16()                                       \
    {                                                                  \
        Uint32 sa = (*src_buffer + 1) >> 3;                            \
        if (sa != 0) {                                                 \
            Uint32 d = (*dst_buffer | *dst_buffer << 16) & 0x07e0f81f; \
            d = (d + (((src_color - d) * sa) >> 5)) & 0x07e0f81f;      \
            *dst_buffer = d | d >> 16;                                 \
        }                                                              \
    }

#define BLEND_PIXEL_TEXT()                                                \
    {                                                                     \
        Uint32 sa = *src_buffer;                                          \
        if (sa == 255) {                                                  \
            *dst_buffer = src_color3;                                     \
        }                                                                 \
        else if (sa != 0) {                                               \
            sa++;                                                         \
            Uint32 d = *dst_buffer & 0xff00ff;                            \
            Uint32 d1 = (d + (((src_color1 - d) * sa) >> 8));             \
            d = *dst_buffer & 0x00ff00;                                   \
            Uint32 d2 = (d + (((src_color2 - d) * sa) >> 8));             \
            *dst_buffer = (d1 & 0xff00ff) | (d2 & 0x00ff00) | 0xff000000; \
        }                                                                 \
    }

// alphaBlendText
// dst: ONSBuf surface (accumulation_surface)
// src: 8bit surface (TTF_RenderGlyph_Shaded())
void ONScripter::alphaBlendText(SDL_Surface* dst_surface, SDL_Rect dst_rect,
                                SDL_Surface* src_surface, SDL_Color& color, SDL_Rect* clip, bool rotate_flag)
{
    int x2 = 0, y2 = 0;
    SDL_Rect clipped_rect;

    /* ---------------------------------------- */
    /* 1st clipping */
    if (clip) {
        if (AnimationInfo::doClipping(&dst_rect, clip, &clipped_rect)) return;

        x2 += clipped_rect.x;
        y2 += clipped_rect.y;
    }

    /* ---------------------------------------- */
    /* 2nd clipping */
    SDL_Rect clip_rect;
    clip_rect.x = clip_rect.y = 0;
    clip_rect.w = dst_surface->w;
    clip_rect.h = dst_surface->h;
    if (AnimationInfo::doClipping(&dst_rect, &clip_rect, &clipped_rect)) return;

    x2 += clipped_rect.x;
    y2 += clipped_rect.y;

    /* ---------------------------------------- */

    SDL_LockSurface(dst_surface);
    SDL_LockSurface(src_surface);

    SDL_PixelFormat* fmt = dst_surface->format;

    if (fmt->BitsPerPixel == 16) {
        Uint32 src_color = (((color.r >> fmt->Rloss) << fmt->Rshift) |
                            ((color.g >> fmt->Gloss) << fmt->Gshift) |
                            ((color.b >> fmt->Bloss) << fmt->Bshift));
        src_color = (src_color | src_color << 16) & 0x07e0f81f;

        Uint16* dst_buffer = (Uint16*)dst_surface->pixels + dst_surface->w * dst_rect.y + dst_rect.x;

        if (!rotate_flag) {
            unsigned char* src_buffer = (unsigned char*)src_surface->pixels + src_surface->pitch * y2 + x2;
            for (int i = 0; i < dst_rect.h; i++) {
                for (int j = dst_rect.w; j != 0; j--) {
                    BLEND_PIXEL_TEXT_BPP16();
                    src_buffer++;
                    dst_buffer++;
                }
                src_buffer += src_surface->pitch - dst_rect.w;
                dst_buffer += dst_surface->w - dst_rect.w;
            }
        }
        else {
            for (int i = 0; i < dst_rect.h; i++) {
                unsigned char* src_buffer = (unsigned char*)src_surface->pixels + src_surface->pitch * (src_surface->h - x2 - 1) + y2 + i;
                for (int j = dst_rect.w; j != 0; j--) {
                    BLEND_PIXEL_TEXT_BPP16();
                    src_buffer -= src_surface->pitch;
                    dst_buffer++;
                }
                dst_buffer += dst_surface->w - dst_rect.w;
            }
        }
    }
    else {
        Uint32 src_color1 = (color.r << fmt->Rshift) | (color.b << fmt->Bshift);
        Uint32 src_color2 = (color.g << fmt->Gshift);
        Uint32 src_color3 = (0xff << fmt->Ashift) | src_color1 | src_color2;

        Uint32* dst_buffer = (Uint32*)dst_surface->pixels + dst_surface->w * dst_rect.y + dst_rect.x;

        if (!rotate_flag) {
            unsigned char* src_buffer = (unsigned char*)src_surface->pixels + src_surface->pitch * y2 + x2;
            for (int i = 0; i < dst_rect.h; i++) {
                for (int j = dst_rect.w; j != 0; j--) {
                    BLEND_PIXEL_TEXT();
                    src_buffer++;
                    dst_buffer++;
                }
                src_buffer += src_surface->pitch - dst_rect.w;
                dst_buffer += dst_surface->w - dst_rect.w;
            }
        }
        else {
            for (int i = 0; i < dst_rect.h; i++) {
                unsigned char* src_buffer = (unsigned char*)src_surface->pixels + src_surface->pitch * (src_surface->h - x2 - 1) + y2 + i;
                for (int j = dst_rect.w; j != 0; j--) {
                    BLEND_PIXEL_TEXT();
                    src_buffer -= src_surface->pitch;
                    dst_buffer++;
                }
                dst_buffer += dst_surface->w - dst_rect.w;
            }
        }
    }

    SDL_UnlockSurface(src_surface);
    SDL_UnlockSurface(dst_surface);
}

void ONScripter::makeNegaSurface(SDL_Surface* surface, SDL_Rect& clip)
{
    SDL_LockSurface(surface);
    ONSBuf* buf = (ONSBuf*)surface->pixels + clip.y * surface->w + clip.x;

    ONSBuf mask = surface->format->Rmask | surface->format->Gmask | surface->format->Bmask;
    for (int i = clip.y; i < clip.y + clip.h; i++) {
        for (int j = clip.x; j < clip.x + clip.w; j++)
            *buf++ ^= mask;
        buf += surface->w - clip.w;
    }

    SDL_UnlockSurface(surface);
}

void ONScripter::makeMonochromeSurface(SDL_Surface* surface, SDL_Rect& clip)
{
    SDL_LockSurface(surface);
    ONSBuf *buf = (ONSBuf*)surface->pixels + clip.y * surface->w + clip.x, c;

    SDL_PixelFormat* fmt = surface->format;
    for (int i = clip.y; i < clip.y + clip.h; i++) {
        for (int j = clip.x; j < clip.x + clip.w; j++) {
            c = ((((*buf & fmt->Rmask) >> fmt->Rshift) << fmt->Rloss) * 77 +
                 (((*buf & fmt->Gmask) >> fmt->Gshift) << fmt->Gloss) * 151 +
                 (((*buf & fmt->Bmask) >> fmt->Bshift) << fmt->Bloss) * 28) >>
                8;
            *buf++ = ((monocro_color_lut[c][0] >> fmt->Rloss) << surface->format->Rshift |
                      (monocro_color_lut[c][1] >> fmt->Gloss) << surface->format->Gshift |
                      (monocro_color_lut[c][2] >> fmt->Bloss) << surface->format->Bshift);
        }
        buf += surface->w - clip.w;
    }

    SDL_UnlockSurface(surface);
}

#define FILL_LAYER_ALPHA_BUF()                                              \
    {                                                                       \
        for (int y = clip.y; y < clip.y + clip.h; y++) {                    \
            unsigned char* p = layer_alpha_buf + screen_width * y + clip.x; \
            for (int x = clip.w; x > 0; --x) *p++ = 0xff;                   \
        }                                                                   \
    }

void ONScripter::refreshSurface(SDL_Surface* surface, SDL_Rect* clip_src, int refresh_mode)
{
    if (refresh_mode == REFRESH_NONE_MODE) return;

    SDL_Rect clip;
    clip.x = clip.y = 0;
    clip.w = surface->w;
    clip.h = surface->h;
    if (clip_src)
        if (AnimationInfo::doClipping(&clip, clip_src)) return;

    int i, top;
    SDL_BlitSurface(bg_info.image_surface, &clip, surface, &clip);

    if (!all_sprite_hide_flag) {
        if (z_order < 10 && refresh_mode & REFRESH_SAYA_MODE)
            top = 9;
        else
            top = z_order;
        for (i = MAX_SPRITE_NUM - 1; i > top; i--) {
            if (sprite_info[i].image_surface && sprite_info[i].visible) {
                drawTaggedSurface(surface, &sprite_info[i], clip);
                if (smpeg_info == &sprite_info[i])
                    FILL_LAYER_ALPHA_BUF();
            }
        }
    }

    if (!all_sprite_hide_flag) {
        for (i = 0; i < 3; i++) {
            if (human_order[2 - i] >= 0 && tachi_info[human_order[2 - i]].image_surface)
                drawTaggedSurface(surface, &tachi_info[human_order[2 - i]], clip);
        }
    }

    if (windowback_flag) {
        if (nega_mode == 1) makeNegaSurface(surface, clip);
        if (monocro_flag) makeMonochromeSurface(surface, clip);
        if (nega_mode == 2) makeNegaSurface(surface, clip);

        if (!all_sprite2_hide_flag) {
            for (i = MAX_SPRITE2_NUM - 1; i >= 0; i--) {
                if (sprite2_info[i].image_surface && sprite2_info[i].visible) {
                    drawTaggedSurface(surface, &sprite2_info[i], clip);
                    if (smpeg_info == &sprite2_info[i])
                        FILL_LAYER_ALPHA_BUF();
                }
            }
        }

        if (refresh_mode & REFRESH_SHADOW_MODE)
            shadowTextDisplay(surface, clip);
        if (refresh_mode & REFRESH_TEXT_MODE)
            text_info.blendOnSurface(surface, 0, 0, clip, layer_alpha_buf);
    }

    if (!all_sprite_hide_flag) {
        if (refresh_mode & REFRESH_SAYA_MODE)
            top = 10;
        else
            top = 0;
        for (i = z_order; i >= top; i--) {
            if (sprite_info[i].image_surface && sprite_info[i].visible) {
                drawTaggedSurface(surface, &sprite_info[i], clip);
                if (smpeg_info == &sprite_info[i])
                    FILL_LAYER_ALPHA_BUF();
            }
        }
    }

    if (!windowback_flag) {
        if (!all_sprite2_hide_flag) {
            for (i = MAX_SPRITE2_NUM - 1; i >= 0; i--) {
                if (sprite2_info[i].image_surface && sprite2_info[i].visible) {
                    drawTaggedSurface(surface, &sprite2_info[i], clip);
                    if (smpeg_info == &sprite2_info[i])
                        FILL_LAYER_ALPHA_BUF();
                }
            }
        }

        if (nega_mode == 1) makeNegaSurface(surface, clip);
        if (monocro_flag) makeMonochromeSurface(surface, clip);
        if (nega_mode == 2) makeNegaSurface(surface, clip);
    }

    if (!(refresh_mode & REFRESH_SAYA_MODE)) {
        for (i = 0; i < MAX_PARAM_NUM; i++) {
            if (bar_info[i])
                drawTaggedSurface(surface, bar_info[i], clip);
        }
        for (i = 0; i < MAX_PARAM_NUM; i++) {
            if (prnum_info[i])
                drawTaggedSurface(surface, prnum_info[i], clip);
        }
    }

    if (!windowback_flag) {
        if (refresh_mode & REFRESH_SHADOW_MODE)
            shadowTextDisplay(surface, clip);
        if (refresh_mode & REFRESH_TEXT_MODE)
            text_info.blendOnSurface(surface, 0, 0, clip, layer_alpha_buf);
    }

    if (refresh_mode & REFRESH_CURSOR_MODE && !textgosub_label) {
        if (clickstr_state == CLICK_WAIT)
            drawTaggedSurface(surface, &cursor_info[0], clip);
        else if (clickstr_state == CLICK_NEWPAGE)
            drawTaggedSurface(surface, &cursor_info[1], clip);
    }

    if (show_dialog_flag)
        drawTaggedSurface(surface, &dialog_info, clip);

    ButtonLink* bl = root_button_link.next;
    while (bl) {
        if (bl->show_flag > 0)
            drawTaggedSurface(surface, bl->anim[bl->show_flag - 1], clip);
        bl = bl->next;
    }
}

void ONScripter::refreshSprite(int sprite_no, bool active_flag, int cell_no,
                               SDL_Rect* check_src_rect, SDL_Rect* check_dst_rect)
{
    if (sprite_info[sprite_no].image_surface &&
        (sprite_info[sprite_no].visible != active_flag ||
         (cell_no >= 0 && sprite_info[sprite_no].current_cell != cell_no) ||
         AnimationInfo::doClipping(check_src_rect, &sprite_info[sprite_no].pos) == 0 ||
         AnimationInfo::doClipping(check_dst_rect, &sprite_info[sprite_no].pos) == 0)) {
        if (cell_no >= 0)
            sprite_info[sprite_no].setCell(cell_no);

        sprite_info[sprite_no].visible = active_flag;

        dirty_rect.add(sprite_info[sprite_no].pos);
    }
}

void ONScripter::createBackground()
{
    bg_info.num_of_cells = 1;
    bg_info.trans_mode = AnimationInfo::TRANS_COPY;
    bg_info.pos.x = 0;
    bg_info.pos.y = 0;
    bg_info.allocImage(screen_width, screen_height, texture_format);

    if (!strcmp(bg_info.file_name, "white")) {
        bg_info.color[0] = bg_info.color[1] = bg_info.color[2] = 0xff;
    }
    else if (!strcmp(bg_info.file_name, "black") ||
             !strcmp(bg_info.file_name, "*bgcpy")) {
        bg_info.color[0] = bg_info.color[1] = bg_info.color[2] = 0x00;
    }
    else if (bg_info.file_name[0] == '#') {
        readColor(&bg_info.color, bg_info.file_name);
    }
    else {
        AnimationInfo anim;
        setStr(&anim.image_name, bg_info.file_name);
        parseTaggedString(&anim);
        anim.trans_mode = AnimationInfo::TRANS_COPY;
        setupAnimationInfo(&anim);

        bg_info.fill(0, 0, 0, 0xff);
        if (anim.image_surface) {
            SDL_Rect src_rect;
            src_rect.x = src_rect.y = 0;
            src_rect.w = anim.image_surface->w;
            src_rect.h = anim.image_surface->h;
            SDL_Rect dst_rect = {0, 0};
            if (screen_width >= anim.image_surface->w) {
                dst_rect.x = (screen_width - anim.image_surface->w) / 2;
            }
            else {
                src_rect.x = (anim.image_surface->w - screen_width) / 2;
                src_rect.w = screen_width;
            }

            if (screen_height >= anim.image_surface->h) {
                dst_rect.y = (screen_height - anim.image_surface->h) / 2;
            }
            else {
                src_rect.y = (anim.image_surface->h - screen_height) / 2;
                src_rect.h = screen_height;
            }
            bg_info.copySurface(anim.image_surface, &src_rect, &dst_rect);
        }
        return;
    }

    bg_info.fill(bg_info.color[0], bg_info.color[1], bg_info.color[2], 0xff);
}
