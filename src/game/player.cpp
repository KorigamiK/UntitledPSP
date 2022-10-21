#include "game/player.hpp"

#include <iostream>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "utils/colors.hpp"

void Player::rayMarch()
{
    for (auto &ray : rays)
        ray.march();
}

bool Player::won() const
{
    return targetsHit >= map->levelTargets;
}

void Player::checkWin()
{
    didWin = won();
}

bool Player::checkCollision(Functions::PointF point)
{
    SDL_Point positionSDL = map->getAbsoluteCoOrdinates(point);
    if (!SDL_PointInRect(&positionSDL, &map->mapRect))
        return true;

    for (auto &wall : map->walls)
    {
        if (wall.isTarget)
        {
            if (!wall.colliding)
                for (int i = 0; i < wall.points.size() - 1; i++)
                    if (Functions::LineCircleIntersection(point, PLAYER_SIZE, wall.points[i], wall.points[i + 1]))
                    {
                        wall.colliding = true;
                        Logger::Debug("Player::checkCollision() - Target Hit at %d", targetsHit);
                        targetsHit++;
                        return false;
                    }
        }
        else
        {
            wall.colliding = false;
            for (int i = 0; i < wall.points.size() - 1; i++)
                if (Functions::LineCircleIntersection(point, PLAYER_SIZE, wall.points[i], wall.points[i + 1]))
                {
                    wall.colliding = true;
                    return true;
                }
        }
    }
    return false;
}

void Player::update(Event &event)
{
    switch (event)
    {
    case Event::UP:
        movingUp = true;
        break;
    case Event::DOWN:
        movingDown = true;
        break;
    case Event::LEFT:
        movingLeft = true;
        break;
    case Event::RIGHT:
        movingRight = true;
        break;

    case Event::UP_RELEASE:
        movingUp = false;
        break;
    case Event::DOWN_RELEASE:
        movingDown = false;
        break;
    case Event::LEFT_RELEASE:
        movingLeft = false;
        break;
    case Event::RIGHT_RELEASE:
        movingRight = false;
        break;
    case Event::ROTATE_LEFT:
        rotatingLeft = true;
        break;
    case Event::ROTATE_RIGHT:
        rotatingRight = true;
        break;
    case Event::ROTATE_LEFT_RELEASE:
        rotatingLeft = false;
        break;
    case Event::ROTATE_RIGHT_RELEASE:
        rotatingRight = false;
        break;
    case Event::ROTATE_LEFT_MOUSE:
        angle -= angleStep * 5;
        break;
    case Event::ROTATE_RIGHT_MOUSE:
        angle += angleStep * 5;
        break;
    case Event::ROTATE_UP:
        verticalAngle += angleStep;
        break;
    case Event::ROTATE_DOWN:
        verticalAngle -= angleStep;
        break;
    default:
        break;
    }
}

void Player::move(float dt)
{

    if (movingLeft)
    {
        xGoal += moveStep * cos(angle - M_PI / 2) * dt;
        yGoal += moveStep * sin(angle - M_PI / 2) * dt;
    }

    if (movingRight)
    {
        xGoal -= moveStep * cos(angle - M_PI / 2) * dt;
        yGoal -= moveStep * sin(angle - M_PI / 2) * dt;
    }

    if (movingUp)
    {
        xGoal += moveStep * cos(angle) * dt;
        yGoal += moveStep * sin(angle) * dt;
    }

    if (movingDown)
    {
        xGoal -= moveStep * cos(angle) * dt;
        yGoal -= moveStep * sin(angle) * dt;
    }

    if (rotatingLeft)
        angle -= angleStep * dt;

    if (rotatingRight)
        angle += angleStep * dt;

    if (checkCollision({xGoal, yGoal}))
    {
        xGoal = position.x;
        yGoal = position.y;
    }
    else
    {
        position.x = xGoal;
        position.y = yGoal;
    }

    position.x = Functions::Lerp(xGoal, position.x, dt);
    position.y = Functions::Lerp(yGoal, position.y, dt);

    updateRays();
    rayMarch();
}

void Player::draw(SDL_Renderer *renderer, float dt)
{
    checkWin();
    move(dt);

    SDL_Point playerAbsPosition = map->getAbsoluteCoOrdinates(position);

    static Sint16 pointsX[RAYS_CASTED + 1];
    static Sint16 pointsY[RAYS_CASTED + 1];
    pointsX[0] = playerAbsPosition.x;
    pointsY[0] = playerAbsPosition.y;
    for (int i = 0; i < RAYS_CASTED; i++)
    {
        SDL_Point absoluteEndPoint = map->getAbsoluteCoOrdinates(rays[i].endPosition);
        pointsX[i + 1] = absoluteEndPoint.x;
        pointsY[i + 1] = absoluteEndPoint.y;
    }
    filledPolygonRGBA(renderer, pointsX, pointsY, RAYS_CASTED + 1, PLAYER_VIEW_COLOR, 255);

    filledCircleRGBA(renderer, playerAbsPosition.x, playerAbsPosition.y, PLAYER_SIZE, PLAYER_COLOR, 255);
}

void Player::init(std::shared_ptr<Map> map)
{
    this->map = map;
    for (auto &ray : rays)
        ray.map = map;
    updateRays();
}

Player::Player() : Entity()
{
    Logger::Info("Player created");
    name = "Player";
}

Player::Player(float x, float y) : Entity(), position{x, y}, xGoal{x}, yGoal{y}
{
    Logger::Info("Player created");
    name = "Player";
    updateRays();
}

Player::~Player()
{
    Logger::Info("Player Destructor");
}

void Player::updateRays()
{
    static float anglePerRay = (float)PLAYER_FIELD_OF_VIEW * Constants::OneDegreeRadian / (float)RAYS_CASTED;

    int i = 0;
    for (int a = -RAYS_CASTED / 2; a < RAYS_CASTED / 2; a++)
    {
        rays[a + RAYS_CASTED / 2].angle = angle + a * anglePerRay;
        rays[a + RAYS_CASTED / 2].position = SDL_Point{(int)position.x, (int)position.y};
    }
}