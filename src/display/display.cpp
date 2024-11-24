#include "display.hpp"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <cstdlib>

display::display() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
    std::exit(-1);
  }

  window =
      SDL_CreateWindow("Chemu8", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 150, 150, SDL_WINDOW_SHOWN);

  if (!window) {
    std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
    exit(-1);
  }

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
}

void display::drawWindow(bool gfx[64 * 32])
{
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  // draw window
  SDL_RenderPresent(renderer);
}

display::~display() {
  // Quit
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
