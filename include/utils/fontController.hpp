#pragma once

#include <SDL2/SDL_ttf.h>
#include "utils/logger.hpp"

#define FONT_PATH "res/font.ttf"

namespace FontController
{
    static TTF_Font *fontBase;

    void LoadFont();
    void UnloadFont();
    SDL_Texture *getTexture(SDL_Renderer *renderer, std::string text, SDL_Color color);
}
