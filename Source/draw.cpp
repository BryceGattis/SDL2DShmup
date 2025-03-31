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

void blit(SDL_Renderer* renderer, RenderedEntity entity)
{
    SDL_Rect dest;

    dest.x = entity.x;
    dest.y = entity.y;
    dest.w = entity.width;
    dest.h = entity.height;

    // Use RenderCopyEx so we can rotate the texture 90 degrees counterclockwise.
    SDL_RenderCopyEx(renderer, entity.texture, nullptr, &dest, entity.texture_angle, nullptr, SDL_FLIP_NONE);
}

void blit_rectangle(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* src, int x, int y)
{
    SDL_Rect dest;

    dest.w = src->w;
    dest.h = src->h;
    dest.x = x;
    dest.y = y;

    SDL_RenderCopy(renderer, texture, src, &dest);
}

