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

int Functions::randomInt(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

double Functions::Distance(PointF p1, PointF p2)
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

float Functions::Lerp(float flGoal, float flCurrent, float dt)
{
    float flDifference = flGoal - flCurrent;

    if (flDifference > dt)
        return flCurrent + dt;
    if (flDifference < -dt)
        return flCurrent - dt;

    return flGoal;
}

bool Functions::LineCircleIntersection(PointF center, float radius, PointF p1, PointF p2)
{
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;

    float a = dx * dx + dy * dy;
    float b = 2 * (dx * (p1.x - center.x) + dy * (p1.y - center.y));
    float c = (p1.x - center.x) * (p1.x - center.x) + (p1.y - center.y) * (p1.y - center.y) - radius * radius;

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return false;

    discriminant = sqrt(discriminant);

    float t1 = (-b - discriminant) / (2 * a);
    float t2 = (-b + discriminant) / (2 * a);

    if (t1 >= 0 && t1 <= 1)
        return true;
    if (t2 >= 0 && t2 <= 1)
        return true;

    return false;
}
