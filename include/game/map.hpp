#pragma once

#include <string>
#include <algorithm>
#include <functional>
#include <SDL2/SDL.h>
#include <json/json.h>
#include <fstream>

#include "utils/functions.hpp"
#include "utils/logger.hpp"
#include "utils/colors.hpp"
#include "game/entity.hpp"
#include "game/object.hpp"
#include "game/player.hpp"

class Player;

struct PointPair
{
    SDL_Point point1;
    SDL_Point point2;
};

class Map : public Entity
{
private:
    friend class GameState;
    friend class Player;
    friend class PlayerView;
    friend class Ray;

    Player *player;
    SDL_Rect mapRect = {0, 0, 100, 100}; // x, y, w, h

    const char *mapFile = "res/map.json";

    std::vector<Wall> walls;

    static SDL_Rect getPaddedRect(SDL_Rect rect, int padding);

    void generateRandomWalls(unsigned int number = 3);
    void generateRandomTargets(unsigned int number = 1);
    void drawCollisionPoints(SDL_Renderer *renderer);
    PointPair getRandomPoints(int maxDistance = 100, int minDistance = 50);
    SDL_Point getRandomPointFrom(SDL_Point point, int maxDistance = 100, int minDistance = 50);

public:
    int const levelTargets = 1;

    Map(const char *mapFile);
    Map(SDL_Rect mapRectAndPosition, int padding = 10, int levelTargets = 1)
        : mapRect(Map::getPaddedRect(mapRectAndPosition, padding)), levelTargets(levelTargets){};
    Map(){};

    void init(Player *p);
    void loadMap();
    void setMapRect(SDL_Rect mapRectAndPosition, int padding = 10);
    SDL_Point getAbsoluteCoOrdinates(SDL_Point point);
    SDL_Point getAbsoluteCoOrdinates(Functions::PointF point);

    void draw(SDL_Renderer *renderer) override;
    void drawWalls(SDL_Renderer *renderer);

    ~Map();
};
