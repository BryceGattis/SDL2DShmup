#include "input.h"

#include <iostream>

#include "defs.h"
#include "SDL.h"
#include "structs.h"

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
        break;
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
        if (event->keysym.scancode == SDL_SCANCODE_LEFT)
        {
            pressed_inputs.left = true;
        }
        if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
        {
            pressed_inputs.right = true;
        }
        if (event->keysym.scancode == SDL_SCANCODE_SPACE)
        {
            pressed_inputs.fire = true;
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
        if (event->keysym.scancode == SDL_SCANCODE_LEFT)
        {
            pressed_inputs.left = false;
        }
        if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
        {
            pressed_inputs.right = false;
        }
        if (event->keysym.scancode == SDL_SCANCODE_SPACE)
        {
            pressed_inputs.fire = false;
        }
    }
}

void fire_bullet(Entity &player, Stage &stage)
{
    player.reload = 8;
    
    Entity* bullet = new Entity(player.x, player.y, PLAYER_BULLET_SPEED, 0, stage.textures[EntityType::PLAYER_BULLET], 90);
    
    if (stage.bullets.tail)
    {
        stage.bullets.tail->next = bullet;
    }

    stage.bullets.tail = bullet;

    if (!stage.bullets.head)
    {
        stage.bullets.head = bullet;
    }
}
