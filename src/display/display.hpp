#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>

class display {
public:
  display();
  ~display();

  void drawWindow(unsigned char gfx[64 * 32]);

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
};
