#include <iostream>
#include "utils/fontController.hpp"

void FontController::LoadFont()
{
    if (TTF_Init() < 0)
    {
        std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
        throw std::runtime_error("TTF_Init failed");
    }
    fontBase = TTF_OpenFont(FONT_PATH, 16);
    if (fontBase == NULL)
    {
        SDL_Log("Failed to load font! SDL_ttf Error: %s", TTF_GetError());
        throw std::runtime_error("Failed to load font!");
    }
}

void FontController::UnloadFont()
{
    TTF_CloseFont(fontBase);
    fontBase = NULL;
    TTF_Quit();
}

SDL_Texture *FontController::getTexture(SDL_Renderer *renderer, std::string text, SDL_Color color)
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(fontBase, text.c_str(), color);
    if (textSurface == NULL)
    {
        SDL_Log("Unable to render text surface! SDL_ttf Error: %s", TTF_GetError());
        throw std::runtime_error("Unable to render text surface!");
    }
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == NULL)
    {
        SDL_Log("Unable to create texture from rendered text! SDL Error: %s", SDL_GetError());
        throw std::runtime_error("Unable to create texture from rendered text!");
    }
    SDL_FreeSurface(textSurface);
    return textTexture;
}