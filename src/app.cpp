#include "app.hpp"

App App::_instance;

void App::draw()
{
    SDL_SetRenderDrawColor(renderer, 41, 41, 41, 255);
    SDL_RenderClear(renderer);

    SDL_GetWindowSize(window, &width, &height);

    // write "Untitled" in the screen
    SDL_Texture *textTexture = FontController::getTexture(renderer, "Debug", {255, 255, 255});
    SDL_Rect textRect;
    SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
    textRect.x = textRect.w;
    textRect.y = height - textRect.h;
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);

#ifdef DEBUG
    renderDebugMessages();
#endif

    map->setMapRect(SDL_Rect{width / 2, 0, width / 2, height}, 10);
    player->draw(renderer);
    map->draw(renderer);
}

void App::renderDebugMessages()
{
    SDL_Rect textRect;
    SDL_Texture *textTexture;
    int i = 0;
    for (auto &message : debugMessages)
    {
        textTexture = FontController::getTexture(renderer, message, {255, 255, 255});
        SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
        textRect.x = 0;
        textRect.y = i * textRect.h;
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_DestroyTexture(textTexture);
        i++;
    }
}

void App::handleBaseEvents(Event &event)
{
    switch (event)
    {
    case Event::QUIT:
        running = false;
        break;
    case Event::CONFIRM:
        addDebugMessage("Confirm");
        AudioController::play(Sound::CONFIRM);
        break;
    }
}

void App::handleEvents()
{
    std::vector<Event> events = eventController.getEvents();
    for (auto &event : events)
    {
        handleBaseEvents(event);
        player->update(event);
    }
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
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER | SDL_INIT_TIMER) < 0)
    {
        SDL_Log("SDL_Init: %s\n", SDL_GetError());
        throw std::runtime_error("SDL_Init failed");
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        SDL_Log("IMG_Init: %s\n", IMG_GetError());
        throw std::runtime_error("IMG_Init failed");
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

    TextureController::init(renderer);
    // SDL_SetWindowIcon(window, TextureController::iconSurface);

    // display icon at the center
    SDL_Rect iconRect;
    SDL_QueryTexture(TextureController::getTexture("icon"), NULL, NULL, &iconRect.w, &iconRect.h);
    iconRect.x = (WINDOW_WIDTH - iconRect.w) / 2;
    iconRect.y = (WINDOW_HEIGHT - iconRect.h) / 2;
    SDL_RenderCopy(renderer, TextureController::getTexture("icon"), NULL, &iconRect);
    SDL_RenderPresent(renderer);

    map = std::make_shared<Map>(SDL_Rect{width / 2, 0, width / 2, height});
    player = new Player(map->mapRect.w / 2, map->mapRect.h / 2);
    player->init(map);
    map->init(player);

    AudioController::init();
    FontController::LoadFont();

    SDL_Delay(1000);
#ifdef DEBUG
    SDL_Log("DEBUG MODE");
    addDebugMessage("Debug mode activated");
#else
    // wait 1 second
#endif
}

App::~App()
{
    SDL_Log("App Destructor");
    AudioController::close();
    FontController::UnloadFont();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TextureController::closeAll();
    IMG_Quit();
    SDL_Quit();
    delete player;
}