#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#ifdef PLATFORM_PSP
#define MUS_PATH "sound.wav"
#else
#define MUS_PATH "res/sound.wav"
#endif

namespace AudioController
{
    static Uint8 *audio_pos; // global pointer to the audio buffer to be played
    static Uint32 audio_len; // remaining length of the sample we have to play

    static Uint32 wav_length;      // length of our sample
    static Uint8 *wav_buffer;      // buffer containing our audio file
    static SDL_AudioSpec wav_spec; // the specs of our piece of music

    static void audioCallback(void *userdata, Uint8 *stream, int len);
    void init();
    void close();
}