#include "game/player.hpp"

void Player::rayMarch()
{
    for (auto &ray : rays)
        ray.march();
}

void Player::update(Event &event)
{
    switch (event)
    {
    case Event::UP:
        position.y -= moveStep;
        break;
    case Event::DOWN:
        position.y += moveStep;
        break;
    case Event::LEFT:
        position.x -= moveStep;
        break;
    case Event::RIGHT:
        position.x += moveStep;
        break;
    case Event::ROTATE_LEFT:
        angle -= angleStep;
        break;
    case Event::ROTATE_RIGHT:
        angle += angleStep;
        break;
    case Event::ROTATE_UP:
        verticalAngle -= angleStep;
        break;
    case Event::ROTATE_DOWN:
        verticalAngle += angleStep;
        break;
    default:
        break;
    }
    updateRays();
    rayMarch();
}

void Player::draw(SDL_Renderer *renderer)
{
    for (auto &ray : rays)
        ray.draw(renderer);

    COLOR_BLUE(renderer);
    SDL_Point relativePos = map->getAbsoluteCoOrdinates(position);
    SDL_Rect r = {relativePos.x - PLAYER_SIZE / 2, relativePos.y - PLAYER_SIZE / 2, PLAYER_SIZE, PLAYER_SIZE};
    SDL_RenderFillRect(renderer, &r);
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

Player::Player(int x, int y) : Entity(), position{x, y}
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
        rays[a + RAYS_CASTED / 2].position = position;
    }
}