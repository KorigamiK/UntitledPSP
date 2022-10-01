#pragma once

#include <map>
#include <filesystem>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace TextureController
{

    extern std::map<const char *, SDL_Texture *> textures;
    extern SDL_Surface *iconSurface;

    SDL_Texture *load(SDL_Renderer *renderer, const char *file);
    void init(SDL_Renderer *renderer);
    SDL_Texture *getTexture(const char *name);
    SDL_Surface *getSurfaceFromFile(const char *name);
    void close(SDL_Texture *texture);
    void closeAll();
}
