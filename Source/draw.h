#pragma once
#include <SDL_render.h>
#include <string>

#include "RenderedEntity.h"

SDL_Texture* load_bitmap(SDL_Renderer* renderer, std::string path);

void blit(SDL_Renderer* renderer, RenderedEntity entity);
void blit_rectangle(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* src, int x, int y);
