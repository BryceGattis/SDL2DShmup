#pragma once
#include <SDL_render.h>
#include <string>

SDL_Texture* load_bitmap(SDL_Renderer*, std::string);

void blit(SDL_Renderer*, SDL_Texture*, int, int);
