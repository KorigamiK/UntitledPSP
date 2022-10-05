#pragma once

#include <memory>

#include "utils/colors.hpp"
#include "utils/logger.hpp"
#include "game/entity.hpp"
#include "game/player.hpp"

class PlayerView : Entity
{
private:
  Player *player;

  SDL_Rect viewRect = {0, 0, 100, 100};

  SDL_Point getAbsoluteCoOrdinates(SDL_Point relativePos);
  float distanceFromCameraPlane(float distanceFromPlayer, float playerAngle, float rayAngle);
  void drawFloor(SDL_Renderer *renderer);

public:
  void setViewRect(SDL_Rect rect);

  PlayerView(Player *p, SDL_Rect view) : Entity(), player(p), viewRect(view) {}
  ~PlayerView();
  void draw(SDL_Renderer *renderer) override;
};