#pragma once

#include <string>
#include <SDL2/SDL.h>

struct Object
{
    std::string color;
};

struct Wall : Object
{
    std::string name;
    std::vector<SDL_Point> points;
    bool colliding = false;
};

struct Target : Object
{
    SDL_Point position;
    int width, height;
    bool collided = false;
};