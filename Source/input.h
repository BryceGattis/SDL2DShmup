#pragma once

#include <SDL_events.h>
#include <SDL_render.h>

#include "structs.h"

struct PressedInputs
{
    bool up = false;
    bool right = false;
    bool down = false;
    bool left = false;
    bool fire = false;
};

void handle_input(PressedInputs&);

void handle_key_down(SDL_KeyboardEvent*, PressedInputs&);
void handle_key_up(SDL_KeyboardEvent*, PressedInputs&);

void fire_bullet(SDL_Texture* bullet_texture, Entity player, Stage &stage);