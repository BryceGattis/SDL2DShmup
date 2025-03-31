#pragma once

#include "app.h"
#include "input.h"
#include "structs.h"

void draw(Application app, Stage stage);

void logic(Stage &stage, PressedInputs pressed_inputs);

void draw_hud(Application app, Stage stage);
void draw_text(Application app, Stage stage, int x, int y, char* text_to_draw);
void draw_player(Application app, Stage stage);
void draw_bullets(Application app, Stage stage);
void draw_enemies(Application app, Stage stage);

void init_player(Stage &stage);
void reset_stage(Stage &stage);
void spawn_enemies(Stage &stage);
void do_player(Stage &stage, PressedInputs pressed_inputs);
void do_bullets(Stage &stage);
void do_collision_checks(Stage &stage);
void do_enemy_spawner(Stage &stage);
void do_fighters(Stage &stage);
void do_enemies(Stage &stage);
void enemy_fire_bullet(RenderedEntity *enemy, Stage &stage);
void constrain_player(Stage &stage);
