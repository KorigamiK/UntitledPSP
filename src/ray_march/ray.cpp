#include "ray_march/ray.hpp"

void Ray::draw(SDL_Renderer *renderer)
{
    COLOR_BLUE(renderer);
    if (map != nullptr && distance != 0)
    {
        auto startAbsolutePos = map->getAbsoluteCoOrdinates(position);
        auto endAbsolutePos = map->getAbsoluteCoOrdinates({(int)endPosition.x, (int)endPosition.y});
        if (distance != PLAYER_VIEW_DISTANCE)
            COLOR_RED(renderer)
        else
            COLOR_GREEN(renderer)
        SDL_RenderDrawLine(renderer, startAbsolutePos.x, startAbsolutePos.y, endAbsolutePos.x, endAbsolutePos.y);
    }
}

Functions::PointF Ray::getTarget()
{
    return {position.x + PLAYER_VIEW_DISTANCE * cos(angle), position.y + PLAYER_VIEW_DISTANCE * sin(angle)};
}

PointAndDistance Ray::march()
{
    float closestDistance = PLAYER_VIEW_DISTANCE;
    auto closestPoint = getTarget();

    for (auto &wall : map->walls)
    {
        auto target = getTarget();
        float a1 = target.y - position.y;
        float b1 = position.x - target.x;
        float c1 = a1 * (position.x) + b1 * (position.y);

        float a2 = wall.p2.y - wall.p1.y;
        float b2 = wall.p1.x - wall.p2.x;
        float c2 = a2 * (wall.p1.x) + b2 * (wall.p1.y);

        float determinant = a1 * b2 - a2 * b1;

        if (determinant != 0)
        {
            float x = (b2 * c1 - b1 * c2) / determinant;
            float y = (a1 * c2 - a2 * c1) / determinant;

            if (Functions::PointOnLine(wall.p1, wall.p2, {x, y}) && Functions::PointOnLine(position, target, {x, y}))
            {
                if (Functions::Distance(position, {x, y}) < closestDistance)
                {
                    closestDistance = (int)Functions::Distance(position, {x, y});
                    closestPoint = {x, y};
                }
            }
        }
    }

    endPosition = closestPoint;
    distance = closestDistance;

    return {closestPoint, closestDistance};
}