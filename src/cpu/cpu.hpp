#ifndef CPU_H
#define CPU_H

#include "../memory/memory.hpp"

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
    BYTE v[16];

    // 12 bit index and program counter registers
    ADRESS pc;
    ADRESS i;

    // the current opcode
    ADRESS opcode;

    // chip-8 used a 64x32 monocolor display
    BYTE gfx[64 * 32];
    
    // two delay timers, both updating at 60 Hz
    BYTE delay_timer;
    BYTE sound_timer;

    // runs the basic fetch-decode-execute loop
    void executeInstructionLoop();
public:
    cpu(/* args */);
    ~cpu();

    void loadRomFile();
};

#endif