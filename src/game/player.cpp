#include "game/player.hpp"

void Player::rayMarch()
{
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
    default:
        break;
    }
    rayMarch();
}

void Player::draw(SDL_Renderer *renderer)
{
    ray.draw(renderer);
    COLOR_BLUE(renderer);
    SDL_Point relativePos = map->getAbsoluteCoOrdinates(position);
    SDL_Rect r = {relativePos.x - PLAYER_SIZE / 2, relativePos.y - PLAYER_SIZE / 2, PLAYER_SIZE, PLAYER_SIZE};
    SDL_RenderFillRect(renderer, &r);
}

void Player::init(std::shared_ptr<Map> map)
{
    this->map = map;
    ray.map = map;
}

Player::Player() : Entity(), ray(position, angle, map)
{
    Logger::Info("Player created");
    name = "Player";
}

Player::Player(int x, int y) : Entity(), position{x, y}, ray(position, angle, map)
{
    Logger::Info("Player created");
    name = "Player";
}

Player::~Player()
{
    Logger::Info("Player Destructor");
}
