#include "game/state/game.hpp"

int GameState::score = 1;
bool GameState::scoreChanged = true;

GameState::GameState(SDL_Renderer *renderer)
    : renderer(renderer), pauseScreen(renderer), winScreen(renderer), scoreTexture(nullptr)
{
    // increase a target after score increases 2 times
    int levelTargets = (score + 2) / 2;
    scoreChanged = true;
    map = std::make_shared<Map>(SDL_Rect{width / 2, 0, width / 2, height}, 10, levelTargets);
    player = new Player(map->mapRect.w / 2, map->mapRect.h / 2);
    player->init(map);
    map->init(player);
    playerView = std::make_unique<PlayerView>(player, SDL_Rect{0, 0, width / 2, height});
}

void GameState::drawScore(int width, int height)
{
    if (scoreChanged)
    {
        if (scoreTexture != nullptr)
            SDL_DestroyTexture(scoreTexture);
        scoreChanged = false;
        std::string scoreText = "Score: " + std::to_string(score);
        scoreTexture = FontController::getTexture(renderer, scoreText.c_str(), {SCORE});
    }

    SDL_Rect textRect;
    SDL_QueryTexture(scoreTexture, NULL, NULL, &textRect.w, &textRect.h);
    textRect.w *= 1.1;
    textRect.h *= 1.1;
    textRect.x = width - textRect.w - 10;
    textRect.y = 10;
    SDL_RenderCopy(renderer, scoreTexture, NULL, &textRect);
}

void GameState::draw(float dt, int width, int height)
{
    map->setMapRect(std::move(SDL_Rect{2 * width / 3, 0, width / 3, height}), 10);
    playerView->setViewRect(std::move(SDL_Rect{0, 0, 2 * width / 3, height}));

    player->draw(renderer, dt);
    playerView->draw(renderer);
    map->draw(renderer);

    drawScore(width, height);

    if (player->didWin)
    {
        winScreen.draw(width, height);
        return;
    }

    if (paused)
        pauseScreen.draw(width, height);
}

void GameState::handleEvent(Event &event)
{
    if (event == Event::MENU)
        paused = !paused;
    else if (!paused)
    {
        if (player->didWin)
        {
            winScreen.update(event);
            if (winScreen.exit)
            {
                this->done = true;
                scoreChanged = true;
                score++;
            }
        }
        else
            player->update(event);
    }
    else
    {
        pauseScreen.update(event);
        if (pauseScreen.exit)
            this->done = true;
    }
}

State GameState::getNextState()
{
    if (winScreen.exit || pauseScreen.skipLevel)
        return State::Game;
    return State::Menu;
}

bool GameState::isDone()
{
    return done;
}

GameState::~GameState()
{
    Logger::Info("GameState::~GameState");
    delete player;
    scoreChanged = true;
    SDL_DestroyTexture(scoreTexture);
}