#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <memory>

#include "game/map.hpp"

#define COLOR_WHITE(x) SDL_SetRenderDrawColor(x, 255, 255, 255, 255);
#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 272

// * Singleton Application class
class App
{
private:
    App(){};

    std::shared_ptr<Player> player;
    std::shared_ptr<Map> map;

    SDL_Window *window = nullptr;
    SDL_Joystick *joystick = nullptr;
    SDL_Renderer *renderer = nullptr;

    static App _instance;
    void loadMap();

    friend class Player;
    friend int main(int argc, char *argv[]);

public:
    int width = WINDOW_WIDTH, height = WINDOW_HEIGHT;

    App(const App &) = delete;

    static App &get() { return _instance; };

    void init();

    void draw();

    void rerender();

    ~App();
};
