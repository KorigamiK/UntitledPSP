#ifdef PLATFORM_PSP
#include <pspkernel.h>
#include <pspdebug.h>
/* Define the module info section */
// PSP_MODULE_INFO("SDL2", 0, 1, 1);

/* Define the main thread's attribute value (optional) */
// PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
#endif

#include <iostream>
#include <SDL2/SDL.h>

#include "app.hpp"

#ifdef PLATFORM_PSP
#define MUS_PATH "sound.wav"
#else
#define MUS_PATH "/home/korigamik/Dev/projects/PSP/game/untitled/res/sound.wav"
#endif

#include "game/player.hpp"

#define FRAME_RENDER_DELAY 25

static Uint8 *audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play

void my_audio_callback(void *userdata, Uint8 *stream, int len)
{
  if (audio_len == 0)
    return;

  len = (len > audio_len ? audio_len : len);
  SDL_memcpy(stream, audio_pos, len); // simply copy from one buffer into the other
  // SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another

  audio_pos += len;
  audio_len -= len;
}

int main(int argc, char *argv[])
{
  App &app = App::get();
  try
  {
    app.init();
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }

  bool done = false;

  SDL_Event event;
  // local variables
  static Uint32 wav_length;      // length of our sample
  static Uint8 *wav_buffer;      // buffer containing our audio file
  static SDL_AudioSpec wav_spec; // the specs of our piece of music

  /* Load the WAV */
  // the specs, length and buffer of our wav are filled
  if (SDL_LoadWAV(MUS_PATH, &wav_spec, &wav_buffer, &wav_length) == NULL)
  {
    SDL_Log("SDL_LoadWAV failed: %s\n", SDL_GetError());
    return -1;
  }

  // set the callback function
  wav_spec.callback = my_audio_callback;
  wav_spec.userdata = NULL;
  audio_pos = wav_buffer; // copy sound buffer
  audio_len = wav_length; // copy file length

  /* Open the audio device */
  if (SDL_OpenAudio(&wav_spec, NULL) < 0)
  {
    SDL_Log("Couldn't open audio: %s\n", SDL_GetError());
    return -1;
  }

  // Start playing
  SDL_PauseAudio(0);

  Player player(app.width / 2, app.height / 2);

  while (!done)
  {
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      // close window if user clicks the X
      case SDL_QUIT:
        done = 1;
        break;

      case SDL_JOYAXISMOTION:
        SDL_Log("Joystick %d axis %d value: %d\n",
                event.jaxis.which,
                event.jaxis.axis, event.jaxis.value);
        break;

      case SDL_JOYBUTTONDOWN:
        SDL_Log("Joystick %d button %d down\n",
                event.jbutton.which, event.jbutton.button);
        // seek for joystick #0
        if (event.jbutton.which == 0)
        {
          if (event.jbutton.button == 2)
          {
            audio_pos = wav_buffer; // copy sound buffer
            audio_len = wav_length;
          }
          else if (event.jbutton.button == 11)
          {
            // (Start) button down
            done = 1;
          }
        }
        break;

      case SDL_KEYDOWN:
        player.update(event);
        break;
      default:
        break;
      }
    }

    app.draw();

    app.drawWalls();

    player.draw(app.renderer);

    app.rerender();

    SDL_Delay(FRAME_RENDER_DELAY);
  }

  // shut everything down
  SDL_CloseAudio();
  SDL_FreeWAV(wav_buffer);

#ifdef PLATFORM_PSP
  sceKernelExitGame();
#endif

  return 0;
}
