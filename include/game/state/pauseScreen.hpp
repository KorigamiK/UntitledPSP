#pragma once

#include <SDL2/SDL.h>

#include "game/state/gameScreen.hpp"
#include "utils/fontController.hpp"
#include "utils/events.hpp"

class PauseScreen : public GameScreen
{
private:
    SDL_Texture *title = nullptr;
    SDL_Texture *subtitle = nullptr;

public:
    PauseScreen(SDL_Renderer *renderer, const char *title = "Paused", const char *subtitle = "Press ESC\nto resume");

    void draw(int w, int h) override;
    void update(Event &event) override;

    ~PauseScreen();
};
