#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <memory>

#include "utils/eventController.hpp"
#include "utils/audioController.hpp"
#include "game/map.hpp"
#include "game/player.hpp"

#define COLOR_WHITE(x) SDL_SetRenderDrawColor(x, 255, 255, 255, 255);
#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 272

// * Singleton Application class
class App
{
private:
    App(){};

    bool running = true;

    Player *player;
    std::shared_ptr<Map> map;
    EventController eventController;

    SDL_Window *window = nullptr;
    SDL_Joystick *joystick = nullptr;
    SDL_Renderer *renderer = nullptr;

    static App _instance;

    friend class Player;
    friend int main(int argc, char *argv[]);

    void loadMap();
    void handleBaseEvents(Event &event);

public:
    int width = WINDOW_WIDTH, height = WINDOW_HEIGHT;

    App(const App &) = delete;

    static App &get() { return _instance; };

    void init();

    void handleEvents();

    void draw();

    void rerender();

    ~App();
};
