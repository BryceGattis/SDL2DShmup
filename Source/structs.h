#pragma once
#include <map>

#include <SDL_render.h>

#include "Entity.h"
#include "enums.h"
#include "RenderedEntity.h"

struct EntityList
{
    RenderedEntity *head = nullptr;
    RenderedEntity *tail = nullptr;
};

struct Stage
{
    EntityList bullets = EntityList();
    EntityList fighters = EntityList();
    RenderedEntity* player;
    
    std::map<EntityType, SDL_Texture*> textures;

    Entity* enemy_spawner;
    int spawn_timer = 0;
    Stage(RenderedEntity *player, Entity *enemy_spawner, std::map<EntityType, SDL_Texture*> textures) : player(player), enemy_spawner(enemy_spawner), textures(textures) {}
};