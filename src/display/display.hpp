#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>

#include "./imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_sdlrenderer2.h"

class display {
public:
  display();
  ~display();

  void drawWindow(bool gfx[64 * 32]);

  // Handles getting input from SDL2 + Imgui. Gets the CPU emulator for reading debug information.
  bool inputLoop(char** keyboardState, 
                unsigned char v[16],
                unsigned char gfx[64 * 32],
                unsigned short index,
                unsigned short pc,
                unsigned short stack,
                unsigned short opcode,
                );

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Rect r;

  int scale = 18;
};
