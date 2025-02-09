#pragma once
#include <algorithm>
#include <ostream>

#include <SDL_render.h>

#include "Entity.h"

class RenderedEntity : public Entity
{
public:
    int width;
    int height;

    bool is_player_friendly;
    int health = 1;
    int reload = 0;

    SDL_Texture* texture;
    int texture_angle;

    RenderedEntity* next = nullptr;

    // Constructor that defaults to texture width/height.
    RenderedEntity(const int x, const int y, const int dx, const int dy, bool is_player_friendly, SDL_Texture* texture, int texture_angle) : Entity(x, y, dx, dy), is_player_friendly(is_player_friendly), texture(texture), texture_angle(texture_angle)
    {
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    }
    // Constructor that can override texture width/height.
    RenderedEntity(const int x, const int y, const int dx, const int dy, bool is_player_friendly, SDL_Texture* texture, int texture_angle, int texture_width, int texture_height) : Entity(x, y, dx, dy), is_player_friendly(is_player_friendly), texture(texture), texture_angle(texture_angle), width(texture_width), height(texture_height)
    {}
    
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
