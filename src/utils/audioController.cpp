
#include "utils/audioController.hpp"

void AudioController::init()
{
    // Load the WAV
    // The specs, length and buffer of our wav are filled
    if (SDL_LoadWAV(MUS_PATH, &wav_spec, &wav_buffer, &wav_length) == NULL)
    {
        SDL_Log("SDL_LoadWAV: %s\n", SDL_GetError());
        throw std::runtime_error("SDL_LoadWAV failed");
    }
    // Set the callback function
    wav_spec.callback = audioCallback;
    wav_spec.userdata = NULL;

    audio_pos = wav_buffer; // copy sound buffer
    audio_len = wav_length; // copy file length

    // Open the audio device
    if (SDL_OpenAudio(&wav_spec, NULL) < 0)
    {
        SDL_Log("SDL_OpenAudio: %s\n", SDL_GetError());
        throw std::runtime_error("SDL_OpenAudio failed");
    }

    // Start playing
    SDL_PauseAudio(0);
}

void AudioController::audioCallback(void *userdata, Uint8 *stream, int len)
{
    if (audio_len == 0)
        return;

    len = (len > audio_len ? audio_len : len);
    SDL_memcpy(stream, audio_pos, len); // simply copy from one buffer into the other
    // SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another

    audio_pos += len;
    audio_len -= len;
}

void AudioController::close()
{
    SDL_CloseAudio();
    SDL_FreeWAV(wav_buffer);
}