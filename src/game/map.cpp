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
  generateRandomTargets(levelTargets);
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
    {
      if (wall.isTarget)
        COLOR_GREEN(renderer);
      else
        COLOR_RED(renderer);
    }
    for (int i = 0; i < wall.points.size(); i++)
      absolutePoints[i] = getAbsoluteCoOrdinates(wall.points[i]);
    SDL_RenderDrawLines(renderer, absolutePoints, wall.points.size());
  }
}

PointPair Map::getRandomPoints(int maxDistance, int minDistance)
{
  PointPair points;
  points.point1 = SDL_Point{Functions::randomInt(0, mapRect.w - 80), Functions::randomInt(0, mapRect.h - 80)};

  points.point2 = SDL_Point{Functions::randomInt(0, mapRect.w - 80), Functions::randomInt(0, mapRect.h - 80)};

  int distance = Functions::Distance(points.point1, points.point2);
  if (distance > maxDistance || distance < minDistance)
    return getRandomPoints(maxDistance, minDistance);
  return std::move(points);
}

SDL_Point Map::getRandomPointFrom(SDL_Point point, int maxDistance, int minDistance)
{
  SDL_Point newPoint = SDL_Point{Functions::randomInt(0, mapRect.w - 80), Functions::randomInt(0, mapRect.h - 80)};

  int distance = Functions::Distance(point, newPoint);
  if (distance > maxDistance || distance < minDistance)
    return getRandomPointFrom(point, maxDistance, minDistance);
  return std::move(newPoint);
}

void Map::drawCollisionPoints(SDL_Renderer *renderer)
{
  for (auto &ray : player->rays)
  {
    SDL_Point absolutePoint = getAbsoluteCoOrdinates(ray.endPosition);
    if (ray.distance != PLAYER_VIEW_DISTANCE)
      filledCircleRGBA(renderer, absolutePoint.x, absolutePoint.y, 2, ACCENT, 0xff);
  }
}

void Map::generateRandomWalls(unsigned int number)
{
  for (int i = 0; i < number; i++)
  {
    PointPair points = getRandomPoints(100, 60);
    SDL_Point p3 = getRandomPointFrom(points.point2, 100, 60);
    walls.push_back(Wall{"blue", "random", {points.point1, points.point2, p3}});
  }
}

void Map::generateRandomTargets(unsigned int number)
{
  for (int i = 0; i < number; i++)
  {
    PointPair points = getRandomPoints(100, 60);
    Logger::Debug("Target Points: %d, %d, %d, %d", points.point1.x, points.point1.y, points.point2.x, points.point2.y);
    walls.push_back(Wall{"red", "target", {points.point1, points.point2}, false, true});
  }
}

void Map::draw(SDL_Renderer *renderer)
{
  COLOR_WHITE(renderer);
  SDL_RenderDrawRect(renderer, &mapRect);
  drawWalls(renderer);
#ifdef VERBOSE
  drawCollisionPoints(renderer);
#endif
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
