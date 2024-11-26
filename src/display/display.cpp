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
  // IMGUI_CHECKVERSION();
  // ImGui::CreateContext();
  // ImGuiIO& io = ImGui::GetIO();
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  // //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

  // io.WantCaptureMouse = true; 
  // io.WantCaptureKeyboard = true;

  // // Setup Dear ImGui style
  // ImGui::StyleColorsDark();
  // //ImGui::StyleColorsLight();

  // // Setup Platform/Renderer backends
  // ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
  // ImGui_ImplSDLRenderer2_Init(renderer);

  // clear the screen
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // Start the Dear ImGui frame
  // ImGui_ImplSDLRenderer2_NewFrame();
  // ImGui_ImplSDL2_NewFrame();
  // ImGui::NewFrame();

  // show the demo window
  bool show_demo = true;
  // ImGui::ShowDemoWindow(&show_demo);

  // Rendering
  // ImGui::Render();
  // ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

  // draw window
  SDL_RenderPresent(renderer);
}

void display::setDebug(bool d)
{
  debug = d;
}

bool display::inputLoop(unsigned char v[16],
                bool gfx[64 * 32],
                unsigned short index,
                unsigned short pc,
                unsigned short stack,
                unsigned short opcode)
{
  // Event loop
  while (SDL_PollEvent(&e) != 0)
  {
    // let ImGui handle the events as well
    // ImGui_ImplSDL2_ProcessEvent(&e);

    switch (e.type)
    {
      case SDL_QUIT:
        exit(0);
        break;

      case SDL_KEYDOWN:
        // testkeycode
        switch (e.key.keysym.sym)
        {
          case SDLK_0:
            debug = !debug;
            break;

          if (debug)
          {
            case SDLK_SPACE:
              return true;
              break;

            case SDLK_g:
              // print graphics memory for debugging
              for (int y = 0; y < 32; y++)
              {
                for (int x = 0; x < 64; x++)
                {
                  int rawIndex = x + (y * 64);
                  if (gfx[rawIndex] != 0)
                  {
                    std::cout << "1";
                  } else {
                    std::cout << "0";
                  }

                  std::cout << " ";
                }
                
                std::cout << std::endl;
              }

              break;
              
            case SDLK_b:
              for (int i = 0; i < 16; i++)
              {
                std::cout << "Register " << i << ": "  << +v[i] << std::endl;
              }

              std::cout << "Index: " << std::hex << +index << std::dec << std::endl;
              std::cout << "Stack: " << std::hex << stack << std::dec << std::endl;
              break;
          }
        }

        break;
    }
  }

  return !debug;
}

void display::drawWindow(bool gfx[64 * 32])
{
  // Start the Dear ImGui frame
  // ImGui_ImplSDLRenderer2_NewFrame();
  // ImGui_ImplSDL2_NewFrame();
  // ImGui::NewFrame();

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
  // bool show_demo = true;
  // ImGui::ShowDemoWindow(&show_demo);

  // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
  // {
  //     static float f = 0.0f;
  //     static int counter = 0;

  //     ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

  //     ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
  //     ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
  //     ImGui::Checkbox("Another Window", &show_another_window);

  //     ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
  //     ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

  //     if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
  //         counter++;
  //     ImGui::SameLine();
  //     ImGui::Text("counter = %d", counter);

  //     ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  //     ImGui::End();
  // }

  // Rendering
  // ImGui::Render();
  // ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

  // draw window
  SDL_RenderPresent(renderer);
}

display::~display() {
  // Quit imgui
  // ImGui_ImplSDLRenderer2_Shutdown();
  // ImGui_ImplSDL2_Shutdown();
  // ImGui::DestroyContext();

  // Quit SDL
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
