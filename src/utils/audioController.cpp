#include "utils/audioController.hpp"

void AudioController::init()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
        throw std::runtime_error("SDL_mixer could not initialize! SDL_mixer Error: " + std::string(Mix_GetError()));
    sound_confirm = Mix_LoadWAV(SOUND_CONFIRM_PATH);
    if (sound_confirm == NULL)
        throw std::runtime_error("Failed to load sound_confirm");
}

void AudioController::play(Sound sound)
{
    switch (sound)
    {
    case Sound::CONFIRM:
        Mix_PlayChannel(-1, sound_confirm, SDL_FALSE);
        break;
    }
}

void AudioController::close()
{
    Mix_FreeChunk(sound_confirm);
    Mix_CloseAudio();
    Mix_Quit();
}