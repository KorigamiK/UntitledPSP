#include "game/state/menu.hpp"

#include "utils/fontController.hpp"

MenuState::MenuState(SDL_Renderer *renderer)
    : renderer(renderer)
{
    titleTexture = FontController::getTexture(renderer, "assets/title.png", SDL_Color{0, 0, 0, 255});
}

void MenuState::handleEvent(Event &event)
{
    switch (event)
    {
    case Event::UP:
        selected = (selected - 1) % 2;
        break;
    case Event::DOWN:
        selected = (selected + 1) % 2;
        break;
    case Event::CONFIRM:
        Logger::Info("MenuState selected: %d", selected);
        break;
    }
}

void MenuState::draw(float dt, int w, int h)
{
    SDL_Rect titleRect = {w / 2 - 100, h / 2 - 100, 200, 200};
    SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);
}

MenuState::~MenuState()
{
    Logger::Info("MenuState::~MenuState");
    SDL_DestroyTexture(titleTexture);
}