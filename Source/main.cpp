#include <cstdlib>
#include <iostream>
#include <ostream>

#include "SDL.h"

#include "app.h"
#include "draw.h"
#include "init.h"
#include "input.h"
#include "stage.h"
#include "structs.h"

int main(int argc, char* argv[])
{
    const Application app = init_sdl();
    SDL_Texture* player_texture = load_bitmap(app.renderer, "resources/spaceShips_001.bmp");
    SDL_Texture* bullet_texture = load_bitmap(app.renderer, "resources/spaceMissiles_037.bmp");

    PressedInputs pressed_inputs = PressedInputs();
    EntityList bullets = EntityList();

    Entity player = Entity(100, 100, 4, 4, player_texture, -90);
    
    while (true)
    {
        SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 0);
        SDL_RenderClear(app.renderer);
        
        handle_input(pressed_inputs);

        logic(app, player, bullet_texture, bullets, pressed_inputs);
        draw(app, player, bullets);

        SDL_RenderPresent(app.renderer);

        SDL_Delay(16);
    }

    return 0;
}
