#pragma once

class Map;

#include <memory>
#include <SDL2/SDL.h>

#include "utils/colors.hpp"
#include "utils/functions.hpp"
#include "game/entity.hpp"

#define PLAYER_VIEW_DISTANCE 230

typedef struct
{
    Functions::PointF point;
    float distance;
} PointAndDistance;

class Ray : public Entity
{
private:
    std::shared_ptr<Map> map;

    SDL_Point position;
    float angle;

public:
    friend class Player;
    friend class PlayerView;

    Functions::PointF endPosition{0, 0};
    SDL_Point *hitWallStartPoint = nullptr;
    int hitWallIndex = -1;
    float distance = 0;

    void draw(SDL_Renderer *renderer) override;
    PointAndDistance march(); // returns the distance to the wall
    Functions::PointF getTarget();

    inline Ray(){};
    inline Ray(SDL_Point position, float angle, std::shared_ptr<Map> map) : position(position), angle(angle), map(map), endPosition(getTarget()){};
    inline ~Ray(){};
};