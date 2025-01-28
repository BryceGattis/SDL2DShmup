#include <iostream>

#include "stage.h"

#include "defs.h"
#include "draw.h"

void logic(Application app, BulletList &bullets)
{
    do_bullets(app, bullets);
}


void do_bullets(Application app, BulletList &bullets)
{
    if (!bullets.head)
        return;
    Entity* bullet = bullets.head;
    Entity* prev = nullptr;
    while (bullet)
    {
        bullet->x += bullet->dx;
        bullet->y += bullet->dy;
        if (bullet->x > SCREEN_WIDTH)
        {
            if (!prev)
            {
                bullets.head = bullet->next;
            }
            else
            {
                prev->next = bullet->next;
            }
            Entity* temp = bullet;
            bullet = bullet->next;
            delete(temp);
        }
        else
        {
            prev = bullet;
            bullet = bullet->next;
        }
    }
}


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