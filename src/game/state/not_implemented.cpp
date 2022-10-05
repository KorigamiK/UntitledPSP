#include "game/state/not_implemented.hpp"

#include "utils/fontController.hpp"

NotImplemented::NotImplemented(SDL_Renderer *renderer)
    : renderer(renderer),
      titleTexture(FontController::getTexture(renderer, "Not Implemented", {255, 255, 255})),
      subTitleTexture(FontController::getTexture(renderer, "Press Return to go back", {255, 255, 255}))
{
}

void NotImplemented::handleEvent(Event &event)
{
    switch (event)
    {
    case Event::CONFIRM:
        this->done = true;
        break;
    }
}

void NotImplemented::draw(float dt, int w, int h)
{
    SDL_Rect titleRect = {w / 2 - 130, h / 2 - 100, 300, 100};
    SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);

    SDL_Rect subTitleRect = {w / 2 - 30, h / 2, 100, 50};
    SDL_RenderCopy(renderer, subTitleTexture, nullptr, &subTitleRect);
}

NotImplemented::~NotImplemented()
{
    Logger::Debug("NotImplemented::~NotImplemented()");
    SDL_DestroyTexture(titleTexture);
    SDL_DestroyTexture(subTitleTexture);
}
