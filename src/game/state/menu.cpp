#include "game/state/menu.hpp"

#include "utils/colors.hpp"
#include "utils/fontController.hpp"
#include "game/state/game.hpp"

MenuState::MenuState(SDL_Renderer *renderer)
    : renderer(renderer)
{
    titleTexture = FontController::getTexture(renderer, "UNTITLED", SDL_Color{HEADING, 255});

    for (int i = 0; i < numOptions; i++)
        optionTextures[i] = FontController::getTexture(renderer, Constants::StateToString.at(options[i]), SDL_Color{TEXT, 255}, 500);
}

void MenuState::handleEvent(Event &event)
{
    switch (event)
    {
    case Event::UP:
        selected = (selected - 1 + numOptions) % numOptions;
        break;
    case Event::DOWN:
        selected = (selected + 1) % numOptions;
        break;
    case Event::CONFIRM:
        this->done = true;
        break;
    }
}

void MenuState::draw(float dt, int w, int h)
{
    // Draw title
    SDL_Rect rect_title = {w / 2, h / 2 - 120, 0, 0};
    SDL_QueryTexture(titleTexture, NULL, NULL, &rect_title.w, &rect_title.h);
    rect_title.w *= 4;
    rect_title.h *= 5;
    rect_title.x -= rect_title.w / 2;
    SDL_RenderCopy(renderer, titleTexture, NULL, &rect_title);

    // Draw options
    for (int i = 0; i < numOptions; i++)
    {
        SDL_Rect rect_option = {w / 2, h / 2 + i * 50 - 20, 0, 0};
        SDL_QueryTexture(optionTextures[i], NULL, NULL, &rect_option.w, &rect_option.h);
        rect_option.w *= 2;
        rect_option.h *= 2;
        rect_option.x -= rect_option.w / 2;
        SDL_RenderCopy(renderer, optionTextures[i], NULL, &rect_option);
        // draw outline around selected option
        if (i == selected)
        {
            rect_option.x -= 10;
            rect_option.y -= 10;
            rect_option.w += 20;
            rect_option.h += 20;
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &rect_option);
        }
    }
}

State MenuState::getNextState()
{
    if (options[selected] == State::Game) // reset score
        GameState::score = 1;
    return options[selected];
}

MenuState::~MenuState()
{
    Logger::Debug("MenuState::~MenuState");
    SDL_DestroyTexture(titleTexture);
    for (int i = 0; i < numOptions; i++)
        SDL_DestroyTexture(optionTextures[i]);
}