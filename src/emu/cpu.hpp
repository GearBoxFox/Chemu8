#ifndef CPU_H
#define CPU_H

#include <iostream>
#include "./memory.hpp"

// macros for extracting nibbles from opcodes
#define FIRSTNIBBLE(x)  (x & 0xF000) >> 12
#define SECONDNIBBLE(x) (x & 0x0F00) >> 8
#define THIRDNIBBLE(x)  (x & 0x00F0) >> 4
#define FOURTHNIBBLE(x) (x & 0x000F)

class cpu
{
private:
    // RAM for fonts + program + work
    chipMemory mem;

    // 15 1-byte general purpose registers + 1 carry-bit register
    unsigned char v[16];

    // 12 bit index and program counter registers
    unsigned short pc;
    unsigned short index;

    // the current opcode
    unsigned char opcode;
    
    // two delay timers, both updating at 60 Hz
    unsigned char delay_timer;
    unsigned char sound_timer;

    // clears the screen
    void clearScreen();
public:
    cpu(/* args */);
    ~cpu();

    // chip-8 used a 64x32 monocolor display
    unsigned char gfx[64 * 32];
    bool drawFlag = false;

    // runs the basic fetch-decode-execute loop
    int executeInstructionLoop();

    // loads a program into the memory and starts the execution
    void loadRomFile(char* rom, size_t romSize);
};

#endif