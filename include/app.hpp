#pragma once

#include <SDL2/SDL.h>
#include <json/json.h>
#include <fstream>
#include <vector>

#include "map.hpp"

#define COLOR_WHITE(x) SDL_SetRenderDrawColor(x, 255, 255, 255, 255);
#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 272

// * Singleton Application class
class App
{
private:
    App() = default;

    SDL_Window *window = nullptr;
    SDL_Joystick *joystick = nullptr;
    SDL_Renderer *renderer = nullptr;

#ifdef PLATFORM_PSP
    const char *mapFile = "map.json";
#else
    const char *mapFile = "res/map.json";
#endif

    static App _instance;
    void loadMap();

    friend class Player;
    friend int main(int argc, char *argv[]);

public:
    int width = WINDOW_WIDTH, height = WINDOW_HEIGHT;

    App(const App &) = delete;
    std::vector<Wall> walls;

    static App &get() { return _instance; };

    void init();

    void draw();

    void rerender();

    void drawWalls();

    ~App();
};
