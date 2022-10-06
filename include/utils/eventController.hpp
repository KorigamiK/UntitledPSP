#pragma once

#include <vector>
#include <SDL2/SDL.h>

#include "utils/logger.hpp"
#include "utils/events.hpp"

#define AXIS_MAX 32767
#define AXIS_MIN -32767

class EventController
{
private:
    bool returned_to_horizontal_center;
    bool returned_to_vertical_center;
    static inline constexpr float ANALOG_DEADZONE_MULTIPLIER = 0.5;

    bool rotating = false;

    Event getEventFromKeyboard(SDL_Keycode key);
    Event getReleaseEventFromKeyboard(SDL_Keycode key);
    Event getEventFromControllerButton(Uint32 button);
    Event getReleaseEventFromControllerButton(Uint32 button);
    Event getEventFromControllerAxis(Uint32 axis, Sint16 value);
    std::vector<Event> getEventFromMouseMotion(Sint32 xrel, Sint32 yrel);

    void openGameController(Sint32);
    void closeDisconnectedGameControllers();
    void closeAllGameControllers();

    std::vector<SDL_GameController *> gameControllers;

public:
    ~EventController();

    std::vector<Event> getEvents();
};