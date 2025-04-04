#include <cstdlib>
#include <iostream>
#include <ostream>

#include "SDL.h"

#include "app.h"
#include "defs.h"
#include "draw.h"
#include "init.h"
#include "input.h"
#include "RenderedEntity.h"
#include "stage.h"
#include "structs.h"

int main(int argc, char* argv[])
{
    const Application app = init_sdl();
    
    SDL_Texture* player_texture = load_bitmap(app.renderer, "resources/spaceShips_001.bmp");
    SDL_Texture* player_bullet_texture = load_bitmap(app.renderer, "resources/spaceMissiles_037.bmp");
    SDL_Texture* enemy_texture = load_bitmap(app.renderer, "resources/enemyBlack1.bmp");
    SDL_Texture* enemy_bullet_texture = load_bitmap(app.renderer, "resources/spaceMissiles_039.bmp");
    SDL_Texture* font_hud_texture = load_bitmap(app.renderer, "resources/fonts/GrotesqueBourgeoisie.bmp");
    
    std::map<EntityType, SDL_Texture*> textures;
    textures[EntityType::PLAYER_FIGHTER] = player_texture;
    textures[EntityType::PLAYER_BULLET] = player_bullet_texture;
    textures[EntityType::ENEMY_FIGHTER] = enemy_texture;
    textures[EntityType::ENEMY_BULLET] = enemy_bullet_texture;
    textures[EntityType::FONT_HUD]  = font_hud_texture;

    PressedInputs pressed_inputs = PressedInputs();
    
    Entity enemy_spawner = Entity(SCREEN_WIDTH - 100, 100, 0, 4);
    
    Stage stage = Stage(&enemy_spawner, textures);
    
    
    while (true)
    {
        SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 0);
        SDL_RenderClear(app.renderer);
        
        handle_input(pressed_inputs);

        logic(stage, pressed_inputs);
        draw(app, stage);

        SDL_RenderPresent(app.renderer);

        SDL_Delay(16);
    }

    return 0;
}
