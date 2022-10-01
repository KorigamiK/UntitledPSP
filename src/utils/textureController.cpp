#include "utils/textureController.hpp"

SDL_Texture *TextureController::load(SDL_Renderer *renderer, const char *file)
{
    if (!std::filesystem::exists(file))
    {
        SDL_Log("cwd: %s", std::filesystem::current_path().c_str());
        throw std::runtime_error("File " + std::string(file) + " does not exist");
    }

    SDL_Surface *img = getSurfaceFromFile(file);
    if (img == nullptr || img == NULL)
    {
        SDL_Log("Failed to load texture: %s", IMG_GetError());
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, img);
    SDL_FreeSurface(img);

    if (texture == nullptr || texture == NULL)
    {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
        return nullptr;
    }

    return std::move(texture);
}

void TextureController::close(SDL_Texture *texture)
{
    SDL_DestroyTexture(texture);
}

void TextureController::init(SDL_Renderer *renderer)
{
    textures["icon"] = load(renderer, "./res/glitch.png");
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