#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../warp_types.h"
#include "../warp_SDL_packaging.h"
#include "../basic_colors.h"
#include "../texture.h"

// Use texture editor window properties
#include "../texture_editor_window.h"

void draw_texture(SDL_Renderer* renderer, Texture& texture, int x, int y) {
    for (int _y = 0; _y < texture.size.height; _y++) {
        for (int _x = 0; _x < texture.size.width; _x++) {
            SDL_RenderDrawPoint(renderer, x + _x, y + _y,
            texture.buffer[_x + _y * texture.size.width]);
        }
    }
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        SDL_Log("Failed to initialize SDL2.");
        return -1;
    }

    auto window_flags = SDL_WINDOW_SHOWN;
    auto window = SDL_CreateWindow(
        "SDL Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_X,
        WINDOW_Y,
        window_flags
    );
    auto renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_PRESENTVSYNC
    );
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    bool quit = 0;
    SDL_Event event;

    uint8_t values[4] = {0, 85, 170, 255};
    Texture test_texture = Texture({16,16,1});
    for (int i = 0; i < 256; i++) {
        test_texture.buffer[i] = {
            values[i & 0b00000011],
            values[(i & 0b00001100) >> 2],
            values[(i & 0b00110000) >> 4],
            values[(i & 0b11000000) >> 6]
        };
    }

    SDL_RenderSetLogicalSize(renderer, SCREEN_X, SCREEN_Y);
    SDL_SetRenderDrawColor(renderer, BLACK);
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
        SDL_SetRenderDrawColor(renderer, BLACK);
        SDL_RenderClear(renderer);
        for (int y = 0; y < SCREEN_Y; y+=test_texture.size.height) {
            for (int x = 0; x < SCREEN_X; x+=test_texture.size.width) {
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