#include <cstdlib>
#include <iostream>
#include <ostream>

#include "SDL.h"

#include "app.h"
#include "defs.h"
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
    SDL_Texture* enemy_texture = load_bitmap(app.renderer, "resources/enemyBlack1.bmp");
    
    std::map<EntityType, SDL_Texture*> textures;
    textures[EntityType::PLAYER] = player_texture;
    textures[EntityType::BULLET] = bullet_texture;
    textures[EntityType::ENEMY] = enemy_texture;

    PressedInputs pressed_inputs = PressedInputs();

    Entity player = Entity(100, 100, 4, 4, player_texture, -90);
    Entity enemy_spawner = Entity(SCREEN_WIDTH - 100, 100, 0, 4);
    
    Stage stage = Stage(&enemy_spawner, textures);
    
    
    while (true)
    {
        SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 0);
        SDL_RenderClear(app.renderer);
        
        handle_input(pressed_inputs);

        logic(player, bullet_texture, stage, pressed_inputs);
        draw(app, player, stage);

        SDL_RenderPresent(app.renderer);

        SDL_Delay(16);
    }

    return 0;
}
