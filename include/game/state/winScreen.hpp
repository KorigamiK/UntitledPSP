#pragma once

#include "SDL2/SDL.h"
#include "game/state/gameScreen.hpp"

class WinScreen : public GameScreen
{
private:
    SDL_Texture *title = nullptr;
    SDL_Texture *subtitle = nullptr;

public:
    WinScreen(SDL_Renderer *, const char *title = "Congratulations!", const char *subtitle = "You cleared the level.");

    void draw(int w, int h) override;
    void update(Event &event) override;

    ~WinScreen();
};