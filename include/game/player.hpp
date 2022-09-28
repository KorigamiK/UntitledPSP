#pragma once

#include "game/entity.hpp"

#define PLAYER_DRECTION_SIZE 20
#define PLAYER_SIZE 10

class Player : public Entity
{
private:
    int x = 0;
    int y = 0;
    int moveStep = 5;
    float angleStep = 0.1;
    float angle = 0;

public:
    void update(SDL_Event &event) override;
    void draw(SDL_Renderer *renderer) override;
    Player();
    Player(int x, int y);
    ~Player();
};
