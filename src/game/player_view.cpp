#include "game/player_view.hpp"

PlayerView::~PlayerView()
{
    Logger::Info("PlayerView destroyed");
}

void PlayerView::draw(SDL_Renderer *renderer)
{
    drawFloor(renderer);
    COLOR_WHITE(renderer)
    SDL_RenderDrawRect(renderer, &viewRect);

    static float maxX = 2.0f * PLAYER_VIEW_DISTANCE * sin(.5f * PLAYER_FIELD_OF_VIEW * Constants::OneDegreeRadian);
    static float wallHeight = .5f * 80 / tan(.5f * PLAYER_VERTICAL_FIELD_OF_VIEW_DEG * Constants::OneDegreeRadian);
    static float playerDistanceHeadOn = PLAYER_VIEW_DISTANCE * cos(.5f * PLAYER_FIELD_OF_VIEW * Constants::OneDegreeRadian);

    float floorLevel = 0.5f * viewRect.h * (1 + tan(player->verticalAngle) / tan(0.5f * PLAYER_VERTICAL_FIELD_OF_VIEW_DEG * Constants::OneDegreeRadian));
    float prevX = 0;

    SDL_Texture *wallTexture = TextureController::getTexture("colorstone");

    for (auto &ray : player->rays)
    {
        float distanceFromCamera = distanceFromCameraPlane(ray.distance, player->angle, ray.angle);
        float rectH = viewRect.h * wallHeight / distanceFromCamera;
        float rectY = floorLevel - 0.5f * rectH;
        float rectX = 0.5f * maxX - playerDistanceHeadOn * tan(player->angle - ray.angle);
        float rectW = std::max(rectX - prevX, 4.0f);

        if (rectX + rectW > viewRect.w + viewRect.x)
            continue;

        prevX = rectX;
        SDL_Rect destRect = {(int)rectX, (int)rectY, (int)rectW, (int)rectH};

        if (ray.distance == PLAYER_VIEW_DISTANCE)
        {
            COLOR_WHITE(renderer)
            auto absoluteCooridinates = getAbsoluteCoOrdinates({(int)rectX, (int)rectY});
            destRect.x = absoluteCooridinates.x;
            destRect.y = absoluteCooridinates.y;
            SDL_RenderFillRect(renderer, &destRect);
            continue;
        }

        float brightness = 255 * (1 - 0.5f * distanceFromCamera / PLAYER_VIEW_DISTANCE);

        SDL_Rect srcRect = {(int)Functions::Distance(ray.endPosition, Functions::PointF(*ray.hitWallStartPoint)) % SPRITE_WIDTH, 0, (int)rectW, SPRITE_HEIGHT};

        auto absoluteCooridinates = getAbsoluteCoOrdinates({(int)rectX, (int)rectY});
        destRect.x = absoluteCooridinates.x;
        destRect.y = absoluteCooridinates.y;

        SDL_SetTextureColorMod(wallTexture, brightness, brightness, brightness);
        SDL_RenderCopy(renderer, wallTexture, &srcRect, &destRect);
    }
}

void PlayerView::setViewRect(SDL_Rect rect)
{
    viewRect = rect;
}

SDL_Point PlayerView::getAbsoluteCoOrdinates(SDL_Point relativePos)
{
    return std::move(SDL_Point{relativePos.x + viewRect.x, relativePos.y + viewRect.y});
}

float PlayerView::distanceFromCameraPlane(float distanceFromPlayer, float playerAngle, float rayAngle)
{
    return distanceFromPlayer * cos(rayAngle - playerAngle);
}

void PlayerView::drawFloor(SDL_Renderer *renderer)
{
    COLOR_GREEN(renderer);
    float floorLevel = 0.5f * viewRect.h * (1 + tan(player->verticalAngle) / tan(0.5f * PLAYER_VERTICAL_FIELD_OF_VIEW_DEG * Constants::OneDegreeRadian));
    SDL_Rect rect = {viewRect.x, (int)floorLevel, viewRect.w, viewRect.h - (int)floorLevel};
    SDL_RenderFillRect(renderer, &rect);
}