#include <iostream>
#include <filesystem>
#include "utils/fontController.hpp"

void FontController::LoadFont()
{
    if (TTF_Init() < 0)
    {
        Logger::Error("Failed to initialize SDL_ttf: %s", TTF_GetError());
        throw std::runtime_error("TTF_Init failed");
    }
    if (!std::filesystem::exists(FONT_PATH))
    {
        Logger::Error("cwd: %s", std::filesystem::current_path().c_str());
        throw std::runtime_error("File " + std::string(FONT_PATH) + " does not exist");
    }

    fontBase = TTF_OpenFont(FONT_PATH, 12);
    if (fontBase == NULL)
    {
        Logger::Error("Failed to load font! SDL_ttf Error: %s", TTF_GetError());
        throw std::runtime_error("Failed to load font!");
    }
    Logger::Info("Font loaded");
}

void FontController::UnloadFont()
{
    TTF_CloseFont(fontBase);
    fontBase = NULL;
    TTF_Quit();
}

SDL_Texture *FontController::getTexture(SDL_Renderer *renderer, std::string text, SDL_Color color, int wrapLength)
{
    SDL_Surface *textSurface = TTF_RenderUTF8_Blended_Wrapped(fontBase, text.c_str(), color, wrapLength);
    if (textSurface == NULL)
    {
        Logger::Error("Unable to render text surface! SDL_ttf Error: %s", TTF_GetError());
        throw std::runtime_error("Unable to render text surface!");
    }
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == NULL)
    {
        Logger::Error("Unable to create texture from rendered text! SDL Error: %s", SDL_GetError());
        throw std::runtime_error("Unable to create texture from rendered text!");
    }
    SDL_FreeSurface(textSurface);
    return textTexture;
}