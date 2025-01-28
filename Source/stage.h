#pragma once

#include "app.h"
#include "structs.h"

void draw(Application, Entity, BulletList);
void logic(Application, BulletList&);

void draw_player(Application, Entity);
void draw_bullets(Application, BulletList);
void do_bullets(Application, BulletList&);
