#include <cstdlib>
#include <iostream>
#include <ostream>

#include "SDL.h"

#include "app.h"
#include "draw.h"
#include "init.h"
#include "input.h"
#include "structs.h"

int main(int argc, char* argv[])
{
    const Application app = init_sdl();
    SDL_Texture* player_texture = load_bitmap(app.renderer, "resources/spaceShips_001.bmp");

    PressedInputs pressed_inputs = PressedInputs();

    Entity player = Entity(100, 100, 4, 4);
    
    while (true)
    {
        SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 0);
        SDL_RenderClear(app.renderer);
        
        handle_input(pressed_inputs);

        if (pressed_inputs.up)
        {
            player.y -= player.dy;
        }
        if (pressed_inputs.down)
        {
            player.y += player.dy;
        }
        if (pressed_inputs.left)
        {
            player.x -= player.dx;
        }
        if (pressed_inputs.right)
        {
            player.x += player.dx;
        }

        blit(app.renderer, player_texture, player.x, player.y);

        SDL_RenderPresent(app.renderer);

        SDL_Delay(16);
    }

    return 0;
}
