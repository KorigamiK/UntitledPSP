#pragma once

#include <SDL2/SDL.h>

#include "game/map.hpp"
#include "game/player.hpp"
#include "game/player_view.hpp"
#include "game/state/base.hpp"
#include "game/state/pauseScreen.hpp"

class GameState : public BaseState
{
private:
    SDL_Renderer *renderer;

    Player *player;
    std::unique_ptr<PlayerView> playerView;
    std::shared_ptr<Map> map;

    PauseScreen pauseScreen;
    bool paused = false;

public:
    GameState(SDL_Renderer *renderer);
    void handleEvent(Event &event) override;
    void draw(float dt, int width, int height) override;
    State getNextState() override;
    ~GameState();
};
