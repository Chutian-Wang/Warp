#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../warp_types.h"
#include "../warp_SDL_packaging.h"
#include "../basic_colors.h"
#include "../texture.h"

// Use game window properties
#include "../game_window.h"

void draw_texture(SDL_Renderer* renderer, Texture& texture, int x, int y) {
    for (int _y = 0; _y < texture.size.height; _y++) {
        for (int _x = 0; _x < texture.size.width; _x++) {
            UpscaledDrawPoint(renderer, x + _x, y + _y,
            texture.buffer[_x + _y * texture.size.width], PIXEL_UPSCALE);
        }
    }
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

    Texture test_texture = Texture({5,2,1});

    SDL_SetRenderDrawColor(renderer, WHITE);
    SDL_RenderClear(renderer);
    size_t frame = 0;
    time_t t = std::time(NULL);
    int fps;
    while (!quit) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
        SDL_RenderClear(renderer);
        for (int y = 0; y < SCREEN_Y; y+=2) {
            for (int x = 0; x < SCREEN_X; x+=5) {
                draw_texture(renderer, test_texture, x, y);
            }
        }
        SDL_RenderPresent(renderer);
        frame++;
        time_t now = std::time(NULL);
        if (now != t) {
            fps = frame;
            frame = 0;
            t = now;
            SDL_Log("FPS: %i\n", fps);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}