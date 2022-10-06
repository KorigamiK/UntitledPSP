#include "game/state/pauseScreen.hpp"

PauseScreen::PauseScreen(SDL_Renderer *renderer, const char *title, const char *subtitle)
    : renderer(renderer),
      title(FontController::getTexture(renderer, title, {255, 255, 255, 255})),
      subtitle(FontController::getTexture(renderer, subtitle, {255, 255, 255, 255}, 84))
{
}

PauseScreen::~PauseScreen()
{
    SDL_DestroyTexture(title);
    SDL_DestroyTexture(subtitle);
}

void PauseScreen::draw(int w, int h)
{
    // Draw small background rect
    SDL_Rect rect = {w / 2 - 150, h / 2 - 50, 300, 100};
    SDL_SetRenderDrawColor(renderer, 0, 39, 56, 20);
    SDL_RenderFillRect(renderer, &rect);

    // Draw title
    SDL_Rect rect_title = {w / 2, h / 2 - 40, 0, 0};
    SDL_QueryTexture(title, NULL, NULL, &rect_title.w, &rect_title.h);
    rect_title.w *= 2;
    rect_title.h *= 2;
    rect_title.x -= rect_title.w / 2;
    SDL_RenderCopy(renderer, title, NULL, &rect_title);

    // Draw subtitle
    SDL_Rect rect_subtitle = {w / 2, h / 2, 0, 0};
    SDL_QueryTexture(subtitle, NULL, NULL, &rect_subtitle.w, &rect_subtitle.h);
    rect_subtitle.x -= rect_subtitle.w / 2;
    SDL_RenderCopy(renderer, subtitle, NULL, &rect_subtitle);
}

void PauseScreen::update(Event &event)
{
    if (event == Event::CONFIRM)
        exit = true;
}