#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <json/json.h>
#include <fstream>
#include "game/object.hpp"
#include "game/player.hpp"

class Map
{
private:
    friend class App;
    std::shared_ptr<Player> player;

#ifdef PLATFORM_PSP
    const char *mapFile = "map.json";
#else
    const char *mapFile = "res/map.json";
#endif

    std::vector<Wall> walls;

public:
    Map(const char *mapFile);
    Map(std::shared_ptr<Player> p) : player(p){};
    Map(){};
    void loadMap();

    ~Map();
};
