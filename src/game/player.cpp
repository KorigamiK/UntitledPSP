#include "game/player.hpp"

void Player::update(Event &event)
{
    SDL_Log("Player::update %d", event);
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
}

void Player::draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Point relativePos = map->getAbsoluteCoOrdinates(position);
    SDL_Rect r = {relativePos.x - PLAYER_SIZE / 2, relativePos.y - PLAYER_SIZE / 2, PLAYER_SIZE, PLAYER_SIZE};
    SDL_RenderFillRect(renderer, &r);
    SDL_RenderDrawLine(renderer, relativePos.x, relativePos.y, relativePos.x + PLAYER_DRECTION_SIZE * cos(angle), relativePos.y + PLAYER_DRECTION_SIZE * sin(angle));
}

void Player::init(std::shared_ptr<Map> map)
{
    this->map = map;
}

Player::Player() : Entity()
{
    SDL_Log("Player created");
    name = "Player";
}

Player::Player(int x, int y) : Entity(), position{x, y}
{
    SDL_Log("Player created");
    name = "Player";
}

Player::~Player()
{
    SDL_Log("Player Destructor");
}
