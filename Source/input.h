#pragma once

#include <SDL_events.h>

struct PressedInputs
{
    bool up = false;
    bool right = false;
    bool down = false;
    bool left = false;
};

void handle_input(PressedInputs&);

void handle_key_down(SDL_KeyboardEvent*, PressedInputs&);
void handle_key_up(SDL_KeyboardEvent*, PressedInputs&);