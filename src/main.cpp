#ifdef PLATFORM_PSP
#include <pspdebug.h>
#include <pspkernel.h>
#endif

#include <SDL2/SDL.h>
#include <iostream>

#include "app.hpp"

int main(int argc, char *argv[])
{
  App &app = App::get();

  try
  {
    app.init();
    Logger::Info("Init Done");
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }

  Uint32 prevTime = 0, currentTime = SDL_GetTicks();
  double dt = 0;

  while (app.running)
  {
    prevTime = currentTime;
    currentTime = SDL_GetTicks();

    dt = currentTime - prevTime;

    if (dt > 0.15f)
      dt = 0.15f;

    app.handleEvents();

    app.draw(dt * 20);

    app.rerender();
  }

#ifdef PLATFORM_PSP
  sceKernelExitGame();
#endif

  return 0;
}
