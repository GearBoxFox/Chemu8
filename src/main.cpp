#include <iostream>
#include <SDL2/SDL.h>
#include "./emu/cpu.hpp"

// You must include the command line parameters for your main function to be recognized by SDL
int main(int argc, char** args) {
	// The Chemu8 Emulator
	cpu chip8;

	while (;;)
	{
		int loopSuccess = chip8.executeInstructionLoop();

		if (loopSuccess != 1) {
			std::cout << "Execution error, panicking";
			return -1;
		}
	}
	
	
	// End the program, but should never get here
	return 0;
}