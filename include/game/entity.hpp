#pragma once

#include <SDL2/SDL.h>
#include "utils/events.hpp"

class Entity
{
private:
    friend class Player;
    const char *name = "Entity";

public:
    virtual void update(Event &event){};
    virtual void draw(SDL_Renderer *renderer){};

    Entity();
    ~Entity();
};
