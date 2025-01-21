#include <cstdlib>
#include <iostream>
#include <ostream>

#include "SDL.h"

#include "app.h"
#include "draw.h"
#include "init.h"
#include "input.h"

int main(int argc, char* argv[])
{
    const Application app = init_sdl();
    SDL_Texture* texture = load_bitmap(app.renderer);

    PressedInputs pressed_inputs = PressedInputs();

    int player_x = 100;
    int player_y = 100;
    
    while (true)
    {
        SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 0);
        SDL_RenderClear(app.renderer);
        
        handle_input(pressed_inputs);

        if (pressed_inputs.up)
        {
            player_y -= 4;
        }
        if (pressed_inputs.down)
        {
            player_y += 4;
        }

        blit(app.renderer, texture, player_x, player_y);

        SDL_RenderPresent(app.renderer);

        SDL_Delay(16);
    }

    return 0;
}
