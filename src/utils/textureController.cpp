#include "utils/textureController.hpp"

std::map<std::string, SDL_Texture *> TextureController::textures;
SDL_Surface *TextureController::iconSurface;

SDL_Texture *TextureController::load(SDL_Renderer *renderer, const char *file)
{
    if (!std::filesystem::exists(file))
    {
        Logger::Error("cwd: %s", std::filesystem::current_path().c_str());
        throw std::runtime_error("File " + std::string(file) + " does not exist");
    }

    SDL_Texture *texture = IMG_LoadTexture(renderer, file);
    if (!texture)
    {
        Logger::Error("IMG_LoadTexture: %s", IMG_GetError());
        throw std::runtime_error("IMG_LoadTexture failed");
    }

#ifdef VERBOSE
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    Logger::Debug("Texture loaded: %s (%d x %d)", file, w, h);
#endif

    return std::move(texture);
}

void TextureController::close(SDL_Texture *texture)
{
    SDL_DestroyTexture(texture);
}

void TextureController::init(SDL_Renderer *renderer)
{
    textures.insert(std::make_pair("icon", load(renderer, "res/glitch.png")));
    iconSurface = getSurfaceFromFile("res/glitch.png");
    loadSprites(renderer);
}

SDL_Texture *TextureController::getTexture(const char *name)
{
    return textures.at(name);
}

SDL_Surface *TextureController::getSurfaceFromFile(const char *name)
{
    return IMG_Load(name);
}

void TextureController::closeAll()
{
    Logger::Info("Closing all textures");
    for (auto &texture : textures)
        close(texture.second);
}

void TextureController::loadSprites(SDL_Renderer *renderer)
{
    textures.insert({"eagle", load(renderer, "./res/sprites/eagle.png")});
    textures.insert({"colorstone", load(renderer, "./res/sprites/colorstone.png")});
}
