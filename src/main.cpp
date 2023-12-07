#include <iostream>
#include <vector>
#include <unistd.h>

extern "C" {
  #include "libswscale/swscale.h"
}

#include "SDL2/SDL.h"

#include "engine.hpp"

#define DELAY 1000 / 30

int main(int argc, char ** argv) {
  uint32_t tick;

  Engine engine = Engine();

  const std::vector<std::string> args(argv + 1, argv + argc);

  std::string path = "";

  for (auto i = args.begin(); i != args.end(); ++i) {
    if (*i == "--path") {
      path = *(i + 1);
    }
  }

  if (!access(path.c_str(), 0) == 0) {
    std::cout << "File not found!" << std::endl;
    return 1;
  }

  engine.init(path);

  SDL_Event event;

  bool isRunning = true;

  while (isRunning) {
    tick = SDL_GetTicks();

    SDL_PollEvent(&event);

    switch (event.type) {
      case SDL_QUIT:
        isRunning = false;
        break;
      default:
        break;
    }

    engine.update();

    if (DELAY > SDL_GetTicks() - tick) {
      SDL_Delay(DELAY - (SDL_GetTicks() - tick));
    }
  }

  engine.clean();

  return 0;
}