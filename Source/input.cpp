#include "input.h"

#include "SDL.h"

void handle_input(PressedInputs &pressed_inputs)
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        exit(0);
    case SDL_KEYDOWN:
        handle_key_down(&event.key, pressed_inputs);
        break;
    case SDL_KEYUP:
        handle_key_up(&event.key, pressed_inputs);
    default:
        break;
    }


}

void handle_key_down(SDL_KeyboardEvent *event, PressedInputs &pressed_inputs)
{
    if (event->repeat == 0)
    {
        if (event->keysym.scancode == SDL_SCANCODE_UP)
        {
            pressed_inputs.up = true;
        }
        if (event->keysym.scancode == SDL_SCANCODE_DOWN)
        {
            pressed_inputs.down = true;
        }
    }
}

void handle_key_up(SDL_KeyboardEvent *event, PressedInputs &pressed_inputs)
{
    if (event->repeat == 0)
    {
        if (event->keysym.scancode == SDL_SCANCODE_UP)
        {
            pressed_inputs.up = false;
        }
        if (event->keysym.scancode == SDL_SCANCODE_DOWN)
        {
            pressed_inputs.down = false;
        }
    }
}
