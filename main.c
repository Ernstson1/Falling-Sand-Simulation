#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "grid.h"
#include "sand.h"
#include "gui.h"


#define WIDTH 900
#define HEIGHT 600

#define BACKGROUND_COLOR 0x0099ff



int main()
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* pWindow = SDL_CreateWindow("Sand game", SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (!pWindow)
    {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface* pSurface = SDL_GetWindowSurface(pWindow);

    if (!pSurface)
    {
        printf("SDL_GetWindowSurface failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        return 1;
    }

    // seed the random method
    srand((unsigned)SDL_GetTicks());

    // variables
    SDL_Rect background = (SDL_Rect){0, 0, WIDTH, HEIGHT};

    grid_clear();
    

    SandGrains grains;
    // init lists of grains;
    if (!sand_grains_init(&grains, 10000))
    {
        printf("Failed to init sand grains\n");
        return 1;
    }

    bool mouse_down = false;

    int running = 1;
    while (running)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                running = 0;
                break;

            case SDL_MOUSEBUTTONDOWN:
                mouse_down = true;
                break;
            case SDL_MOUSEBUTTONUP:
                mouse_down = false;
                break;
            }
        }

        if (mouse_down == true)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            SDL_MouseButtonEvent fake = {.button = SDL_BUTTON_LEFT, .x = x, .y = y};
            spawn_sand(fake, &grains.falling, grid);
        }

        // Event loop
        SDL_FillRect(pSurface, &background, BACKGROUND_COLOR);
        stepGrain(pSurface, &grains.falling, &grains.stationary, grid);
        paintStationaryGrain(pSurface, &grains.stationary);
        SDL_UpdateWindowSurface(pWindow);
        SDL_Delay(15);
    }

    sand_grains_free(&grains);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
}