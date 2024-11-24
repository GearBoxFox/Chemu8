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

  // SDL event
  SDL_Event e;

  // the first argument should be the ROM file to load
  if (argc < 2) {
    std::cout << "Missing ROM file to play." << std::endl;
    return -1;
  } else if (argc > 2) {
    std::cout << "Too many arguments." << std::endl;
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

  while (true) {
    // Event loop
    while (SDL_PollEvent(&e) != 0)
    {
      switch (e.type)
      {
      case SDL_QUIT:
        return 0;
        break;

      case SDL_KEYDOWN:
        // testkeycode
        switch (e.key.keysym.sym)
        {
          case SDLK_SPACE:
            std::cout << "Executing loop cycle" << std::endl;

            // run CPU clock cycle
            if (chip8.executeInstructionLoop() != 0)
            {
              return -1;
            }

            // draw the screen
            if (chip8.drawFlag)
            {
              display.drawWindow(chip8.gfx);
            }
          break;

          case SDLK_g:
            // print graphics memory for debugging
            for (int y = 0; y < 32; y++)
            {
              for (int x = 0; x < 64; x++)
              {
                int rawIndex = x + (y * 64);
                if (chip8.gfx[rawIndex] != 0)
                {
                  std::cout << "1";
                } else {
                  std::cout << "0";
                }

                std::cout << " ";
              }
              
              std::cout << std::endl;
            }
            
        }

        break;
      }
    }
  }

  // End the program, but should never get here
  return 0;
}
