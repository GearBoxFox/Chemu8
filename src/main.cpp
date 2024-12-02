#include "./emu/cpu.hpp"
#include "./display/display.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

// The Chemu8 Emulator
cpu chip8;
display display;

FILE *rom;

bool modern = false;

bool keyboardState[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool *keyPtr = keyboardState;
bool preloadedRom = false;

void loadRom(char *name)
{
  // read the file
  rom = fopen(name, "rb");
  std::cout << "Loading ROM File" << std::endl;

  // make sure the rom file actually opened
  if (rom == NULL) {
    std::cout << "Failed to open ROM file." << std::endl;
    exit(-1);
  }

  // obtain file size:
  fseek(rom, 0, SEEK_END);
  long lSize = ftell(rom);
  rewind(rom);

  char *buffer = (char *)malloc(sizeof(char) * lSize);
  if (buffer == NULL) {
    std::cout << "Error allocating memory for ROM file." << std::endl;
    exit(-1);
  }

  // 0x00-0x200 is initially reserved for the emulator and fonts
  if (lSize > 0xDFF) {
    std::cout << "ROM File too large" << std::endl;
  }

  // read the actual file into the buffer
  size_t result = fread(buffer, 1, lSize, rom);
  if (result != lSize) {
    std::cout << "Failed reading the file into buffer" << std::endl;
    exit(-1);
  }

  // pass the file into our CPU emulator
  chip8.loadRomFile(buffer, result);

  // close the rom file
  fclose(rom);
  free(buffer);
}

static void  mainloop()
{
  if (!preloadedRom)
  {
    preloadedRom = display.preloadScreen(loadRom);
    // std::cout << "ROM Loaded?" << preloadedRom << std::endl;
  } else {
    // std::cout << "Running CPU Cycle" << std::endl;
    bool runLoop = false;

    // timing for frame limiting
    Uint64 start = SDL_GetPerformanceCounter();

    for (int i = 0; i < 5; i++)
    {
      
      // let the cpu run faster
      runLoop = display.inputLoop(
        keyPtr,
        chip8.v,
        chip8.gfx,
        chip8.index,
        chip8.pc,
        chip8.stackPointer,
        chip8.opcode);

      // std::cout << "Current keyboard state: " << std::endl;
      // for (int i = 0; i < 16; i++)
      // {
      //     std::cout << std::hex << i << std::dec << " " << keyboardState[i] << std::endl;
      // }

      if (runLoop)
      {
        // run CPU clock cycle
        if (chip8.executeInstructionLoop(keyPtr) != 0)
        {
          #ifdef __EMSCRIPTEN__
          emscripten_cancel_main_loop();  /* this should "kill" the app. */
          #else
          exit(-1);
          #endif
        }
      }
    }

    if (runLoop && chip8.drawFlag)
    {
      display.drawWindow(chip8.gfx, chip8.startX, chip8.startY);
    }

    Uint64 end = SDL_GetPerformanceCounter();

    float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

    // Cap to 1/120th of a second, roughly the frame rate of the chip-8
    // 1.426f
    if ((8.0f - elapsedMS) > 0)
    {
      SDL_Delay(floor(8.0f - elapsedMS));
      // timer += 8.0f;
    } else {
      // timer += elapsedMS;
    }

    chip8.updateTimers();

    // // // Timers only update on a 60Hrz frequency
    // // std::cout << "Elapsed Timer" << elapsedMS << std::endl;
    // // std::cout << "Timer: " << timer << std::endl;
    // if (timer > 16.666f && runLoop)
    // {
    //   timer = 0.0;
    //   chip8.updateTimers();
    // }
  }
}

// You must include the command line parameters for your main function to be
// recognized by SDL
int main(int argc, char **args) {
  float timer = 0.0;

  std::cout << args[0] << " " << args[1] << " " << args[2] << " " << args[3] << std::endl;

  // the first argument should be the ROM file to load
  if (argc < 2) {
    preloadedRom = false;
  } else {
    std::cout << "Starting Emulator" << std::endl;
    preloadedRom = true;
    
    loadRom(args[1]);
  }

  bool debug = (args[2] != NULL);
  display.setDebug(false);

  modern = (args[3] != NULL);
  std::cout << modern << std::endl;

  #ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(mainloop, 0, 1);
  #else
  while (true) {
    mainloop();
  }
  #endif

  // End the program, but should never get here
  return 0;
}
