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
            x -= moveStep;
            break;
        case SDLK_RIGHT:
            x += moveStep;
            break;
        case SDLK_UP:
            y -= moveStep;
            break;
        case SDLK_DOWN:
            y += moveStep;
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
    SDL_Rect r = {x, y, 4, 4};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &r);
}

Player::Player() : Entity()
{
    SDL_Log("Player created");
    name = "Player";
}

Player::Player(int x, int y) : Entity(), x(x), y(y)
{
    SDL_Log("Player created");
    name = "Player";
}

Player::~Player()
{
    SDL_Log("Player destroyed");
}
