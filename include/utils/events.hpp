#pragma once

enum class Event
{
    NONE = 0,
    CONFIRM,
    CANCEL,
    LEFT,
    LEFT_RELEASE,
    RIGHT,
    RIGHT_RELEASE,
    UP,
    UP_RELEASE,
    DOWN,
    DOWN_RELEASE,
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
