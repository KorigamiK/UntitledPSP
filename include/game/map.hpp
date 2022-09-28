#pragma once

#include <string>
#include "game/object.hpp"
#include <SDL2/SDL.h>
#include <json/json.h>
#include <fstream>

class Map
{
private:
    friend class App;

#ifdef PLATFORM_PSP
    const char *mapFile = "map.json";
#else
    const char *mapFile = "res/map.json";
#endif

    std::vector<Wall> walls;

public:
    Map(const char *mapFile);
    Map() = default;

    void loadMap();

    ~Map();
};
