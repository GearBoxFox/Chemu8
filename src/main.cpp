#include "./emu/cpu.hpp"
#include "./display/display.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

static void  mainloop(
    cpu chip, 
    display dis,
    bool keyboard[16],
    bool *keyPtr)
{
  bool runLoop = false;

  // timing for frame limiting
  Uint64 start = SDL_GetPerformanceCounter();

  for (int i = 0; i < 5; i++)
  {
    
    // let the cpu run faster
    runLoop = dis.inputLoop(
      keyPtr,
      chip.v,
      chip.gfx,
      chip.index,
      chip.pc,
      chip.stackPointer,
      chip.opcode);

    // std::cout << "Current keyboard state: " << std::endl;
    // for (int i = 0; i < 16; i++)
    // {
    //     std::cout << std::hex << i << std::dec << " " << keyboardState[i] << std::endl;
    // }

    if (runLoop)
    {
      // run CPU clock cycle
      if (chip.executeInstructionLoop(keyPtr) != 0)
      {
        exit(-1);
      }
    }
  }

  if (runLoop && chip.drawFlag)
  {
    dis.drawWindow(chip.gfx, chip.startX, chip.startY);
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

  chip.updateTimers();

  // // // Timers only update on a 60Hrz frequency
  // // std::cout << "Elapsed Timer" << elapsedMS << std::endl;
  // // std::cout << "Timer: " << timer << std::endl;
  // if (timer > 16.666f && runLoop)
  // {
  //   timer = 0.0;
  //   chip8.updateTimers();
  // }
}

// You must include the command line parameters for your main function to be
// recognized by SDL
int main(int argc, char **args) {
  // The Chemu8 Emulator
  cpu chip8;
  display display;

  float timer = 0.0;

  // the first argument should be the ROM file to load
  if (argc < 2) {
    std::cout << "Missing ROM file to play." << std::endl;
    return -1;
  } else {
    std::cout << "Starting Emulator" << std::endl;

    // read the file
    FILE *rom = fopen(args[1], "rb");

    // make sure the rom file actually opened
    if (rom == NULL) {
      std::cout << "Failed to open ROM file." << std::endl;
      return -1;
    }

    // obtain file size:
    fseek(rom, 0, SEEK_END);
    long lSize = ftell(rom);
    rewind(rom);

    char *buffer = (char *)malloc(sizeof(char) * lSize);
    if (buffer == NULL) {
      std::cout << "Error allocating memory for ROM file." << std::endl;
      return -2;
    }

    // 0x00-0x200 is initially reserved for the emulator and fonts
    if (lSize > 0xDFF) {
      std::cout << "ROM File too large" << std::endl;
    }

    // read the actual file into the buffer
    size_t result = fread(buffer, 1, lSize, rom);
    if (result != lSize) {
      std::cout << "Failed reading the file into buffer" << std::endl;
      return -1;
    }

    // pass the file into our CPU emulator
    chip8.loadRomFile(buffer, result);

    // close the rom file
    fclose(rom);
    free(buffer);
  }

  bool debug = (args[2] != NULL);
  display.setDebug(debug);

  bool keyboardState[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  bool *keyPtr = keyboardState;

  while (true) {
    mainloop(chip8, display, keyboardState, keyPtr);
  }

  // End the program, but should never get here
  return 0;
}
