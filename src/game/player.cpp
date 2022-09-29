#include "game/player.hpp"

void Player::update(SDL_Event &event)
{
    SDL_Log("Player::update %d", event.type);
    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
        case SDLK_a:
            position.x -= moveStep;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            position.x += moveStep;
            break;
        case SDLK_UP:
        case SDLK_w:
            position.y -= moveStep;
            break;
        case SDLK_DOWN:
        case SDLK_s:
            position.y += moveStep;
            break;
        case SDLK_q:
            angle -= angleStep;
            break;
        case SDLK_e:
            angle += angleStep;
            break;
        default:
            break;
        }
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
    SDL_Log("Player destroyed");
}
