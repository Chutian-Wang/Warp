#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "warp_types.h"

#ifndef WARP_SDL_PACKAGING
#define WARP_SDL_PACKAGING

inline int SDL_SetRenderDrawColor(SDL_Renderer* renderer, color_t c) {
    return SDL_SetRenderDrawColor(renderer, c.red, c.green, c.blue, c.alpha);
}

// The color_t that will be set by this function is passed by reference.
inline int SDL_GetRenderDrawColor(SDL_Renderer* renderer, color_t& c) {
    return SDL_GetRenderDrawColor(renderer, &c.red, &c.green, &c.blue, &c.alpha);
}

inline int SDL_RenderDrawPoint(SDL_Renderer* renderer, int x, int y, color_t c) {
    SDL_SetRenderDrawColor(renderer, c);
    return SDL_RenderDrawPoint(renderer, x, y);
}

#endif