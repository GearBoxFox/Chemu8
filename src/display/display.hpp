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
  bool inputLoop(unsigned char v[16],
                bool gfx[64 * 32],
                unsigned short index,
                unsigned short pc,
                unsigned short stack,
                unsigned short opcode
                );

  void setDebug(bool d);

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Rect r;

  // SDL event
  SDL_Event e;
  bool debug = true;
  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  int scale = 18;
};
