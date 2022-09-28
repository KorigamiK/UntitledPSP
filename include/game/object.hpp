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
    SDL_Point p1;
    SDL_Point p2;
};