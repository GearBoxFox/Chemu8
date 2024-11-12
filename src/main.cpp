#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "./emu/cpu.hpp"

// You must include the command line parameters for your main function to be recognized by SDL
int main(int argc, char** args) {
	// The Chemu8 Emulator
	cpu chip8;

	// the first argument should be the ROM file to load
	if (argc < 2) {
		std::cout << "Missing ROM file to play." << std::endl;
		return -1;
	} else if (argc > 2) {
		std::cout << "Too many arguments." << std::endl;
		return -1;
	} else {
		// read the file
		FILE * rom = fopen(args[1], "rb");

		// make sure the rom file actually opened
		if (rom == NULL) 
		{
			std::cout << "Failed to open ROM file." << std::endl;
			return -1;
		}

		// obtain file size:
		fseek (rom, 0, SEEK_END);
		long lSize = ftell (rom);
		rewind (rom);

		char * buffer = (char*) malloc(sizeof(char) * lSize);
		if (buffer == NULL)
		{
			std::cout << "Error allocating memory for ROM file." << std::endl;
			return -2;
		}

		// 0x00-0x200 is initially reserved for the emulator and fonts 
		if (lSize > 0xDFF)
		{
			std::cout << "ROM File too large" << std::endl;
		}

		// read the actual file into the buffer
		size_t result = fread(buffer, 1, lSize, rom);
		if (result != lSize)
		{
			std::cout << "Failed reading the file into buffer" << std::endl;
			return -1;
		}

		// pass the file into our CPU emulator 
		chip8.loadRomFile(buffer, result);

		// close the rom file
		fclose(rom);
		free(buffer);
	}

	while (true)
	{
		int loopSuccess = chip8.executeInstructionLoop();

		if (loopSuccess != 0) {
			std::cout << "Execution error, panicking" << std::endl;
			return -1;
		}
	}
	
	
	// End the program, but should never get here
	return 0;
}