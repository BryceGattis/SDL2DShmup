#include "stage.h"

#include <iostream>

#include "defs.h"
#include "draw.h"
#include "math.h"

void logic(RenderedEntity &player, Stage &stage, PressedInputs pressed_inputs)
{
    spawn_enemies(stage);
    do_player(player, stage, pressed_inputs);
    do_bullets(stage);
    do_collision_checks(stage);
    do_enemy_spawner(stage);
    do_fighters(stage);
    do_enemies(player, stage);
    constrain_player(player);
}

void spawn_enemies(Stage& stage)
{
    if (stage.spawn_timer > 0)
    {
        stage.spawn_timer--;
        return;
    }
    stage.spawn_timer = 40;

    RenderedEntity* enemy = new RenderedEntity(stage.enemy_spawner->x, stage.enemy_spawner->y, -4, 0, false, stage.textures[EntityType::ENEMY_FIGHTER], 90, SHIP_WIDTH, SHIP_HEIGHT);

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


void do_player(RenderedEntity &player, Stage &stage, PressedInputs pressed_inputs)
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
    RenderedEntity* bullet = stage.bullets.head;
    RenderedEntity* prev = nullptr;
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
    RenderedEntity* bullet = stage.bullets.head;
    while (bullet)
    {
        RenderedEntity* fighter = stage.fighters.head;
        while (fighter)
        {
            if (bullet->is_player_friendly != fighter->is_player_friendly && bullet->collides_with(fighter))
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
    RenderedEntity* fighter = stage.fighters.head;
    RenderedEntity* prev = nullptr;
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

void do_enemies(RenderedEntity player, Stage& stage)
{
    if (!stage.fighters.head)
        return;
    RenderedEntity* fighter = stage.fighters.head;
    while (fighter)
    {
        if (fighter->reload == 0)
        {
            enemy_fire_bullet(player, fighter, stage);
        }
        else
        {
            fighter->reload--;
        }
        fighter = fighter->next;
    }
}

void enemy_fire_bullet(RenderedEntity player, RenderedEntity *enemy, Stage &stage)
{
    enemy->reload = 120;
    RenderedEntity* bullet = new RenderedEntity(enemy->x, enemy->y, 0, 0, false, stage.textures[EntityType::ENEMY_BULLET], -90);
    
    get_slope(enemy->x, enemy->y, player.x, player.y, &bullet->dx, &bullet->dy);
    bullet->dx *= ENEMY_BULLET_SPEED;
    bullet->dy *= ENEMY_BULLET_SPEED;
    
    if (stage.bullets.tail)
    {
        stage.bullets.tail->next = bullet;
    }

    stage.bullets.tail = bullet;

    if (!stage.bullets.head)
    {
        stage.bullets.head = bullet;
    }
}


void constrain_player(RenderedEntity& player)
{
    if (player.x < 0)
    {
        player.x = 0;
    }
    if (player.x + player.width > SCREEN_WIDTH)
    {
        player.x = SCREEN_WIDTH - player.width;
    }
    if (player.y < 0)
    {
        player.y = 0;
    }
    if (player.y + player.height > SCREEN_HEIGHT)
    {
        player.y = SCREEN_HEIGHT - player.height;
    }
}





void draw(Application app, RenderedEntity player, Stage stage)
{
    draw_player(app, player);
    draw_bullets(app, stage);
    draw_enemies(app, stage);
}

void draw_player(Application app, RenderedEntity player)
{
    blit(app.renderer, player);
}

void draw_bullets(Application app, Stage stage)
{
    if (!stage.bullets.head)
        return;
    RenderedEntity* bullet = stage.bullets.head;
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
    RenderedEntity* fighter = stage.fighters.head;
    while (fighter)
    {
        blit(app.renderer, *fighter);
        fighter = fighter->next;
    }
}
