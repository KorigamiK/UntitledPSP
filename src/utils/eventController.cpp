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
        case SDL_JOYBUTTONDOWN:
            events.push_back(getEventFromJoystickButton(event.jbutton.button));
            break;
        // case SDL_MOUSEBUTTONDOWN:
        //     events.push_back(getEventFromMouseButton(event.button.button));
        //     break;
        // case SDL_MOUSEBUTTONUP:
        //     events.push_back(getEventFromMouseButtonUp(event.button.button));
        //     break;
        case SDL_CONTROLLERBUTTONDOWN:
            events.push_back(getEventFromControllerButton(event.cbutton.button));
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

Event EventController::getEventFromJoystickButton(Uint32 button)
{
    switch (button)
    {
    case 2:
        return Event::CONFIRM;
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
    case SDL_CONTROLLER_BUTTON_START:
        event = Event::MENU;
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

    switch (axis)
    {
    case SDL_CONTROLLER_AXIS_LEFTX:
        if (value > (AXIS_MAX * ANALOG_DEADZONE_MULTIPLIER))
        {
            if (this->returned_to_horizontal_center)
            {
                event = Event::RIGHT;
                this->returned_to_horizontal_center = false;
            }
        }
        else if (value < (AXIS_MIN * ANALOG_DEADZONE_MULTIPLIER))
        {
            if (this->returned_to_horizontal_center)
            {
                event = Event::LEFT;
                this->returned_to_horizontal_center = false;
            }
        }
        else
        {
            this->returned_to_horizontal_center = true;
        }
        break;
    case SDL_CONTROLLER_AXIS_LEFTY:
        if (value > (AXIS_MAX * ANALOG_DEADZONE_MULTIPLIER))
        {
            if (this->returned_to_vertical_center)
            {
                event = Event::DOWN;
                this->returned_to_vertical_center = false;
            }
        }
        else if (value < (AXIS_MIN * ANALOG_DEADZONE_MULTIPLIER))
        {
            if (this->returned_to_vertical_center)
            {
                event = Event::UP;
                this->returned_to_vertical_center = false;
            }
        }
        else
        {
            this->returned_to_vertical_center = true;
        }
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
        SDL_Log("Adding controller: %s", SDL_GameControllerName(controller));
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
            SDL_Log("Removing controller: %s", SDL_GameControllerName(controller));
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
        SDL_Log("Removing controller: %s", SDL_GameControllerName(gameControllers[i]));
        SDL_GameControllerClose(gameControllers[i]);
        gameControllers[i] = NULL;
    }
}

EventController::~EventController()
{
    SDL_Log("EventController Destructor");
    closeAllGameControllers();
}