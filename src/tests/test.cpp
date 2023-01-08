#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../warp_types.h"
#include "../warp_SDL_packaging.h"
#include "../basic_colors.h"

// Use game window properties
#include "../game_window.h"

void drawTile(SDL_Renderer* renderer, int x = 0, int y = 0){
    color_t c;
    SDL_GetRenderDrawColor(renderer, c);
    SDL_Rect rect = {x , y, 128, 128};
    SDL_SetRenderDrawColor(renderer, BLACK);
    SDL_RenderDrawRect(renderer, &rect);
    for (int _y = y; _y < y + 128; _y++) {
        for (int _x = x; _x < x + 128; _x++) {
            uint8_t a = (255 * ((_x/2 + _y/2) % 2));
            SDL_SetRenderDrawColor(renderer,  {a, a, a, 255});
            SDL_RenderDrawPoint(renderer, _x, _y);
        }
    }
    SDL_SetRenderDrawColor(renderer, c);
}

void drawColorBar(SDL_Renderer* renderer, color_t c, int x, int y){
    color_t lastColor;
    SDL_GetRenderDrawColor(renderer, lastColor);
    for (int i = 0; i < 128; i++) {
        for (int height = 0; height < 8; height++) {
            c.alpha = i;
            SDL_SetRenderDrawColor(renderer, c);
            SDL_RenderDrawPoint(renderer, x+i, y+height);
        }
    }
    SDL_SetRenderDrawColor(renderer, BLACK);
    SDL_Rect rect = {x, y, 128, 8};
    SDL_RenderDrawRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, lastColor);
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        SDL_Log("Failed to initialize SDL2.");
        return -1;
    }

    auto window_flags = SDL_WINDOW_SHOWN;
    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_X, WINDOW_Y, window_flags);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    bool quit = 0;
    SDL_Event event;

    SDL_RenderSetLogicalSize(renderer, SCREEN_X, SCREEN_Y);

    SDL_SetRenderDrawColor(renderer, WHITE);
    SDL_RenderClear(renderer);
    while (!quit) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
        SDL_RenderClear(renderer);
        drawTile(renderer, 8, 8);
        drawColorBar(renderer, RED, 128 + 8*2, 8*2);
        drawColorBar(renderer, GREEN, 128 + 8*2, 8*4);
        drawColorBar(renderer, BLUE, 128 + 8*2, 8*6);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}