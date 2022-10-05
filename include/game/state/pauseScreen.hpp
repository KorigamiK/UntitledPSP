#pragma once

#include <SDL2/SDL.h>

#include "utils/fontController.hpp"
#include "utils/events.hpp"

class PauseScreen
{
private:
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *title = nullptr;
    SDL_Texture *subtitle = nullptr;

public:
    bool exit = false;

    PauseScreen(SDL_Renderer *renderer, const char *title = "Paused", const char *subtitle = "Press ESC\nto resume");

    void draw(int w, int h);
    void update(Event &event);

    ~PauseScreen();
};
