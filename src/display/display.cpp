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

  // Create the SDL Renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
    exit(-1);
  }

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsLight();

  // Setup Platform/Renderer backends
  ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer2_Init(renderer);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

bool display::inputLoop(char** keyboardState, 
                unsigned char v[16],
                unsigned char gfx[64 * 32],
                unsigned short index,
                unsigned short pc,
                unsigned short stack,
                unsigned short opcode
                )
{
  
}

void display::drawWindow(bool gfx[64 * 32])
{
  // Start the Dear ImGui frame
  ImGui_ImplSDLRenderer2_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();

  // clear window to black
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // set draw color to white
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

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

  // show the demo window
  bool show_demo = true;
  ImGui::ShowDemoWindow(&show_demo);

  // Rendering
  ImGui::Render();
  ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

  // draw window
  SDL_RenderPresent(renderer);
}

display::~display() {
  // Quit imgui
  ImGui_ImplSDLRenderer2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  // Quit SDL
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
