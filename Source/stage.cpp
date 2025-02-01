#include "stage.h"

#include "defs.h"
#include "draw.h"

void logic(Application app, Entity &player, SDL_Texture* bullet_texture, EntityList &bullets, PressedInputs pressed_inputs)
{
    do_player(app, player, bullet_texture, bullets, pressed_inputs);
    do_bullets(app, bullets);
}

void do_player(Application app, Entity &player, SDL_Texture* bullet_texture, EntityList &bullets, PressedInputs pressed_inputs)
{
    if (pressed_inputs.up)
    {
        player.y -= player.dy;
    }
    if (pressed_inputs.down)
    {
        player.y += player.dy;
    }
    if (pressed_inputs.left)
    {
        player.x -= player.dx;
    }
    if (pressed_inputs.right)
    {
        player.x += player.dx;
    }
    if (pressed_inputs.fire)
    {
        fire_bullet(bullet_texture, player, bullets);
    }
}



void do_bullets(Application app, EntityList &bullets)
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


void draw(Application app, Entity player, EntityList bullets)
{
    draw_player(app, player);
    draw_bullets(app, bullets);
}

void draw_player(Application app, Entity player)
{
    blit(app.renderer, player);
}

void draw_bullets(Application app, EntityList bullets)
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