#include <iostream>
#include <SDL2/SDL.h>
#include "./cpu/cpu.hpp"

// You shouldn't really use this statement, but it's fine for small programs
using namespace std;

// You must include the command line parameters for your main function to be recognized by SDL
int main(int argc, char** args) {
	// Memory for the Chemu8 Emulator
	chipMemory memory;

	int firstNibble = FIRSTNIBBLE(0x10E0);
	cout << "raw " << (int) 0x10E0 << endl;
	cout << "should " << (int) 0x1 << endl;
	cout << "is " << (int) firstNibble << endl;
	
	// End the program
	return 0;
}