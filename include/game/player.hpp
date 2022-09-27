#pragma once

#include "game/entity.hpp"

class Player : public Entity
{
private:
    int x = 0;
    int y = 0;
    int moveStep = 5;

public:
    void update(SDL_Event &event) override;
    void draw(SDL_Renderer *renderer) override;
    Player();
    Player(int x, int y);
    ~Player();
};
