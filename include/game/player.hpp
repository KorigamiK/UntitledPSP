#pragma once

#include <memory>

#include "game/entity.hpp"
#include "game/map.hpp"
#include "ray_march/ray.hpp"

#define PLAYER_DRECTION_SIZE 20
#define PLAYER_SIZE 10

class Map;

class Player : public Entity
{
private:
    /* All Co-Ordinates are relative to the map */

    std::shared_ptr<Map> map;

    Ray ray;
    SDL_Point position{0, 0};
    int moveStep = 5;
    float angleStep = 0.1;
    float angle = 0;

    void rayMarch();

public:
    void update(Event &event) override;
    void draw(SDL_Renderer *renderer) override;
    Player();
    Player(int x, int y);

    void init(std::shared_ptr<Map> map);

    ~Player();
};
