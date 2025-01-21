#pragma once

struct Entity
{
    int x;
    int y;
    int dx;
    int dy;
    Entity(const int x, const int y, const int dx, const int dy) : x(x), y(y), dx(dx), dy(dy) {}
};
