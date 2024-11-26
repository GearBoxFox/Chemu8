#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>
#include "./memory.hpp"

// macros for extracting nibbles from opcodes
#define FIRSTNIBBLE(x)  (x & 0xF000) >> 12
#define SECONDNIBBLE(x) (x & 0x0F00) >> 8
#define THIRDNIBBLE(x)  (x & 0x00F0) >> 4
#define FOURTHNIBBLE(x) (x & 0x000F)

// SDLs Uint8 typedef
typedef uint8_t Uint8;

class cpu
{
private:
    // RAM for fonts + program + work
    chipMemory mem;

    // two delay timers, both updating at 60 Hz
    unsigned char delay_timer;
    unsigned char sound_timer;

    // clears the screen
    void clearScreen();
public:
    cpu(/* args */);
    ~cpu();

    // chip-8 used a 64x32 monocolor display
    bool gfx[64 * 32];
    bool drawFlag = false;

    // 15 1-byte general purpose registers + 1 carry-bit register
    unsigned char v[16];
    unsigned short index;

    // 12 bit index and program counter registers
    unsigned short pc;
    unsigned short pcStack;

    // the current opcode
    unsigned short opcode;

    // runs the basic fetch-decode-execute loop
    int executeInstructionLoop(const Uint8 *keyboard);

    // loads a program into the memory and starts the execution
    void loadRomFile(char* rom, size_t romSize);

    // updates the timers and makes the beep if neccessary
    bool updateTimers();
};

#endif