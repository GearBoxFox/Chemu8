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
                       SDL_WINDOWPOS_UNDEFINED, 64 * scale, 32 * scale, SDL_WINDOW_SHOWN);

  if (!window) {
    std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
    exit(-1);
  }

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void display::drawWindow(bool gfx[64 * 32])
{
  // clear window to black
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // set draw color to white
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  std::cout << "Starting to draw window" << std::endl;
  for (int y = 0; y < 32; y++)
  {
    for (int x = 0; x < 64; x++)
    {
      int rawIndex = x + (y * 64);
      if (gfx[rawIndex] != 0)
      {
        r.x = x * scale;
        r.y = y * scale;
        r.h = scale;
        r.w = scale;

        SDL_RenderFillRect(renderer, &r);
      }
    }
  }

  std::cout << "Finished drawing window" << std::endl;

  // draw window
  SDL_RenderPresent(renderer);
}

display::~display() {
  // Quit
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
