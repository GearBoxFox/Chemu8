#include "cpu.hpp"

cpu::cpu(/* args */)
{
}

cpu::~cpu()
{
}

int cpu::executeInstructionLoop()
{
    // fetch step
    // loads the current program counter into the index 
    // opcodes are 2 bytes long, so we have to bit shift and merge
    opcode = mem.getAdress(pc) << 8 | mem.getAdress(pc + 1);

    // decode + execute
    // chip-8 has fairly a simple execute stage, so we can merge the two steps

    // chip-8 uses half-bytes or "nibbles"
    BYTE nibbles[4] = 
    {
        FIRSTNIBBLE(opcode),
        SECONDNIBBLE(opcode),
        THIRDNIBBLE(opcode),
        FOURTHNIBBLE(opcode),
    };

    switch (nibbles[0])
    {
    case 0x0:
        // 0x00E0 - clear screen
        for (int i = 0; i < sizeof(gfx) / sizeof(gfx[0]); i++)
        {
            gfx[i] = 0x00;
        }

        // redraw screen
        drawFlag = true;
        break;

    case 0x1:
        /* code */
        break;

    case 0x2:
        /* code */
        break;

    case 0x3:
        /* code */
        break;

    case 0x4:
        /* code */
        break;
    
    case 0x5:
        /* code */
        break;

    case 0x6:
        /* code */
        break;

    case 0x7:
        /* code */
        break;

    case 0x8:
        /* code */
        break;

    case 0x9:
        /* code */
        break;

    case 0xA:
        /* code */
        break;

    case 0xB:
        /* code */
        break;

    case 0xC:
        /* code */
        break;

    case 0xD:
        /* code */
        break;

    case 0xE:
        /* code */
        break;

    case 0xF:
        /* code */
        break;

    default:
        // error, we got a bad opcode
        return 1;
    } 

    return 0;
}
