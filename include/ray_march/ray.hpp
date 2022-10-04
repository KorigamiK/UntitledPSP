#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include "game/map.hpp"

#include "utils/colors.hpp"
#include "utils/functions.hpp"
#include "game/entity.hpp"

#define PLAYER_VIEW_DISTANCE 200

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
    float distance = 0;

    void draw(SDL_Renderer *renderer) override;
    PointAndDistance march(); // returns the distance to the wall
    Functions::PointF getTarget();

    inline Ray(){};
    inline Ray(SDL_Point position, float angle, std::shared_ptr<Map> map) : position(position), angle(angle), map(map), endPosition(getTarget()){};
    inline ~Ray(){};
};