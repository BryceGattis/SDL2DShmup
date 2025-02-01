#pragma once

#include "app.h"
#include "input.h"
#include "structs.h"

void draw(Application, Entity, EntityList);
void logic(Application app, Entity &player, SDL_Texture* bullet_texture, EntityList &bullets, PressedInputs pressed_inputs);

void draw_player(Application, Entity);
void draw_bullets(Application, EntityList);
void do_player(Application app, Entity &player, SDL_Texture* bullet_texture, EntityList& bullets, PressedInputs pressed_inputs);
void do_bullets(Application, EntityList&);
