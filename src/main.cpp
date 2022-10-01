#ifdef PLATFORM_PSP
#include <pspkernel.h>
#include <pspdebug.h>
#endif

#include <iostream>
#include <SDL2/SDL.h>

#include "app.hpp"

#define FRAME_RENDER_DELAY 25

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

  while (app.running)
  {
    app.handleEvents();

    app.draw();

    app.rerender();

    SDL_Delay(FRAME_RENDER_DELAY);
  }

#ifdef PLATFORM_PSP
  sceKernelExitGame();
#endif

  return 0;
}
