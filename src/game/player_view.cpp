#include "game/player_view.hpp"

PlayerView::~PlayerView()
{
    Logger::Info("PlayerView destroyed");
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

void PlayerView::draw(SDL_Renderer *renderer)
{
    drawFloor(renderer);
    COLOR_WHITE(renderer)
    SDL_RenderDrawRect(renderer, &viewRect);

    static float angleBetweenRays = Constants::OneDegreeRadian * PLAYER_FIELD_OF_VIEW / (float)RAYS_CASTED;

    float maxX = 2.0f * PLAYER_VIEW_DISTANCE * sin(.5f * PLAYER_FIELD_OF_VIEW * Constants::OneDegreeRadian);

    static float wallHeight = .5f * 80 / tan(.5f * PLAYER_VERTICAL_FIELD_OF_VIEW_DEG * Constants::OneDegreeRadian);

    static float cameraMaxDistance = PLAYER_VIEW_DISTANCE * cos(.5f * PLAYER_FIELD_OF_VIEW * Constants::OneDegreeRadian);

    float floorLevel = 0.5f * viewRect.h * (1 + tan(player->verticalAngle) / tan(0.5f * PLAYER_VERTICAL_FIELD_OF_VIEW_DEG * Constants::OneDegreeRadian));

    SDL_Texture *wallTexture = TextureController::getTexture("colorstone");

    float relativeAngle;

    for (auto &ray : player->rays)
    {
        relativeAngle = ray.angle - player->angle;

        float distanceFromCamera = distanceFromCameraPlane(ray.distance, player->angle, ray.angle);

        // Destination rectangle
        float rectH = viewRect.h * wallHeight / distanceFromCamera;
        float rectY = floorLevel - 0.5f * rectH;
        float rectX = 0.5f * maxX - cameraMaxDistance * tan(relativeAngle);

        float rectW = cameraMaxDistance * (tan(relativeAngle) - tan(relativeAngle - angleBetweenRays));

        if (rectX + rectW > viewRect.w + viewRect.x)
            continue;

        SDL_Rect destRect = {(int)rectX, (int)rectY, (int)std::max<float>(round(rectW), 4), (int)rectH};

        if (ray.distance == PLAYER_VIEW_DISTANCE)
        {
            COLOR_WHITE(renderer)
            auto absoluteCooridinates = getAbsoluteCoOrdinates({(int)rectX, (int)rectY});
            destRect.x = absoluteCooridinates.x;
            destRect.y = absoluteCooridinates.y;
            SDL_RenderFillRect(renderer, &destRect);
            continue;
        }

        float brightness = 255 * (1 - distanceFromCamera / PLAYER_VIEW_DISTANCE);

        // Source rectangle
        int textureX = (int)Functions::Distance(ray.endPosition, Functions::PointF(*ray.hitWallStartPoint)) % SPRITE_WIDTH;
        SDL_Rect srcRect = {textureX, 0, (int)rectW, SPRITE_HEIGHT};

        auto absoluteCooridinates = getAbsoluteCoOrdinates({(int)rectX, (int)rectY});
        destRect.x = absoluteCooridinates.x;
        destRect.y = absoluteCooridinates.y;

        SDL_SetTextureColorMod(wallTexture, brightness, brightness, brightness);
        SDL_RenderCopy(renderer, wallTexture, &srcRect, &destRect);
    }
}