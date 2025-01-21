#include <cstdio>

#include "SDL.h"

#include "init.h"
#include "app.h"

Application init_sdl()
{
    Application app;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        exit(1);
    }
    app.window = SDL_CreateWindow("SDL2DShmup", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!app.window)
    {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        exit(1);
    }
    
    app.renderer = SDL_CreateRenderer(app.window, -1, 0);
    if (!app.renderer)
    {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        exit(1);
    }
    
    return app;
}

void cleanup_sdl(const Application app)
{
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
}