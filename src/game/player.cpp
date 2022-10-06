#include "game/player.hpp"

#include <SDL2/SDL2_gfxPrimitives.h>

void Player::rayMarch()
{
    for (auto &ray : rays)
        ray.march();
}

bool Player::checkCollision(Functions::PointF point)
{
    for (auto &wall : map->walls)
    {
        wall.colliding = false;
        for (int i = 0; i < wall.points.size() - 1; i++)
            if (Functions::LineCircleIntersection(point, PLAYER_SIZE, wall.points[i], wall.points[i + 1]))
            {
                wall.colliding = true;
                return true;
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
        angle -= angleStep;
        break;
    case Event::ROTATE_RIGHT:
        angle += angleStep;
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
    move(dt);

    for (auto &ray : rays)
        ray.draw(renderer);

    SDL_Point relativePos = map->getAbsoluteCoOrdinates(position);
    filledCircleRGBA(renderer, relativePos.x, relativePos.y, PLAYER_SIZE, 0, 0, 255, 255);
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
    static float anglePerRay = PLAYER_FIELD_OF_VIEW * Constants::OneDegreeRadian / RAYS_CASTED;

    int i = 0;
    for (int a = -RAYS_CASTED / 2; a < RAYS_CASTED / 2; a++)
    {
        rays[a + RAYS_CASTED / 2].angle = angle + a * anglePerRay;
        rays[a + RAYS_CASTED / 2].position = SDL_Point{(int)position.x, (int)position.y};
    }
}