#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <json/json.h>
#include <fstream>

#include "utils/logger.hpp"
#include "utils/colors.hpp"
#include "game/entity.hpp"
#include "game/object.hpp"

class Player;

class Map : public Entity
{
private:
    friend class App;
    friend class Player;
    friend class Ray;

    Player *player;
    SDL_Rect mapRect = {0, 0, 100, 100}; // x, y, w, h

    const char *mapFile = "res/map.json";

    std::vector<Wall> walls;

    static SDL_Rect getPaddedRect(SDL_Rect rect, int padding);

    void generateRandomWalls(unsigned int number = 3);

public:
    Map(const char *mapFile);
    Map(SDL_Rect mapRectAndPosition, int padding = 10) : mapRect(Map::getPaddedRect(mapRectAndPosition, padding)){};
    Map(){};

    void init(Player *p);
    void loadMap();
    void setMapRect(SDL_Rect mapRectAndPosition, int padding = 10);
    SDL_Point getAbsoluteCoOrdinates(SDL_Point point);

    void draw(SDL_Renderer *renderer) override;
    void drawWalls(SDL_Renderer *renderer);

    ~Map();
};
