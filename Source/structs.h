#pragma once
#include <map>
#include <ostream>

#include <SDL_render.h>

#include "enums.h"

struct Entity
{
    int x;
    int y;
    int width;
    int height;
    int dx;
    int dy;
    int health = 1;
    int reload = 0;
    SDL_Texture* texture;
    int texture_angle;
    Entity* next = nullptr;

    // Constructor for rendered entities.
    Entity(const int x, const int y, const int dx, const int dy, SDL_Texture* texture, int texture_angle) :
    x(x), y(y), dx(dx), dy(dy), texture(texture), texture_angle(texture_angle)
    {
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    }

    // Constructor for non-rendered entities.
    Entity(const int x, const int y, const int dx, const int dy): x(x), y(y), width(0), height(0), dx(dx), dy(dy), texture(nullptr), texture_angle(0) {}

    bool collides_with(const Entity* other) const
    {
        if (other == nullptr)
        {
            return false;
        }
        bool overlaps_x = std::max(x, other->x) < std::min(x + width, other->x + other->width);
        bool overlaps_y = std::max(y, other->y) < std::min(y + height, other->y + other->height);
        if (overlaps_x && overlaps_y)
        {
            return true;
        }
        return false;
    }
};

struct EntityList
{
    Entity *head = nullptr;
    Entity *tail = nullptr;
};

struct Stage
{
    EntityList bullets = EntityList();
    EntityList fighters = EntityList();
    
    std::map<EntityType, SDL_Texture*> textures;

    Entity* enemy_spawner;
    int spawn_timer = 0;
    Stage(Entity *enemy_spawner, std::map<EntityType, SDL_Texture*> textures) : enemy_spawner(enemy_spawner), textures(textures) {}
};