#ifndef CPU_H
#define CPU_H

#include "../memory/memory.hpp"

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