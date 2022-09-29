#include "app.hpp"

App App::_instance;

void App::draw()
{
    SDL_SetRenderDrawColor(renderer, 41, 41, 41, 255);
    SDL_RenderClear(renderer);

    SDL_GetWindowSize(window, &width, &height);

    map->setMapRect(SDL_Rect{width / 2, 0, width / 2, height}, 10);
    player->draw(renderer);
    map->draw(renderer);
}

void App::rerender()
{
    SDL_RenderPresent(renderer);
}

void App::init()
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

    map = std::make_shared<Map>(SDL_Rect{width / 2, 0, width / 2, height});
    player = new Player(map->mapRect.w / 2, map->mapRect.h / 2);
    player->init(map);
    map->init(player);
}

App::~App()
{
    SDL_Log("App Destructor");
    SDL_JoystickClose(joystick);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    delete player;
}