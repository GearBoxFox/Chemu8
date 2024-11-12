#include "cpu.hpp"

cpu::cpu(/* args */)
{
}

cpu::~cpu()
{
}

void cpu::executeInstructionLoop()
{
    // fetch step
    // loads the current program counter into the index 
    // opcodes are 2 bytes long, so we have to bit shift and merge
    opcode = mem.getAdress(pc) << 8 | mem.getAdress(pc + 1);

    // decode + execute
    // chip-8 has fairly a simple execute stage, so we can merge the two steps
    // switch (opcode & 0xC0)
    // {
    // case /* constant-expression */:
    //     /* code */
    //     break;
    
    // default:
    //     break;
    // } 
}
