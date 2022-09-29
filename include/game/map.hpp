#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <json/json.h>
#include <fstream>
#include "game/entity.hpp"
#include "game/object.hpp"

#define COLOR_WHITE(x) SDL_SetRenderDrawColor(x, 255, 255, 255, 255);

class Player;

class Map : public Entity
{
private:
    friend class App;
    friend class Player;

    Player *player;
    SDL_Rect mapRect = {0, 0, 100, 100}; // x, y, w, h

#ifdef PLATFORM_PSP
    const char *mapFile = "map.json";
#else
    const char *mapFile = "res/map.json";
#endif

    std::vector<Wall> walls;

    SDL_Point getRelativeCoOrdinates(SDL_Point point);

    static SDL_Rect getPaddedRect(SDL_Rect rect, int padding)
    {
        return SDL_Rect{rect.x + padding, rect.y + padding, rect.w - padding * 2, rect.h - padding * 2};
    }

public:
    Map(const char *mapFile);
    Map(SDL_Rect mapRectAndPosition, int padding = 10) : mapRect(Map::getPaddedRect(mapRectAndPosition, padding)){};
    Map(){};

    void init(Player *p);
    void loadMap();
    void setMapRect(SDL_Rect mapRectAndPosition, int padding = 10);

    void draw(SDL_Renderer *renderer) override;
    void drawWalls(SDL_Renderer *renderer);

    ~Map();
};
