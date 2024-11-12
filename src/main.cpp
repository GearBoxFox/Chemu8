#include <iostream>
#include <SDL2/SDL.h>
#include "./memory/memory.hpp"

// You shouldn't really use this statement, but it's fine for small programs
using namespace std;

// You must include the command line parameters for your main function to be recognized by SDL
int main(int argc, char** args) {
	// Memory for the Chemu8 Emulator
	chipMemory memory;

	cout << memory.getAdress(0x050) << std::endl;
	
	// End the program
	return 0;
}