#include "app.hpp"

App App::_instance;

void App::draw()
{
    SDL_SetRenderDrawColor(renderer, 41, 41, 41, 255);
    SDL_RenderClear(renderer);

    SDL_GetWindowSize(window, &width, &height);

#ifdef VERBOSE
    renderDebugMessages();
#endif

    map->setMapRect(std::move(SDL_Rect{width / 2, 0, width / 2, height}), 10);
    playerView->setViewRect(std::move(SDL_Rect{0, 0, width / 2, height}));

    player->draw(renderer);
    map->draw(renderer);
    playerView->draw(renderer);
}

void App::renderDebugMessages()
{
    if (debugChanged)
    {
        if (debugTexture != nullptr)
            SDL_DestroyTexture(debugTexture);
        debugChanged = false;
        std::string debugText = "";
        for (auto &message : debugMessages)
        {
            debugText += message;
            debugText += "\n";
        }
        debugTexture = FontController::getTexture(renderer, debugText.c_str(), {255, 255, 255});
    }

    SDL_Rect textRect;
    SDL_QueryTexture(debugTexture, NULL, NULL, &textRect.w, &textRect.h);
    textRect.x = 0;
    textRect.y = height - textRect.h;
    SDL_RenderCopy(renderer, debugTexture, NULL, &textRect);
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
        Logger::Debug("Event: %d", event);
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
    Logger::Info("App::init");

#ifdef VERBOSE
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE);
#endif

    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER | SDL_INIT_TIMER) < 0)
    {
        Logger::Error("SDL_Init: %s\n", SDL_GetError());
        throw std::runtime_error("SDL_Init failed");
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        Logger::Error("IMG_Init: %s\n", IMG_GetError());
        throw std::runtime_error("IMG_Init failed");
    }

    // create an SDL window (pspgl enabled)
    window = SDL_CreateWindow("Untitled", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (!window)
    {
        Logger::Error("SDL_CreateWindow: %s\n", SDL_GetError());
        SDL_Quit();
        throw std::runtime_error("SDL_CreateWindow failed");
    }

    // create a renderer (OpenGL ES2)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        Logger::Error("SDL_CreateRenderer: %s\n", SDL_GetError());
        SDL_Quit();
        throw std::runtime_error("SDL_CreateRenderer failed");
    }

    TextureController::init(renderer);
    SDL_SetWindowIcon(window, TextureController::iconSurface);

    SDL_Rect iconRect;
    SDL_Texture *iconTexture = TextureController::load(renderer, "res/glitch.png");
    SDL_QueryTexture(iconTexture, NULL, NULL, &iconRect.w, &iconRect.h);
    iconRect.x = (WINDOW_WIDTH - iconRect.w) / 2;
    iconRect.y = (WINDOW_HEIGHT - iconRect.h) / 2;
    SDL_RenderCopy(renderer, iconTexture, NULL, &iconRect);
    SDL_RenderPresent(renderer);

    map = std::make_shared<Map>(SDL_Rect{width / 2, 0, width / 2, height});
    player = new Player(map->mapRect.w / 2, map->mapRect.h / 2);
    player->init(map);
    map->init(player);
    playerView = std::make_unique<PlayerView>(player, SDL_Rect{0, 0, width / 2, height});

    AudioController::init();
    FontController::LoadFont();

    Logger::Info("App::init done");

#ifdef VERBOSE
    Logger::Info("DEBUG MODE");
    addDebugMessage("Debug mode");
#else
    SDL_Delay(1000);
#endif
}

App::~App()
{
    Logger::Info("App Destructor");
    AudioController::close();
    FontController::UnloadFont();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TextureController::closeAll();
    IMG_Quit();
    SDL_Quit();
    delete player;
}