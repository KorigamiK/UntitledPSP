#pragma once

#include <memory>

#include "utils/constants.hpp"
#include "game/entity.hpp"
#include "game/map.hpp"
#include "ray_march/ray.hpp"

#define PLAYER_SIZE 10
#define PLAYER_FIELD_OF_VIEW 90
#define PLAYER_VERTICAL_FIELD_OF_VIEW_DEG 130
#define RAYS_CASTED 130

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
    float verticalAngle = 0;
    Ray rays[RAYS_CASTED]; // rays to be casted per degree

    void rayMarch();
    void updateRays();

public:
    friend class PlayerView;

    void update(Event &event) override;
    void draw(SDL_Renderer *renderer) override;
    Player();
    Player(int x, int y);

    void init(std::shared_ptr<Map> map);

    ~Player();
};
