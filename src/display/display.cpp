#include "display.hpp"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <cstdlib>

display::display() {
  if (SDL_Init(SDL_INIT_EVERYTHING & ~(SDL_INIT_TIMER | SDL_INIT_HAPTIC)) < 0) {
    std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
    std::exit(-1);
  }

  if ( TTF_Init() < 0 ) {
    std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
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

bool display::inputLoop(
                bool keyboard[16],
                unsigned char v[16],
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
          case SDLK_1:
            keyboard[0x1] = true;
            break;

          case SDLK_2:
            keyboard[0x2] = true;
            break;

          case SDLK_3:
            keyboard[0x3] = true;
            break;

          case SDLK_4:
            keyboard[0xC] = true;
            break;

          case SDLK_q:
            keyboard[0x4] = true;
            break;

          case SDLK_w:
            keyboard[0x5] = true;
            break;
          
          case SDLK_e:
            keyboard[0x6] = true;
            break;

          case SDLK_r:
            keyboard[0xD] = true;
            break;

          case SDLK_a:
            keyboard[0x7] = true;
            break;

          case SDLK_s:
            keyboard[0x8] = true;
            break;

          case SDLK_d:
            keyboard[0x9] = true;
            break;

          case SDLK_f:
            keyboard[0xE] = true;
            break;

          case SDLK_z:
            keyboard[0xA] = true;
            break;

          case SDLK_x:
            keyboard[0x0] = true;
            break;

          case SDLK_c:
            keyboard[0xB] = true;
            break;

          case SDLK_v:
            keyboard[0xF] = true;
            break;

          // debugging keybinds
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

      case SDL_KEYUP:
        switch (e.key.keysym.sym)
        {
          case SDLK_1:
            keyboard[0x1] = false;
            break;

          case SDLK_2:
            keyboard[0x2] = false;
            break;

          case SDLK_3:
            keyboard[0x3] = false;
            break;

          case SDLK_4:
            keyboard[0xC] = false;
            break;

          case SDLK_q:
            keyboard[0x4] = false;
            break;

          case SDLK_w:
            keyboard[0x5] = false;
            break;
          
          case SDLK_e:
            keyboard[0x6] = false;
            break;

          case SDLK_r:
            keyboard[0xD] = false;
            break;

          case SDLK_a:
            keyboard[0x7] = false;
            break;

          case SDLK_s:
            keyboard[0x8] = false;
            break;

          case SDLK_d:
            keyboard[0x9] = false;
            break;

          case SDLK_f:
            keyboard[0xE] = false;
            break;

          case SDLK_z:
            keyboard[0xA] = false;
            break;

          case SDLK_x:
            keyboard[0x0] = false;
            break;

          case SDLK_c:
            keyboard[0xB] = false;
            break;

          case SDLK_v:
            keyboard[0xF] = false;
            break;
        }
        break;
    }
  }

  return !debug;
}

void display::drawWindow(bool gfx[64 * 32], int startX, int startY)
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
      if (gfx[rawIndex])
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

bool display::preloadScreen(void (*funcptr)(char*))
{
  // draw input screen
  if (!preloadedScreenDrawn)
  {
    TTF_Font* font;
    font = TTF_OpenFont("./assets/UbuntuNerdFont-Medium.ttf", 24);
    if (!font) {
      std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
    }

    SDL_Surface *text;
    SDL_Color color = {255, 255, 255};

    const char *message = "Press a key to select a ROM File: \n \n 1. IBM Logo\n 2. Octojam 2nd Title Screen\n 3. Pong\n 4. Mini Lights Out\n 5. 15 Puzzle\n 6. Connect 4\n 7. Tic Tac Toe";

    text = TTF_RenderText_Blended_Wrapped(font, message, color, 0);
    if (!text) {
      std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
    }

    SDL_Texture* text_texture;

    text_texture = SDL_CreateTextureFromSurface(renderer, text);

    SDL_Rect dest = { 0, 0, text->w, text->h };

    SDL_RenderCopy(renderer, text_texture, NULL, &dest);
    SDL_RenderPresent(renderer);

    preloadedScreenDrawn = true;
  }

  SDL_Event e;
  while (SDL_PollEvent(&e) != 0)
  {
    switch (e.type)
    {
      case SDL_QUIT:
        exit(0);
        break;

      case SDL_KEYDOWN:
        switch (e.key.keysym.sym)
        {
        case SDLK_1:
          funcptr("assets/roms/IBMLogo.ch8");
          return true;
          break;

        case SDLK_2:
          funcptr("assets/roms/octojam2title.ch8");
          return true;
          break;

        case SDLK_3:
          funcptr("assets/roms/pong.ch8");
          return true;
          break;

        case SDLK_4:
          funcptr("assets/roms/mini-lights-out.ch8");
          return true;
          break;

        case SDLK_5:
          funcptr("assets/roms/15puzzle.ch8");
          return true;
          break;

        case SDLK_6:
          funcptr("assets/roms/connect4.ch8");
          return true;
          break;

        case SDLK_7:
          funcptr("assets/roms/tictac.ch8");
          return true;
          break;
        
        default:
          break;
        }
      
      default:
        break;
    }
  }

  return false;
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
