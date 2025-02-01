#pragma once
#include <map>

#include "enums.h"

struct Entity
{
    int x;
    int y;
    int dx;
    int dy;
    SDL_Texture* texture;
    int texture_angle;
    Entity* next = nullptr;

    // Constructor for rendered entities.
    Entity(const int x, const int y, const int dx, const int dy, SDL_Texture* texture, int texture_angle) :
    x(x), y(y), dx(dx), dy(dy), texture(texture), texture_angle(texture_angle) {}

    // Constructor for non-rendered entities.
    Entity(const int x, const int y, const int dx, const int dy): x(x), y(y), dx(dx), dy(dy), texture(nullptr), texture_angle(0) {}
};

struct EntityList
{
    Entity *head;
    Entity *tail;
};

struct Stage
{
    EntityList bullets = EntityList();
    EntityList fighters = EntityList();
    
    std::map<EntityType, SDL_Texture*> textures;

    Entity* enemy_spawner;
    int spawn_timer = 8;
    Stage(Entity *enemy_spawner, std::map<EntityType, SDL_Texture*> textures) : enemy_spawner(enemy_spawner), textures(textures) {}
};