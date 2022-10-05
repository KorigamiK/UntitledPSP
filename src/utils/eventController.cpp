#include "utils/eventController.hpp"

std::vector<Event> EventController::getEvents()
{
    std::vector<Event> events;
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            events.push_back(Event::QUIT);
            break;
        case SDL_KEYDOWN:
            events.push_back(getEventFromKeyboard(event.key.keysym.sym));
            break;
        // case SDL_MOUSEBUTTONDOWN:
        //     events.push_back(getEventFromMouseButton(event.button.button));
        //     break;
        // case SDL_MOUSEBUTTONUP:
        //     events.push_back(getEventFromMouseButtonUp(event.button.button));
        //     break;
        case SDL_KEYUP:
            events.push_back(getReleaseEventFromKeyboard(event.key.keysym.sym));
            break;
        case SDL_CONTROLLERBUTTONDOWN:
            events.push_back(getEventFromControllerButton(event.cbutton.button));
            break;
        case SDL_CONTROLLERBUTTONUP:
            events.push_back(getReleaseEventFromControllerButton(event.cbutton.button));
            break;
        case SDL_CONTROLLERAXISMOTION:
            events.push_back(getEventFromControllerAxis(event.caxis.axis, event.caxis.value));
            break;
        case SDL_CONTROLLERDEVICEADDED:
            openGameController(event.cdevice.which);
            break;
        case SDL_CONTROLLERDEVICEREMOVED:
            closeDisconnectedGameControllers();
            break;
        }
    }
    return events;
}

Event EventController::getReleaseEventFromKeyboard(SDL_Keycode key)
{
    switch (key)
    {
    case SDLK_LEFT:
    case SDLK_a:
        return Event::LEFT_RELEASE;
    case SDLK_RIGHT:
    case SDLK_d:
        return Event::RIGHT_RELEASE;
    case SDLK_UP:
    case SDLK_w:
        return Event::UP_RELEASE;
    case SDLK_DOWN:
    case SDLK_s:
        return Event::DOWN_RELEASE;
    default:
        return Event::OTHER;
    }
}

Event EventController::getReleaseEventFromControllerButton(Uint32 button)
{
    switch (button)
    {
    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
        return Event::LEFT_RELEASE;
    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
        return Event::RIGHT_RELEASE;
    case SDL_CONTROLLER_BUTTON_DPAD_UP:
        return Event::UP_RELEASE;
    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
        return Event::DOWN_RELEASE;
    default:
        return Event::OTHER;
    }
}

Event EventController::getEventFromKeyboard(SDL_Keycode key)
{
    Event event;

    switch (key)
    {
    case SDLK_w:
    case SDLK_UP:
        event = Event::UP;
        break;
    case SDLK_s:
    case SDLK_DOWN:
        event = Event::DOWN;
        break;
    case SDLK_a:
    case SDLK_LEFT:
        event = Event::LEFT;
        break;
    case SDLK_d:
    case SDLK_RIGHT:
        event = Event::RIGHT;
        break;
    case SDLK_q:
        event = Event::ROTATE_LEFT;
        break;
    case SDLK_e:
        event = Event::ROTATE_RIGHT;
        break;
    case SDLK_z:
        event = Event::ROTATE_UP;
        break;
    case SDLK_x:
        event = Event::ROTATE_DOWN;
        break;
    case SDLK_RETURN:
    case SDLK_SPACE:
        event = Event::CONFIRM;
        break;
    case SDLK_BACKSPACE:
        event = Event::CANCEL;
        break;
    case SDLK_PAGEUP:
        event = Event::NEXT;
        break;
    case SDLK_PAGEDOWN:
        event = Event::PREVIOUS;
        break;
    case SDLK_ESCAPE:
        event = Event::MENU;
        break;
    default:
        event = Event::OTHER;
        break;
    }

    return event;
}

Event EventController::getEventFromControllerButton(Uint32 button)
{
    Event event;

    switch (button)
    {
    case SDL_CONTROLLER_BUTTON_DPAD_UP:
        event = Event::UP;
        break;
    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
        event = Event::DOWN;
        break;
    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
        event = Event::LEFT;
        break;
    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
        event = Event::RIGHT;
        break;
    case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
        event = Event::ROTATE_LEFT;
        break;
    case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
        event = Event::ROTATE_RIGHT;
        break;
    case SDL_CONTROLLER_BUTTON_A:
        event = Event::CONFIRM;
        break;
    case SDL_CONTROLLER_BUTTON_B:
        event = Event::CANCEL;
        break;
    case SDL_CONTROLLER_BUTTON_X:
        event = Event::ROTATE_DOWN;
        break;
    case SDL_CONTROLLER_BUTTON_Y:
        event = Event::ROTATE_UP;
        break;
    case SDL_CONTROLLER_BUTTON_START:
        // event = Event::MENU;
        event = Event::QUIT;
        break;
    default:
        event = Event::OTHER;
        break;
    }

    return event;
}

Event EventController::getEventFromControllerAxis(Uint32 axis, Sint16 value)
{
    Event event = Event::NONE;

    static const int deadZone = 8000;

    switch (axis)
    {
    case SDL_CONTROLLER_AXIS_LEFTX:
        if (value < -deadZone)
            event = Event::ROTATE_LEFT;
        else if (value > deadZone)
            event = Event::ROTATE_RIGHT;
        break;
    case SDL_CONTROLLER_AXIS_LEFTY:
        if (value < -deadZone)
            event = Event::ROTATE_UP;
        else if (value > deadZone)
            event = Event::ROTATE_DOWN;
        break;
    case SDL_CONTROLLER_AXIS_RIGHTY:
        if (value < -deadZone)
            event = Event::LEFT;
        else if (value > deadZone)
            event = Event::RIGHT;
        break;
    case SDL_CONTROLLER_AXIS_RIGHTX:
        if (value < -deadZone)
            event = Event::UP;
        else if (value > deadZone)
            event = Event::DOWN;
        break;
    default:
        break;
    }

    return event;
}

void EventController::openGameController(Sint32 index)
{
    if (SDL_IsGameController(index))
    {
        SDL_GameController *controller = SDL_GameControllerOpen(index);
        Logger::Debug("Adding controller: %s", SDL_GameControllerName(controller));
        gameControllers.push_back(controller);
    }
}

void EventController::closeDisconnectedGameControllers()
{
    std::vector<SDL_GameController *> currentControllers;
    for (SDL_GameController *controller : gameControllers)
    {
        if (!SDL_GameControllerGetAttached(controller))
        {
            Logger::Debug("Removing controller: %s", SDL_GameControllerName(controller));
            SDL_GameControllerClose(controller);
            controller = NULL;
        }
        else
            currentControllers.push_back(controller);
    }
    gameControllers = currentControllers;
}

void EventController::closeAllGameControllers()
{
    for (int i = 0; i < int(gameControllers.size()); i++)
    {
        Logger::Debug("Removing controller: %s", SDL_GameControllerName(gameControllers[i]));
        SDL_GameControllerClose(gameControllers[i]);
        gameControllers[i] = NULL;
    }
}

EventController::~EventController()
{
    Logger::Info("EventController Destructor");
    closeAllGameControllers();
}