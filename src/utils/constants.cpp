#include "utils/constants.hpp"

const std::map<State, const std::string> Constants::StateToString = {
    {State::Game, "Game"},
    {State::Menu, "Menu"},
    {State::NotImplemented, "Not Implemented"},
    {State::Exit, "Exit"},
};