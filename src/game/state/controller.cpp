#include "game/state/controller.hpp"

#include "game/state/game.hpp"
#include "game/state/menu.hpp"
#include "utils/audioController.hpp"
#include "utils/sounds.hpp"

StateController::StateController(SDL_Renderer *renderer, bool &running)
    : renderer(renderer), appRunning(running), currentState(new MenuState(renderer))
{
}

void StateController::handleEvent(Event &event)
{
    currentState->handleEvent(event);
}

void StateController::update()
{
    if (this->currentState->isDone())
        switchState(this->currentState->getNextState());
}

void StateController::clearState()
{
    delete this->currentState;
    this->currentState = nullptr;
}

void StateController::switchState(State state)
{
    clearState();
    switch (state)
    {
    case State::Game:
        this->currentState = new GameState(renderer);
        break;
    case State::Menu:
        this->currentState = new MenuState(renderer);
        break;
    case State::Exit:
        appRunning = false;
        break;
    }
}

StateController::~StateController()
{
    clearState();
}