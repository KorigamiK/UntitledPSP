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
