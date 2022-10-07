#include "game/map.hpp"

#include <SDL2/SDL2_gfxPrimitives.h>

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
  return std::move(SDL_Point{point.x + mapRect.x, point.y + mapRect.y});
}

SDL_Point Map::getAbsoluteCoOrdinates(Functions::PointF point)
{
  return SDL_Point{(int)point.x + mapRect.x, (int)point.y + mapRect.y};
}

void Map::drawWalls(SDL_Renderer *renderer)
{
  for (auto &wall : walls)
  {
    SDL_Point absolutePoints[wall.points.size()];
    COLOR_WHITE(renderer);
    if (wall.colliding)
      COLOR_RED(renderer)
    for (int i = 0; i < wall.points.size(); i++)
      absolutePoints[i] = getAbsoluteCoOrdinates(wall.points[i]);
    SDL_RenderDrawLines(renderer, absolutePoints, wall.points.size());
  }
}

void Map::drawCollisionPoints(SDL_Renderer *renderer)
{
  COLOR_BLACK(renderer);
  for (auto &ray : player->rays)
  {
    SDL_Point absolutePoint = getAbsoluteCoOrdinates(ray.endPosition);
    filledCircleRGBA(renderer, absolutePoint.x, absolutePoint.y, 2, 0, 0, 0, 255);
    if (ray.hitWallStartPoint != nullptr)
    {
      absolutePoint = getAbsoluteCoOrdinates(*ray.hitWallStartPoint);
      filledCircleRGBA(renderer, absolutePoint.x, absolutePoint.y, 2, 255, 255, 255, 255);
    }
  }
}

void Map::generateRandomWalls(unsigned int number)
{
  for (int i = 0; i < number; i++)
  {
    SDL_Point p1 = {rand() % mapRect.w, rand() % mapRect.h};
    SDL_Point p2 = {rand() % mapRect.w, rand() % mapRect.h};
    walls.push_back(Wall{"blue", "random", {p1, p2}});
  }
}

void Map::draw(SDL_Renderer *renderer)
{
  COLOR_WHITE(renderer);
  SDL_RenderDrawRect(renderer, &mapRect);
  drawWalls(renderer);
  drawCollisionPoints(renderer);
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
    std::string color = jsonWalls[index].get("color", "white").asString();

    Json::Value &jsonPoints = jsonWalls[index]["points"];
    std::vector<SDL_Point> points;
    for (Json::Value::ArrayIndex i = 0; i < jsonPoints.size(); ++i)
      points.push_back(SDL_Point{jsonPoints[i].get("x", -1).asInt(), jsonPoints[i].get("y", -1).asInt()});

    walls.push_back(Wall{color, name, std::move(points)});

    Logger::Debug("Wall %d Color: %s", index, walls[index].color.c_str());
  }
}
#endif
