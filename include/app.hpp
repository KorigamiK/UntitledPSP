#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <memory>

#include "utils/logger.hpp"
#include "utils/colors.hpp"
#include "utils/eventController.hpp"
#include "utils/audioController.hpp"
#include "utils/fontController.hpp"
#include "utils/textureController.hpp"
#include "game/map.hpp"
#include "game/player.hpp"
#include "game/player_view.hpp"
#include "game/state/controller.hpp"

#define DEBUG_MESSAGE_MAX 4

// * Singleton Application class
class App
{
private:
    static App _instance;

    App(){};

    bool running = true;
    std::deque<const char *> debugMessages = {};
    bool debugChanged = true;
    SDL_Texture *debugTexture = nullptr;

    EventController eventController;
    std::unique_ptr<StateController> stateController;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    friend class Player;
    friend int main(int argc, char *argv[]);

    void loadMap();
    void handleBaseEvents(Event &event);
    void renderDebugMessages();

public:
    int width = WINDOW_WIDTH, height = WINDOW_HEIGHT;

    App(const App &) = delete;

    static App &get() { return _instance; };

    void init();

    void handleEvents();

    void draw(float dt);

    void rerender();

    inline void addDebugMessage(const char *message)
    {
        if (debugMessages.size() == DEBUG_MESSAGE_MAX)
            debugMessages.pop_front();
        debugMessages.push_back(message);
        debugChanged = true;
    }

    ~App();
};
