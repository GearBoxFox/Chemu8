#include "cpu.hpp"

cpu::cpu(/* args */)
{
    pc = 0x200;
    index = 0x0;
    clearScreen();
}

cpu::~cpu()
{
}

void cpu::loadRomFile(char* rom, size_t romSize)
{
    for (int i = 0; i < romSize; i++) 
    {
        mem.setAdress(0x200 + i, rom[i]);
    }
}

int cpu::executeInstructionLoop()
{
    // fetch step
    // loads the current program counter into the index 
    // opcodes are 2 unsigned chars long, so we have to bit shift and merge
    opcode = mem.getAdress(pc) << 8 | mem.getAdress(pc + 1);

    pc += 2;
    // decode + execute
    // chip-8 has fairly a simple execute stage, so we can merge the two steps
    std::cout << "Instruction: " << std::hex << std::setfill('0') << std::setw(2) << opcode << std::dec << std::endl;

    // chip-8 uses half-unsigned chars or "nibbles"
    int nibbles[4] = 
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
        clearScreen();
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
        std::cout << "Setting variable " << nibbles[1] << " to value " << (nibbles[2] << 4 | nibbles[3]) << std::endl;
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
    {
        // 0xDXYN - draw to screen
        // I register - the index of the sprite to draw
        // N - how many pixels tall the sprite is
        // VX - register that holds the X coord
        // VY - register that holds the Y coord

        int xCoord = v[nibbles[1]]; // modulo 64 because the screen is oly 64 pixel long
        int yCoord = v[nibbles[2]]; // modulo 32 because the screen is oly 32 pixel tall

        int spriteHeight = nibbles[3];
        unsigned short pixel;

        std::cout << "X, Y: " << 
        std::hex << xCoord <<
        std::dec <<  ", " <<
        std::hex << yCoord << 
        std::dec << std::endl;

        std::cout << "Sprite height: " << spriteHeight << std::endl;

        // draw top->bottom
        for (int y = 0; y < spriteHeight; y++)
        {
            // get the row for the sprite
            unsigned char row = mem.getAdress(index + y);
            std::cout << "Pixel row: " << row << std::endl;
            // draw left->right, each sprite is 8 bits long
            for(int x = 7; x >= 0; x--)
            {
                // mask out the specific pixel
                bool pixel = row & (0x01 << x);

                // error if drawing off screen
                int xIndex = xCoord + (8 - x);
                if (xIndex > 64) break;

                // error if drawing off screen
                int yIndex = yCoord + y;
                if (yIndex > 32) break;

                // the gfx array storing pixels is a 1D array
                int rawIndex = xIndex + (yIndex * 64);
                bool currentPixel = gfx[rawIndex];

                std::cout << "Drawing pixel at (" << xIndex << ", " << yIndex << "). Raw: " << rawIndex << std::endl;
                std::cout << "Current pixel: " << currentPixel << ". New pixel: " << pixel << std::endl;

                // the pixels are drawn by xoring 
                bool overflow = currentPixel ^ pixel;
                if (overflow) {
                    std::cout << "Pixel drawn!" << std::endl;
                    gfx[rawIndex] = !gfx[rawIndex];
                    v[0xF] = 1;
                    drawFlag = true;
                }
            }
        }

        // v[0xF] = 0;
        // for (int yline = 0; yline < spriteHeight; yline++)
        // {
        //     pixel = mem.getAdress(index + yline);
        //     for(int xline = 0; xline < 8; xline++)
        //     {
        //         if((pixel & (0x80 >> xline)) != 0)
        //         {
        //         if(gfx[(x + xline + ((y + yline) * 64))] == 1)
        //             v[0xF] = 1;                                 
        //         gfx[x + xline + ((y + yline) * 64)] ^= 1;
        //         }
        //     }
        // }

        break;
    }
    case 0xE:
        /* code */
        break;

    case 0xF:
        /* code */
        break;

    default:
        // error, we got a bad opcode
        std::cout << "Unknown opcode: " << opcode << std::endl;
        return 1;
    } 

    return 0;
}

void cpu::clearScreen()
{
    for (int i = 0; i < sizeof(gfx) / sizeof(gfx[0]); i++)
    {
        gfx[i] = 0x00;
    }


    // redraw screen
    drawFlag = true;
}
