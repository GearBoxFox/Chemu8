#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include "./emu/cpu.hpp"

// You must include the command line parameters for your main function to be recognized by SDL
int main(int argc, char** args) {
	// The Chemu8 Emulator
	cpu chip8;

	// the first argument should be the ROM file to load
	std::cout << argc << std::endl;
	if (argc < 2) {
		std::cout << "Missing ROM file to play." << std::endl;
	} else if (argc > 2) {
		std::cout << "Too many arguments." << std::endl;
	} else {
		// read the file
		std::ifstream rom(args[1], std::ios::binary);
		
		if (!rom) 
		{
			std::cout << "Failed to open ROM file." << std::endl;
			return -1;
		}

		// pass the file into our CPU emulator 
		chip8.loadRomFile(&rom);

		// close the rom file
		rom.close();
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