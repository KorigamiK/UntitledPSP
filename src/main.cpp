#ifdef PLATFORM_PSP
#include <pspdebug.h>
#include <pspkernel.h>
#endif

#include <SDL2/SDL.h>
#include <iostream>

#include "app.hpp"

#define FRAME_RENDER_DELAY 25

int main(int argc, char *argv[]) {
  App &app = App::get();

  try {
    app.init();
    Logger::Info("Init Done");
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }

  while (app.running) {
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
