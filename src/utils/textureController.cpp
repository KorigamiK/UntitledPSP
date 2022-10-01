#include "utils/textureController.hpp"

std::map<const char *, SDL_Texture *> TextureController::textures;
SDL_Surface *TextureController::iconSurface;

SDL_Texture *TextureController::load(SDL_Renderer *renderer, const char *file)
{
    if (!std::filesystem::exists(file))
    {
        SDL_Log("cwd: %s", std::filesystem::current_path().c_str());
        throw std::runtime_error("File " + std::string(file) + " does not exist");
    }

    SDL_Texture *texture = IMG_LoadTexture(renderer, file);
    if (!texture)
    {
        SDL_Log("IMG_LoadTexture: %s", IMG_GetError());
        throw std::runtime_error("IMG_LoadTexture failed");
    }

    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Log("w %d h %d", w, h);

    return texture;
}

void TextureController::close(SDL_Texture *texture)
{
    SDL_DestroyTexture(texture);
}

void TextureController::init(SDL_Renderer *renderer)
{
    textures["icon"] = load(renderer, "res/glitch.png");
    iconSurface = getSurfaceFromFile("res/glitch.png");
}

SDL_Texture *TextureController::getTexture(const char *name)
{
    return textures[name];
}

SDL_Surface *TextureController::getSurfaceFromFile(const char *name)
{
    return IMG_Load(name);
}

void TextureController::closeAll()
{
    SDL_Log("Closing all textures");
    if (textures["icon"] != NULL)
    {
        SDL_Log("Closing icon texture");
        close(textures["icon"]);
    }
}