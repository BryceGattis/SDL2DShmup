#include "stage.h"

#include <iostream>

#include "defs.h"
#include "draw.h"
#include "math.h"

void logic(Stage &stage, PressedInputs pressed_inputs)
{
    spawn_enemies(stage);
    do_player(stage, pressed_inputs);
    do_bullets(stage);
    do_collision_checks(stage);
    do_enemy_spawner(stage);
    do_fighters(stage);
    do_enemies(stage);
    constrain_player(stage);
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


void do_player(Stage &stage, PressedInputs pressed_inputs)
{
    if (stage.player == nullptr)
    {
        return;
    }
    if (stage.player->health <= 0)
    {
        stage.player = nullptr;
        return;
    }
    if (stage.player->reload > 0)
    {
        stage.player->reload--;
    }
    if (pressed_inputs.up)
    {
        stage.player->y -= stage.player->dy;
    }
    if (pressed_inputs.down)
    {
        stage.player->y += stage.player->dy;
    }
    if (pressed_inputs.left)
    {
        stage.player->x -= stage.player->dx;
    }
    if (pressed_inputs.right)
    {
        stage.player->x += stage.player->dx;
    }
    if (pressed_inputs.fire && stage.player->reload == 0)
    {
        fire_bullet(*stage.player, stage);
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
        // Check for enemy bullet and player collision
        if (stage.player && bullet->is_player_friendly != stage.player->is_player_friendly && bullet->collides_with(stage.player))
        {
            bullet->health = 0;
            stage.player->health = 0;
        }
        
        // Check for player bullet and enemy collision
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

void do_enemies(Stage& stage)
{
    if (!stage.fighters.head)
        return;
    RenderedEntity* fighter = stage.fighters.head;
    while (fighter)
    {
        if (stage.player && fighter->reload == 0)
        {
            enemy_fire_bullet(fighter, stage);
        }
        else
        {
            fighter->reload--;
        }
        fighter = fighter->next;
    }
}

void enemy_fire_bullet(RenderedEntity *enemy, Stage &stage)
{
    enemy->reload = 120;
    RenderedEntity* bullet = new RenderedEntity(enemy->x, enemy->y, 0, 0, false, stage.textures[EntityType::ENEMY_BULLET], -90);
    
    get_slope(enemy->x, enemy->y, stage.player->x, stage.player->y, &bullet->dx, &bullet->dy);
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


void constrain_player(Stage &stage)
{
    if (!stage.player)
    {
        return;
    }
    if (stage.player->x < 0)
    {
        stage.player->x = 0;
    }
    if (stage.player->x + stage.player->width > SCREEN_WIDTH)
    {
        stage.player->x = SCREEN_WIDTH - stage.player->width;
    }
    if (stage.player->y < 0)
    {
        stage.player->y = 0;
    }
    if (stage.player->y + stage.player->height > SCREEN_HEIGHT)
    {
        stage.player->y = SCREEN_HEIGHT - stage.player->height;
    }
}


void draw(Application app, Stage stage)
{
    draw_player(app, stage);
    draw_bullets(app, stage);
    draw_enemies(app, stage);
}

void draw_player(Application app, Stage stage)
{
    if (!stage.player)
        return;
    blit(app.renderer, *stage.player);
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
