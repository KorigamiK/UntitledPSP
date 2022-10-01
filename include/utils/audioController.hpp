#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "utils/sounds.hpp"

#ifdef PLATFORM_PSP
#define SOUND_CONFIRM_PATH "sound.wav"
#else
#define SOUND_CONFIRM_PATH "res/sound.wav"
#endif

namespace AudioController
{
    namespace
    {
        Mix_Chunk *sound_confirm = nullptr;
    }
    void init();
    void play(Sound sound);
    void close();
}