#include "./emu/cpu.hpp"
#include "./display/display.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>

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
  bool runLoop = false;

  while (true) {
    // timing for frame limiting
    Uint64 start = SDL_GetPerformanceCounter();

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
        exit(-1);
      }

      // draw the screen
      if (chip8.drawFlag)
      {
        chip8.drawFlag = false;
        display.drawWindow(chip8.gfx, chip8.startX, chip8.startY);
      }
    }

    Uint64 end = SDL_GetPerformanceCounter();

	  float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

	  // Cap to 200 FPS, roughly the frame rate of the chip-8
    if ((1.428f - elapsedMS) > 0)
    {
	    SDL_Delay(floor(1.428f - elapsedMS));
      timer += 1.428f;
    } else {
      timer += elapsedMS;
    }

    // // Timers only update on a 60Hrz frequency
    // std::cout << "Elapsed Timer" << elapsedMS << std::endl;
    // std::cout << "Timer: " << timer << std::endl;
    if (timer > 16.666f && runLoop)
    {
      timer = 0.0;
      chip8.updateTimers();
    }
  }

  // End the program, but should never get here
  return 0;
}
