#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Vec.h"

#ifndef WARP_TYPES_H
#define WARP_TYPES_H

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
} color_t;

typedef struct {
    int screenX;
    int screenY;
    int scale;
} windowSize_t;

typedef struct {
    int width;
    int height;
    int frameCount;
} textureSize_t;

static_assert(sizeof(color_t) == sizeof(Uint32), "[compile time] Size mismatch: Warp::color_t and Uint32");

union color_u {
    color_t colorT;
    Uint32  color32;
};

#endif