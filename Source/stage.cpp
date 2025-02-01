#include "stage.h"

#include "defs.h"
#include "draw.h"

void logic(Entity &player, SDL_Texture* bullet_texture, Stage &stage, PressedInputs pressed_inputs)
{
    do_player(player, bullet_texture, stage, pressed_inputs);
    do_bullets(stage);
}

void do_player(Entity &player, SDL_Texture* bullet_texture, Stage &stage, PressedInputs pressed_inputs)
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
        fire_bullet(bullet_texture, player, stage);
    }
}

void do_bullets(Stage &stage)
{
    if (!stage.bullets.head)
        return;
    Entity* bullet = stage.bullets.head;
    Entity* prev = nullptr;
    while (bullet)
    {
        bullet->x += bullet->dx;
        bullet->y += bullet->dy;
        if (bullet->x > SCREEN_WIDTH)
        {
            if (!prev)
            {
                stage.bullets.head = bullet->next;
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


void draw(Application app, Entity player, Stage stage)
{
    draw_player(app, player);
    draw_bullets(app, stage);
}

void draw_player(Application app, Entity player)
{
    blit(app.renderer, player);
}

void draw_bullets(Application app, Stage stage)
{
    if (!stage.bullets.head)
        return;
    Entity* bullet = stage.bullets.head;
    while (bullet)
    {
        blit(app.renderer, *bullet);
        bullet = bullet->next;
    }
}