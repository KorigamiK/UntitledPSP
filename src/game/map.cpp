#include "game/map.hpp"

Map::Map(const char *mapFileName) : mapFile(mapFileName){};

Map::~Map() { SDL_Log("Map Destroyed"); }

void Map::init(Player *p)
{
    player = p;
    loadMap();
}

void Map::setMapRect(SDL_Rect mapRectAndPosition, int padding)
{
    mapRect = Map::getPaddedRect(mapRectAndPosition, padding);
}

void Map::drawWalls(SDL_Renderer *renderer)
{
    COLOR_WHITE(renderer);
    for (auto &wall : walls)
    {
        auto p1 = getAbsoluteCoOrdinates(wall.p1);
        auto p2 = getAbsoluteCoOrdinates(wall.p2);
        SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
    }
}

void Map::draw(SDL_Renderer *renderer)
{
    COLOR_WHITE(renderer);
    SDL_RenderDrawRect(renderer, &mapRect);
    drawWalls(renderer);
}

void Map::loadMap()
{
    SDL_Log("Map::loadMap");
    Json::Value root;
    Json::Reader reader;
    std::ifstream file(mapFile);
    bool parsingSuccessful = reader.parse(file, root);
    if (!parsingSuccessful)
    {
        SDL_Log("Failed to parse map.json");
        return;
    }

    Json::Value &jsonWalls = root["walls"];
    for (int index = 0; index < jsonWalls.size(); ++index)
    {
        std::string name = jsonWalls[index].get("name", "name").asString();

        walls.push_back(
            Wall{
                jsonWalls[index].get("color", "blue").asString(), // Object
                name,
                SDL_Point{
                    jsonWalls[index].get("p1", "A DEFAULT VALUE").get("x", "0").asInt(),
                    jsonWalls[index].get("p1", "A DEFAULT VALUE").get("y", "0").asInt()},
                SDL_Point{
                    jsonWalls[index].get("p2", "A DEFAULT VALUE").get("x", "0").asInt(),
                    jsonWalls[index].get("p2", "A DEFAULT VALUE").get("y", "0").asInt()}});

        SDL_Log("Wall %d Color: %s", index, walls.at(index).color.c_str());
    }
}

SDL_Point Map::getAbsoluteCoOrdinates(SDL_Point point)
{
    return SDL_Point{point.x + mapRect.x, point.y + mapRect.y};
}