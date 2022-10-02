#pragma once

#include <memory>

#include "utils/constants.hpp"
#include "game/entity.hpp"
#include "game/map.hpp"
#include "ray_march/ray.hpp"

#define PLAYER_DRECTION_SIZE 20
#define PLAYER_SIZE 10
#define PLAYER_FIELD_OF_VIEW 60

class Map;

class Player : public Entity
{
private:
    /* All Co-Ordinates are relative to the map */

    std::shared_ptr<Map> map;

    SDL_Point position{0, 0};
    int moveStep = 5;
    float angleStep = 0.1;
    float angle = 0;
    Ray rays[PLAYER_FIELD_OF_VIEW]; // rays to be casted per degree

    void rayMarch();
    void updateRays();

public:
    void update(Event &event) override;
    void draw(SDL_Renderer *renderer) override;
    Player();
    Player(int x, int y);

    void init(std::shared_ptr<Map> map);

    ~Player();
};
