#include "ray_march/ray.hpp"
#include "game/map.hpp"

void Ray::draw(SDL_Renderer *renderer)
{
    COLOR_BLUE(renderer);
    if (map != nullptr && distance != 0)
    {
        auto startAbsolutePos = map->getAbsoluteCoOrdinates(position);
        auto endAbsolutePos = map->getAbsoluteCoOrdinates(SDL_Point{(int)endPosition.x, (int)endPosition.y});
        if (distance != PLAYER_VIEW_DISTANCE)
            COLOR_RAY_PRIMARY(renderer);
        else
            COLOR_RAY_SECONDARY(renderer);
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

    auto target = getTarget();
    hitWallStartPoint = nullptr;
    for (auto &wall : map->walls)
    {
        float a1 = target.y - position.y;
        float b1 = position.x - target.x;
        float c1 = a1 * (position.x) + b1 * (position.y);

        for (auto i = 0; i < wall.points.size() - 1; i++)
        {
            auto &p1 = wall.points[i];
            auto &p2 = wall.points[i + 1];
            float a2 = p2.y - p1.y;
            float b2 = p1.x - p2.x;
            float c2 = a2 * (p1.x) + b2 * (p1.y);

            float determinant = a1 * b2 - a2 * b1;

            // The lines are parallel.
            if (determinant == 0)
                continue;

            float x = (b2 * c1 - b1 * c2) / determinant;
            float y = (a1 * c2 - a2 * c1) / determinant;

            if (Functions::PointOnLine(p1, p2, {x, y}) && Functions::PointOnLine(position, target, {x, y}))
            {
                auto distance = Functions::Distance(position, {x, y});
                if (distance < closestDistance)
                {
                    hitWallStartPoint = &p1;
                    closestDistance = distance;
                    closestPoint = {x, y};
                }
            }
        }
    }

    endPosition = closestPoint;
    distance = closestDistance;

    return {closestPoint, closestDistance};
}