#pragma once

#include <SDL2/SDL.h>

class Entity
{
private:
    friend class Player;
    const char *name = "Entity";

public:
    virtual void update(SDL_Event &event){};
    virtual void draw(SDL_Renderer *renderer){};

    Entity();
    ~Entity();
};
