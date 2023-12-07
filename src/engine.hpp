#pragma once

#include <string>

#include "SDL2/SDL.h"

#include "player.hpp"

class Engine {
  public:
    Engine();

    void init(std::string &path);

    void update();
    void clean();

  private:
    Player *player = nullptr;

    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Event event;
};