#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <format>
#include "./memory.hpp"

// macros for extracting nibbles from opcodes
#define FIRSTNIBBLE(x)  (BYTE)(x & 0xF000) >> 12
#define SECONDNIBBLE(x) (BYTE)(x & 0x0F00) >> 8
#define THIRDNIBBLE(x)  (BYTE)(x & 0x00F0) >> 4
#define FOURTHNIBBLE(x) (BYTE)(x & 0x000F)

class cpu
{
private:
    // RAM for fonts + program + work
    chipMemory mem;

    // 15 1-byte general purpose registers + 1 carry-bit register
    BYTE v[16];

    // 12 bit index and program counter registers
    ADRESS pc;
    ADRESS index;

    // the current opcode
    ADRESS opcode;
    
    // two delay timers, both updating at 60 Hz
    BYTE delay_timer;
    BYTE sound_timer;

    // clears the screen
    void clearScreen();
public:
    cpu(/* args */);
    ~cpu();

    // chip-8 used a 64x32 monocolor display
    BYTE gfx[64 * 32];
    BYTE drawFlag = false;

    // runs the basic fetch-decode-execute loop
    int executeInstructionLoop();

    // loads a program into the memory and starts the execution
    void loadRomFile(std::ifstream* rom);
};

#endif