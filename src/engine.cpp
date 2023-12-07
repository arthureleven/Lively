#include <windows.h>

#include "SDL2/SDL_image.h"

#include "engine.hpp"

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
  HWND homeView = FindWindowEx(hwnd, nullptr, "SHELLDLL_DefView", nullptr);
  HWND *ret = (HWND *) lParam;

  if (homeView) {
    *ret = FindWindowEx(NULL, hwnd, "WorkerW", nullptr);
  }

  return true;
}

HWND getDesktopW() {
  HWND progman = FindWindow("ProgMan", nullptr);

  SendMessageTimeout(progman, 0x052C, 0, 0, SMTO_NORMAL, 1000, nullptr);

  HWND wpHwnd = nullptr;

  EnumWindows(EnumWindowsProc, (LPARAM) &wpHwnd);

  return wpHwnd;
}

Engine::Engine() {}

void Engine::init(std::string &path) {
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    window = SDL_CreateWindowFrom((void *) getDesktopW());
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer) {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }
  }

  player = new Player(renderer, path);
}

void Engine::update() {
  SDL_RenderClear(renderer);

  player->update();

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderPresent(renderer);
}

void Engine::clean() {
  delete player;

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}