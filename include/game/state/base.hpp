#pragma once

#include <SDL2/SDL.h>

#include "utils/events.hpp"
#include "game/state/states.hpp"

#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 272

class BaseState
{
private:
    SDL_Renderer *renderer = nullptr;

public:
    virtual ~BaseState(){};

    virtual void handleEvent(Event &event) = 0;
    virtual void draw(float dt, int windowWidth, int windowHeight) = 0;

    virtual bool isDone() { return done; };
    virtual State getNextState() { return State::Exit; };

protected:
    bool done = false;
    int width = WINDOW_WIDTH, height = WINDOW_HEIGHT;
};