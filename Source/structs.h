#pragma once

struct Entity
{
    int x;
    int y;
    int dx;
    int dy;
    SDL_Texture* texture;
    Entity* next = nullptr;
    Entity(const int x, const int y, const int dx, const int dy, SDL_Texture* texture) : x(x), y(y), dx(dx), dy(dy), texture(texture) {}
};

struct BulletList
{
    Entity *head;
    Entity *tail;
};