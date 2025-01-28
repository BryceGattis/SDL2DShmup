#include <iostream>

#include "stage.h"

#include "draw.h"

void draw(Application app, Entity player, BulletList bullets)
{
    draw_player(app, player);
    draw_bullets(app, bullets);
}

void draw_player(Application app, Entity player)
{
    blit(app.renderer, player);
}

void draw_bullets(Application app, BulletList bullets)
{
    if (!bullets.head)
        return;
    Entity* bullet = bullets.head;
    while (bullet)
    {
        blit(app.renderer, *bullet);
        bullet = bullet->next;
    }
}