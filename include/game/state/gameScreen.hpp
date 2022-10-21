#pragma once

#include <SDL2/SDL.h>
#include "utils/events.hpp"

class GameScreen
{
protected:
    SDL_Renderer *renderer = nullptr;
    GameScreen(SDL_Renderer *renderer) : renderer(renderer){};

public:
    bool exit = false;
    virtual void draw(int w, int h) = 0;
    virtual void update(Event &event) = 0;
    virtual ~GameScreen(){};
};
