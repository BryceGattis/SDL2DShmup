#pragma once

#include "app.h"
#include "input.h"
#include "structs.h"

void draw(Application app, Entity player, Stage stage);

void logic(Entity &player, SDL_Texture* bullet_texture, Stage &stage, PressedInputs pressed_inputs);

void draw_player(Application app, Entity player);
void draw_bullets(Application app, Stage stage);
void draw_enemies(Application app, Stage stage);

void spawn_enemies(Stage &stage);
void do_player(Entity &player, SDL_Texture* bullet_texture, Stage &stage, PressedInputs pressed_inputs);
void do_bullets(Stage &stage);
void do_enemy_spawner(Stage &stage);
void do_fighters(Stage &stage);
