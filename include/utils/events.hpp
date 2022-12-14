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
    ROTATE_LEFT_RELEASE,
    ROTATE_RIGHT,
    ROTATE_RIGHT_RELEASE,
    ROTATE_LEFT_MOUSE,
    ROTATE_RIGHT_MOUSE,
    ROTATE_UP,
    ROTATE_DOWN,
    MENU,
    MOUSEMOVE,
    QUIT,
    NEXT,
    PREVIOUS,
    OTHER
};
