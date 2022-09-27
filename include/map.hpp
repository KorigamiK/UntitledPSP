#pragma once

#include <string>
#include <SDL2/SDL.h>

struct Wall
{
    std::string name;
    std::string color;
    SDL_Point p1;
    SDL_Point p2;
};