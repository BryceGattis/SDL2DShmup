#pragma once

struct Entity
{
    int x;
    int y;
    int dx;
    int dy;
    SDL_Texture* texture;
    int texture_angle;
    Entity* next = nullptr;
    Entity(const int x, const int y, const int dx, const int dy, SDL_Texture* texture, int texture_angle) :
    x(x), y(y), dx(dx), dy(dy), texture(texture), texture_angle(texture_angle) {}
};

struct BulletList
{
    Entity *head;
    Entity *tail;
};