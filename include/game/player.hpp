#pragma once

#include <memory>
#include <cmath>

class Map;

#include "utils/functions.hpp"
#include "utils/constants.hpp"
#include "game/entity.hpp"
#include "game/map.hpp"
#include "ray_march/ray.hpp"

#define PLAYER_SIZE 5
#define PLAYER_FIELD_OF_VIEW 90
#define PLAYER_VERTICAL_FIELD_OF_VIEW_DEG 130
#define RAYS_CASTED 96

class Player : public Entity
{
private:
    /* All Co-Ordinates are relative to the map */

    std::shared_ptr<Map> map;

    Functions::PointF position{0, 0};

    int targetsHit = 0;
    float xGoal = 0, yGoal = 0;

    int moveStep = 1;
    bool movingLeft = false, movingRight = false, movingUp = false, movingDown = false;
    bool rotatingLeft = false, rotatingRight = false;

    float angleStep = 0.02;
    float angle = -M_PI_2;
    float verticalAngle = 0;
    Ray rays[RAYS_CASTED];

    void rayMarch();
    bool checkCollision(Functions::PointF position);
    void updateRays();
    void checkWin();
    void move(float dt);

public:
    friend class PlayerView;
    friend class Map;

    bool didWin = false;

    void update(Event &event) override;
    void draw(SDL_Renderer *renderer, float dt) override;
    bool won() const;

    Player();
    Player(float x, float y);

    void init(std::shared_ptr<Map> map);

    ~Player();
};
