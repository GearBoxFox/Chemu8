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
        // 0x1NNN - jump NNN
        pc = 0x0 << 12
            | nibbles[1] << 8
            | nibbles[2] << 4
            | nibbles[3];
        break;

    case 0x2:
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
        // 0x6XNN - set register VX to NN
        v[nibbles[1] - 1] = nibbles[2] << 4 | nibbles[3];
        break;

    case 0x7:
        // 0x7XNN - add value NN to register VX
        v[nibbles[1] - 1] = v[nibbles[1] - 1] 
            + (nibbles[2] << 4 | nibbles[3]);
        break;

    case 0x8:
        /* code */
        break;

    case 0x9:
        /* code */
        break;

    case 0xA:
        // 0xANNN - set register I to NNN
        index =  0x0 << 12 
            | nibbles[1] << 8
            | nibbles[2] << 4
            | nibbles[3];
        break;

    case 0xB:
        /* code */
        break;

    case 0xC:
        /* code */
        break;

    case 0xD:
        // 0xDXYN - draw to screen
        // I register - the index of the sprite to draw
        // N - how many pixels tall the sprite is
        // VX - register that holds the X coord
        // VY - register that holds the Y coord

        BYTE xCoord = v[nibbles[1]] % 64; // modulo 64 because the screen is oly 64 pixel long
        BYTE yCoord = v[nibbles[2]] % 32; // modulo 32 because the screen is oly 32 pixel tall

        BYTE spriteHeight = nibbles[3];

        // draw top->bottom
        for (int x = 0; x < spriteHeight; x++)
        {
            // get the row for the sprite
            BYTE row = mem.getAdress(index + x);
            // draw left->right, each sprite is 8 bits long
            for(int y = 7; y >= 0; y--)
            {
                // mask out the specific pixel
                bool pixel = row & (0x01 << y);

                // error if drawing off screen
                int xIndex = xCoord + (8 - y);
                if (xIndex > 64) break;

                // error if drawing off screen
                int yIndex = yCoord + x;
                if (yIndex > 32) break;

                // the gfx array storing pixels is a 1D array
                int rawIndex = xIndex + (yIndex * 64);
                BYTE currentPixel = gfx[rawIndex];

                // the pixels are drawn by xoring 
                bool overflow = currentPixel ^ pixel;
                if (overflow) {
                    gfx[rawIndex] = !gfx[rawIndex];
                    v[0xF] = 1;
                    drawFlag = true;
                }
            }
        }
        
        
        break;

    case 0xE:
        /* code */
        break;

    case 0xF:
        /* code */
        break;

    default:
        // error, we got a bad opcode
        std::cout << std::format("Unknown opcode {}", opcode);
        return 1;
    } 

    return 0;
}
