#include "game/state/game.hpp"

GameState::GameState(SDL_Renderer *renderer)
    : renderer(renderer)
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
}

void GameState::handleEvent(Event &event)
{
    player->update(event);
}

GameState::~GameState()
{
    Logger::Info("GameState::~GameState");
    delete player;
}