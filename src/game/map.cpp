#include "game/map.hpp"

Map::Map(const char *mapFileName) : mapFile(mapFileName){};

Map::~Map() { Logger::Info("Map Destructor"); }

void Map::init(Player *p)
{
  player = p;
#ifdef PLATFORM_PSP
  generateRandomWalls();
#else
  loadMap();
#endif
}

void Map::setMapRect(SDL_Rect mapRectAndPosition, int padding)
{
  mapRect = Map::getPaddedRect(mapRectAndPosition, padding);
}

SDL_Rect Map::getPaddedRect(SDL_Rect rect, int padding)
{
  rect.x += padding;
  rect.y += padding;
  rect.w -= padding * 2;
  rect.h -= padding * 2;
  return rect;
}

SDL_Point Map::getAbsoluteCoOrdinates(SDL_Point point)
{
  return SDL_Point{point.x + mapRect.x, point.y + mapRect.y};
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

void Map::generateRandomWalls(unsigned int number)
{
  for (int i = 0; i < number; i++)
  {
    SDL_Point p1 = {rand() % mapRect.w, rand() % mapRect.h};
    SDL_Point p2 = {rand() % mapRect.w, rand() % mapRect.h};
    walls.push_back(Wall{"blue", "random", p1, p2});
  }
}

void Map::draw(SDL_Renderer *renderer)
{
  COLOR_WHITE(renderer);
  SDL_RenderDrawRect(renderer, &mapRect);
  drawWalls(renderer);
}

/* TODO: Json doesn't work with the PSP */
#ifndef PLATFORM_PSP
void Map::loadMap()
{
  Logger::Info("Map::loadMap");
  Json::Value root;
  Json::Reader reader;
  std::ifstream file(mapFile);
  bool parsingSuccessful = reader.parse(file, root);
  if (!parsingSuccessful)
  {
    Logger::Error("Failed to parse map.json");
    return;
  }

  Json::Value &jsonWalls = root["walls"];
  for (int index = 0; index < jsonWalls.size(); ++index)
  {
    std::string name = jsonWalls[index].get("name", "name").asString();

    walls.push_back(Wall{
        jsonWalls[index].get("color", "blue").asString(), // Object
        name,
        SDL_Point{
            jsonWalls[index].get("p1", "A DEFAULT VALUE").get("x", "0").asInt(),
            jsonWalls[index]
                .get("p1", "A DEFAULT VALUE")
                .get("y", "0")
                .asInt()},
        SDL_Point{
            jsonWalls[index].get("p2", "A DEFAULT VALUE").get("x", "0").asInt(),
            jsonWalls[index]
                .get("p2", "A DEFAULT VALUE")
                .get("y", "0")
                .asInt()}});

    Logger::Debug("Wall %d Color: %s", index, walls[index].color.c_str());
  }
}
#endif
