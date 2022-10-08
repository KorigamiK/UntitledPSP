#include "game/state/not_implemented.hpp"

#include "utils/colors.hpp"
#include "utils/fontController.hpp"

NotImplemented::NotImplemented(SDL_Renderer *renderer)
    : renderer(renderer),
      titleTexture(FontController::getTexture(renderer, "Not Implemented", {HEADING}, 150)),
      subTitleTexture(FontController::getTexture(renderer, "Press Return\n  to go back", {TEXT}, 115))
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
    // Draw title based on texture dimensions
    SDL_Rect rect_title = {w / 2, h / 2 - 75, 0, 0};
    SDL_QueryTexture(titleTexture, NULL, NULL, &rect_title.w, &rect_title.h);
    rect_title.w *= 3;
    rect_title.h *= 4;
    rect_title.x -= rect_title.w / 2;
    SDL_RenderCopy(renderer, titleTexture, NULL, &rect_title);

    // Draw subtitle based on texture dimensions
    SDL_Rect rect_option = {w / 2, h / 2, 0, 0};
    SDL_QueryTexture(subTitleTexture, NULL, NULL, &rect_option.w, &rect_option.h);
    rect_option.x -= rect_option.w / 2;
    SDL_RenderCopy(renderer, subTitleTexture, NULL, &rect_option);
}

NotImplemented::~NotImplemented()
{
    Logger::Debug("NotImplemented::~NotImplemented()");
    SDL_DestroyTexture(titleTexture);
    SDL_DestroyTexture(subTitleTexture);
}
