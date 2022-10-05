#pragma once

#include <map>
#include <cmath>
#include <string>

#include "game/state/states.hpp"

namespace Constants
{
    inline constexpr float OneDegreeRadian = M_PI / 180;

    extern const std::map<State, const std::string> StateToString;
}