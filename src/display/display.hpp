#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <stdio.h>

class display {
public:
  display();
  ~display();

  void drawWindow(bool gfx[64 * 32], int startX, int startY);

  // Handles getting input from SDL2 + Imgui. Gets the CPU emulator for reading debug information.
  bool inputLoop(
                bool keyboard[16],
                unsigned char v[16],
                bool gfx[64 * 32],
                unsigned short index,
                unsigned short pc,
                unsigned short stack,
                unsigned short opcode
                );

  void setDebug(bool d);

  bool preloadScreen(void (*funcptr)(char*));

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Rect r;

  bool prevgfx[64 * 32];

  bool preloadedScreenDrawn = false;

  // SDL event
  SDL_Event e;
  bool debug = true;
  bool show_demo_window = true;
  bool show_another_window = false;

  int scale = 18;
};
