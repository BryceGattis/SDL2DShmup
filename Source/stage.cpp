#include "stage.h"

#include "defs.h"
#include "draw.h"

void logic(Entity &player, Stage &stage, PressedInputs pressed_inputs)
{
    spawn_enemies(stage);
    do_player(player, stage, pressed_inputs);
    do_bullets(stage);
    do_collision_checks(stage);
    do_enemy_spawner(stage);
    do_fighters(stage);
}

void spawn_enemies(Stage& stage)
{
    if (stage.spawn_timer > 0)
    {
        stage.spawn_timer--;
        return;
    }
    stage.spawn_timer = 40;

    Entity* enemy = new Entity(stage.enemy_spawner->x, stage.enemy_spawner->y, -4, 0, stage.textures[EntityType::ENEMY], 90);

    if (stage.fighters.tail)
    {
        stage.fighters.tail->next = enemy;
    }

    stage.fighters.tail = enemy;

    if (!stage.fighters.head)
    {
        stage.fighters.head = enemy;
    }
}


void do_player(Entity &player, Stage &stage, PressedInputs pressed_inputs)
{
    if (player.reload > 0)
    {
        player.reload--;
    }
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
    if (pressed_inputs.fire && player.reload == 0)
    {
        fire_bullet(player, stage);
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
        if (bullet->x > SCREEN_WIDTH || bullet->health == 0)
        {
            if (!bullet->next)
            {
                stage.bullets.tail = prev;
            }
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

void do_collision_checks(Stage& stage)
{
    if (!stage.bullets.head)
        return;
    Entity* bullet = stage.bullets.head;
    while (bullet)
    {
        Entity* fighter = stage.fighters.head;
        while (fighter)
        {
            if (bullet->collides_with(fighter))
            {
                bullet->health = 0;
                fighter->health = 0;
            }
            fighter = fighter->next;
        }
        bullet = bullet->next;
    }
}


void do_enemy_spawner(Stage& stage)
{
    stage.enemy_spawner->y += stage.enemy_spawner->dy;
    if (stage.enemy_spawner->y > SCREEN_HEIGHT || stage.enemy_spawner->y < 0)
    {
        stage.enemy_spawner->dy *= -1;
    }
}

void do_fighters(Stage& stage)
{
    if (!stage.fighters.head)
        return;
    Entity* fighter = stage.fighters.head;
    Entity* prev = nullptr;
    while (fighter)
    {
        fighter->x += fighter->dx;
        fighter->y += fighter->dy;
        if (fighter->x > SCREEN_WIDTH || fighter->x < 0 || fighter->health == 0)
        {
            if (!fighter->next)
            {
                stage.fighters.tail = prev;
            }
            if (!prev)
            {
                stage.fighters.head = fighter->next;
            }
            else
            {
                prev->next = fighter->next;
            }
            Entity* temp = fighter;
            fighter = fighter->next;
            delete(temp);
        }
        else
        {
            prev = fighter;
            fighter = fighter->next;
        }
    }
}




void draw(Application app, Entity player, Stage stage)
{
    draw_player(app, player);
    draw_bullets(app, stage);
    draw_enemies(app, stage);
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

void draw_enemies(Application app, Stage stage)
{
    if (!stage.fighters.head)
        return;
    Entity* fighter = stage.fighters.head;
    while (fighter)
    {
        blit(app.renderer, *fighter);
        fighter = fighter->next;
    }
}
