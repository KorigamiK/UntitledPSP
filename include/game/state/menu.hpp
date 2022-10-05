#pragma once

#include "game/state/base.hpp"
#include "utils/constants.hpp"

class MenuState : public BaseState
{
private:
    SDL_Renderer *renderer;

    SDL_Texture *titleTexture = nullptr;

    int numOptions = 3;

    State options[3] = {State::Game, State::NotImplemented, State::Exit};

    SDL_Texture *optionTextures[3];

    int selected = 0;

public:
    MenuState(SDL_Renderer *renderer);

    void handleEvent(Event &event) override;
    void draw(float dt, int w, int h) override;
    State getNextState() override;

    ~MenuState();
};