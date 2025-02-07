#pragma once
#include <algorithm>

#include <SDL_render.h>

#include "Entity.h"

class RenderedEntity : public Entity
{
public:
    int width;
    int height;

    int health = 1;
    int reload = 0;

    SDL_Texture* texture;
    int texture_angle;

    RenderedEntity* next = nullptr;

    RenderedEntity(const int x, const int y, const int dx, const int dy, SDL_Texture* texture, int texture_angle) : Entity(x, y, dx, dy), texture(texture), texture_angle(texture_angle)
    {
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    }
    
    bool collides_with(const RenderedEntity* other) const
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
