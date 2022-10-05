#pragma once

#include "game/state/base.hpp"

class MenuState : public BaseState
{
private:
    SDL_Renderer *renderer;

    SDL_Texture *titleTexture = nullptr;

    int selected = 0;

public:
    MenuState(SDL_Renderer *renderer);

    void handleEvent(Event &event) override;
    void draw(float dt, int w, int h) override;

    ~MenuState();
};