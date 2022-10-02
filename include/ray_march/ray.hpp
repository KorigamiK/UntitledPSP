#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include "game/map.hpp"

#include "utils/colors.hpp"
#include "utils/functions.hpp"
#include "game/entity.hpp"

#define PLAYER_VIEW_DISTANCE 100

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

    Functions::PointF endPosition{0, 0};
    float distance = 0;

public:
    friend class Player;

    void draw(SDL_Renderer *renderer) override;
    PointAndDistance march(); // returns the distance to the wall
    Functions::PointF getTarget();

    inline Ray(){};
    inline Ray(SDL_Point position, float angle, std::shared_ptr<Map> map) : position(position), angle(angle), map(map), endPosition(getTarget()){};
    inline ~Ray(){};
};