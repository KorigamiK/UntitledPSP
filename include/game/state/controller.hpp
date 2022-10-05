#pragma once

#include <SDL2/SDL.h>

#include "game/state/states.hpp"
#include "game/state/base.hpp"

class StateController
{
private:
    bool &appRunning;
    SDL_Renderer *renderer;

    void clearState();
    void switchState(State state);

public:
    BaseState *currentState = nullptr;

    StateController(SDL_Renderer *renderer, bool &running);

    // * Updates any changes to the current state
    void update();
    void handleEvent(Event &event);

    ~StateController();
};