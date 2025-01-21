#pragma once
#include <SDL_render.h>

SDL_Texture* load_bitmap(SDL_Renderer*);

void blit(SDL_Renderer*, SDL_Texture*, int, int);
