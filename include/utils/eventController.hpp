#pragma once

#include <vector>
#include <SDL2/SDL.h>

#include "utils/events.hpp"

#define AXIS_MAX 32767
#define AXIS_MIN -32767

class EventController
{
private:
    bool returned_to_horizontal_center;
    bool returned_to_vertical_center;
    static inline constexpr float ANALOG_DEADZONE_MULTIPLIER = 0.5;

    Event getEventFromKeyboard(SDL_Keycode key);
    // Event getEventFromMouseButton(Uint8 button);
    // Event getEventFromMouseButtonUp(Uint8 button);
    Event getEventFromControllerButton(Uint32 button);
    Event getEventFromControllerAxis(Uint32 axis, Sint16 value);

    void openGameController(Sint32);
    void closeDisconnectedGameControllers();
    void closeAllGameControllers();

    std::vector<SDL_GameController *> gameControllers;

public:
    ~EventController();

    std::vector<Event> getEvents();
};