#include "stage.h"

#include <iostream>

#include "defs.h"
#include "draw.h"
#include "math.h"

void logic(Stage &stage, PressedInputs pressed_inputs)
{
    if (!stage.player && --stage.stage_reset_timer <= 0)
    {
        reset_stage(stage);
    }
    spawn_enemies(stage);
    do_player(stage, pressed_inputs);
    do_bullets(stage);
    do_collision_checks(stage);
    do_enemy_spawner(stage);
    do_fighters(stage);
    do_enemies(stage);
    constrain_player(stage);
}

void init_player(Stage& stage)
{
    RenderedEntity* player = new RenderedEntity(100, 100, 4, 4, true, stage.textures[EntityType::PLAYER_FIGHTER], -90, SHIP_WIDTH, SHIP_HEIGHT);
    stage.player = player;
}

void reset_stage(Stage& stage)
{
    RenderedEntity* bullet = stage.bullets.head;
    while (bullet)
    {
        Entity* temp = bullet;
        bullet = bullet->next;
        delete(temp);
    }
    stage.bullets.head = nullptr;
    stage.bullets.tail = nullptr;
    
    RenderedEntity* fighter = stage.fighters.head;
    while (fighter)
    {
        Entity* temp = fighter;
        fighter = fighter->next;
        delete(temp);
    }
    stage.fighters.head = nullptr;
    stage.fighters.tail = nullptr;
    
    init_player(stage);
    
    stage.stage_reset_timer = 120;
    stage.score = 0;
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
        RenderedEntity* temp = stage.player;
        stage.player = nullptr;
        delete(temp);
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
                stage.score++;
            }
            fighter = fighter->next;
        }
        bullet = bullet->next;
    }
}


void do_enemy_spawner(Stage& stage)
{
    stage.enemy_spawner->y += stage.enemy_spawner->dy;
    // TODO: Use spawn class height to ensure they are never spawned offscreen at all.
    if (stage.enemy_spawner->y + 30 > SCREEN_HEIGHT || stage.enemy_spawner->y < 0)
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
    draw_hud(app, stage);
}

void draw_hud(Application app, Stage stage)
{
    char buff[100];
    int chars_written = snprintf(buff, sizeof(buff), "Score: %d", stage.score);
    if (chars_written > 0)
    {
        draw_text(app, stage, 0, 0, buff);
    }
}

void draw_text(Application app, Stage stage, int x, int y, char* text_to_draw)
{
    int ascii_to_decimal_offset;
    SDL_Rect current_rect;

    for (int i = 0; i < strlen(text_to_draw); i++)
    {
        current_rect.w = GLYPH_SIZE;
        current_rect.h = GLYPH_SIZE;
        ascii_to_decimal_offset = text_to_draw[i] - ' ';
        // Font was converted from ttf to bmp to simplify library usage using https://stmn.itch.io/font2bitmap
        // Default settings of this tool put 19 items per row, so we need to calculate where our glyphs are on the grid.
        current_rect.x = (ascii_to_decimal_offset % 19) * GLYPH_SIZE;
        current_rect.y = ascii_to_decimal_offset / 19 * GLYPH_SIZE;
        blit_rectangle(app.renderer, stage.textures[FONT_HUD], &current_rect, x, y);
        x += GLYPH_SIZE;
    }
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
