#pragma once
// Some useful functions

#include <cmath>
#include <SDL2/SDL.h>

namespace Functions
{
    struct PointF
    {
        float x, y;
        PointF(float x, float y) : x(x), y(y){};
        PointF(SDL_Point p) : x(p.x), y(p.y){};
    };

    // Find the distance between two points
    double PointDistance(int x1, int y1, int x2, int y2);

    double Distance(PointF p1, PointF p2);

    // Check if a point t is on a line segment p1-p2
    bool PointOnLine(PointF p1, PointF p2, PointF t);
}
