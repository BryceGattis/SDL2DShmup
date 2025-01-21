#include <cstdio>

#include "draw.h"

#include <string>

SDL_Texture* load_bitmap(SDL_Renderer* renderer, std::string path)
{
    SDL_Surface *bitmap = SDL_LoadBMP(path.c_str());
    if (!bitmap)
    {
        printf("SDL_LoadBMP Error: %s\n", SDL_GetError());
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, bitmap);
    return texture;
}

void blit(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, nullptr, nullptr, &dest.w, &dest.h);

    // Use RenderCopyEx so we can rotate the texture 90 degrees counterclockwise.
    SDL_RenderCopyEx(renderer, texture, nullptr, &dest, -90, nullptr, SDL_FLIP_NONE);
}

