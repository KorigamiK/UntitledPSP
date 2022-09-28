#include "app.hpp"

App App::_instance;

void App::drawWalls()
{
    for (auto &wall : map.walls)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, wall.p1.x, wall.p1.y, wall.p2.x, wall.p2.y);
    }
}

void App::draw()
{
    SDL_SetRenderDrawColor(renderer, 41, 41, 41, 255);
    SDL_RenderClear(renderer);

    SDL_GetWindowSize(window, &width, &height);
}

void App::rerender()
{
    SDL_RenderPresent(renderer);
}

void App::init(std::shared_ptr<Player> p)
{
    SDL_Log("App::init");

    // SET THIS TO ACTIVATE joystick
    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) < 0)
    {
        SDL_Log("SDL_Init: %s\n", SDL_GetError());
        throw std::runtime_error("SDL_Init failed");
    }

    // create an SDL window (pspgl enabled)
    window = SDL_CreateWindow("Untitled", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (!window)
    {
        SDL_Log("SDL_CreateWindow: %s\n", SDL_GetError());
        SDL_Quit();
        throw std::runtime_error("SDL_CreateWindow failed");
    }

    // create a renderer (OpenGL ES2)
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        SDL_Log("SDL_CreateRenderer: %s\n", SDL_GetError());
        SDL_Quit();
        throw std::runtime_error("SDL_CreateRenderer failed");
    }

    if (SDL_NumJoysticks() < 1)
        SDL_Log("No joysticks connected: %s\n", SDL_GetError());

    joystick = SDL_JoystickOpen(0);
    if (joystick == NULL)
    {
        SDL_Log("SDL_JoystickOpen: %s\n", SDL_GetError());
        // SDL_Quit();
        // return -1;
    }
    else
        SDL_Log("Joystick found: %s\n", SDL_JoystickName(joystick));

    player = p;
    map = Map(player);
    map.loadMap();
}

App::~App()
{
    SDL_Log("App Destructor");
    SDL_JoystickClose(joystick);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}