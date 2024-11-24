#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>

class display {
public:
  display();
  ~display();

  void drawWindow(bool gfx[64 * 32]);

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Rect r;

  int scale = 18;
};
