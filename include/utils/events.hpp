#pragma once

enum class Event
{
    NONE = 0,
    CONFIRM,
    CANCEL,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    ROTATE_LEFT,
    ROTATE_RIGHT,
    ROTATE_UP,
    ROTATE_DOWN,
    MENU,
    MOUSEMOVE,
    QUIT,
    NEXT,
    PREVIOUS,
    OTHER
};
