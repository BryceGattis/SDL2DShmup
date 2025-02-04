#pragma once

#include "app.h"
#include "input.h"
#include "structs.h"

void draw(Application app, Entity player, Stage stage);

void logic(Entity &player, Stage &stage, PressedInputs pressed_inputs);

void draw_player(Application app, Entity player);
void draw_bullets(Application app, Stage stage);
void draw_enemies(Application app, Stage stage);

void spawn_enemies(Stage &stage);
void do_player(Entity &player, Stage &stage, PressedInputs pressed_inputs);
void do_bullets(Stage &stage);
void do_collision_checks(Stage &stage);
void do_enemy_spawner(Stage &stage);
void do_fighters(Stage &stage);
void do_enemies(Entity player, Stage &stage);
void enemy_fire_bullet(Entity player, Entity *enemy, Stage &stage);
void constrain_player(Entity &player);
