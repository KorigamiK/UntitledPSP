#include "game/map.hpp"

Map::Map(const char *mapFileName) : mapFile(mapFileName){};

Map::~Map() { SDL_Log("Map Destroyed"); }

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