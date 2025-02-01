#pragma once

#include "app.h"
#include "input.h"
#include "structs.h"

void draw(Application app, Entity player, Stage stage);
void logic(Entity &player, SDL_Texture* bullet_texture, Stage &stage, PressedInputs pressed_inputs);

void draw_player(Application app, Entity player);
void draw_bullets(Application app, Stage stage);
void do_player(Entity &player, SDL_Texture* bullet_texture, Stage &stage, PressedInputs pressed_inputs);
void do_bullets(Stage &stage);
