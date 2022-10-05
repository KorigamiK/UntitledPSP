#include "game/state/base.hpp"

class NotImplemented : public BaseState
{
private:
    SDL_Renderer *renderer;
    SDL_Texture *titleTexture = nullptr;
    SDL_Texture *subTitleTexture = nullptr;

public:
    NotImplemented(SDL_Renderer *renderer);

    void handleEvent(Event &event) override;
    void draw(float dt, int w, int h) override;
    bool isDone() override { return this->done; }
    inline State getNextState() override { return State::Menu; }

    ~NotImplemented();
};
