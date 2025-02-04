#pragma once
#include <algorithm>
#include <SDL_render.h>

class Entity
{
protected:
    int x;
    int y;
    int dx;
    int dy;
    
    Entity* next = nullptr;

    // Constructor for non-rendered entities.
    Entity(const int x, const int y, const int dx, const int dy): x(x), y(y), dx(dx), dy(dy) {}



    
};
