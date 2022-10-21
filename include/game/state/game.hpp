#pragma once

#include <SDL2/SDL.h>

#include "game/map.hpp"
#include "game/player.hpp"
#include "game/player_view.hpp"
#include "game/state/base.hpp"
#include "game/state/pauseScreen.hpp"
#include "game/state/winScreen.hpp"

class GameState : public BaseState
{
private:
    SDL_Renderer *renderer;

    static bool scoreChanged;
    SDL_Texture *scoreTexture;
    void drawScore(int width, int height);

    Player *player;
    std::unique_ptr<PlayerView> playerView;
    std::shared_ptr<Map> map;

    PauseScreen pauseScreen;
    WinScreen winScreen;

    bool paused = false;

public:
    static int score;

    GameState(SDL_Renderer *renderer);
    void handleEvent(Event &event) override;
    void draw(float dt, int width, int height) override;
    bool isDone() override;
    State getNextState() override;
    ~GameState();
};
