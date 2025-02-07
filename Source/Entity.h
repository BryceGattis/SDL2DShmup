#pragma once

class Entity
{
public:
    int x;
    int y;
    int dx;
    int dy;

    // Constructor for non-rendered entities.
    Entity(const int x, const int y, const int dx, const int dy): x(x), y(y), dx(dx), dy(dy) {}



    
};
