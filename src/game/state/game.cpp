#include "game/state/game.hpp"

GameState::GameState(SDL_Renderer *renderer)
    : renderer(renderer), pauseScreen(renderer)
{
    map = std::make_shared<Map>(SDL_Rect{width / 2, 0, width / 2, height});
    player = new Player(map->mapRect.w / 2, map->mapRect.h / 2);
    player->init(map);
    map->init(player);
    playerView = std::make_unique<PlayerView>(player, SDL_Rect{0, 0, width / 2, height});
}

void GameState::draw(float dt, int width, int height)
{
    map->setMapRect(std::move(SDL_Rect{width / 2, 0, width / 2, height}), 10);
    playerView->setViewRect(std::move(SDL_Rect{0, 0, width / 2, height}));

    player->draw(renderer, dt);
    map->draw(renderer);
    playerView->draw(renderer);

    if (paused)
        pauseScreen.draw(width, height);
}

void GameState::handleEvent(Event &event)
{
    if (event == Event::MENU)
        paused = !paused;
    else if (!paused)
        player->update(event);
    else
    {
        pauseScreen.update(event);
        if (pauseScreen.exit)
            this->done = true;
    }
}

State GameState::getNextState()
{
    return State::Menu;
}

bool GameState::isDone()
{
    if (player->won())
        return true;
    return done;
}

GameState::~GameState()
{
    Logger::Info("GameState::~GameState");
    delete player;
}