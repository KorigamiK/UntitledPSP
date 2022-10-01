#include "utils/functions.hpp"

double Functions::PointDistance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

bool Functions::PointOnLine(PointF p1, PointF p2, PointF t)
{
    if (fmin(p1.x, p2.x) <= t.x && t.x <= fmax(p1.x, p2.x) && fmin(p1.y, p2.y) <= t.y && t.y <= fmax(p1.y, p2.y))
        return true;

    return false;
}

double Functions::Distance(PointF p1, PointF p2)
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}