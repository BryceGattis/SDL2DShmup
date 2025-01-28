#pragma once
#include <SDL_render.h>
#include <string>

#include "structs.h"

SDL_Texture* load_bitmap(SDL_Renderer* renderer, std::string path);

void blit(SDL_Renderer* renderer, Entity entity);
