#include "cpu.hpp"

cpu::cpu(/* args */)
{
    pc = 0x200;
    index = 0x0;
    clearScreen();
    
    for (int i = 0; i < 16; i++)
    {
        v[i] = 0x0;
    }
    
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

    unsigned char testValue;
    int result;

    switch (nibbles[0])
    {
    case 0x0:
        if (opcode == 0x00E0)
        {
            // 0x00E0 - clear screen
            clearScreen();
        } else if (opcode == 0x00EE) {
            // 0x00EE - return from subroutine
            std::cout << "Returning from subroutine" << std::endl;
            pc = pcStack;
        }
        break;

    case 0x1:
        // 0x1NNN - jump NNN
        pc = 0x0 << 12
            | nibbles[1] << 8
            | nibbles[2] << 4
            | nibbles[3];
        break;

    case 0x2:
        // 0x2NNN - call subroutine
        pcStack = pc;
        pc = 0x0 << 12
            | nibbles[1] << 8
            | nibbles[2] << 4
            | nibbles[3];
        break;

    case 0x3:
        // 0x3XNN - skip if value in register X is equal to NN
        testValue = nibbles[2] << 4 | nibbles[3];
        if (testValue == v[nibbles[1]])
        {
            pc += 2;
        }
        break;

    case 0x4:
        // 0x4XNN - skip if value in register X is NOT equal to NN
        testValue = nibbles[2] << 4 | nibbles[3];
        if (testValue != v[nibbles[1]])
        {
            pc += 2;
        }
        break;
    
    case 0x5:
        // 0x5XY0 - skip if register X and Y are equal
        if (v[nibbles[1]] == v[nibbles[2]])
        {
            pc += 2;
        }
        break;

    case 0x6:
        // 0x6XNN - set register VX to NN
        v[nibbles[1]] = nibbles[2] << 4 | nibbles[3];
        break;

    case 0x7:
        // 0x7XNN - add value NN to register VX
        v[nibbles[1]] = v[nibbles[1]] 
            + (nibbles[2] << 4 | nibbles[3]);
        break;

    case 0x8:
        // 0x8XYN - ALU Operations
        switch (nibbles[3])
        {
        case 0x0:
            // 0x8XY0 - Set vX to vY
            v[nibbles[1]] = v[nibbles[2]];
            break;
        
        case 0x1:
            // 0x8XY1 - vX is set to the binary OR of vX and vY
            v[nibbles[1]] = v[nibbles[1]] | v[nibbles[2]];
            break;

        case 0x2:
            // 0x8XY2 - vX is set to the binary AND of vX and vY
            v[nibbles[1]] = v[nibbles[1]] & v[nibbles[2]];
            break;

        case 0x3:
            // 08XY3 - vX is set to the logical XOR of vX and vY
            v[nibbles[1]] = v[nibbles[1]] ^ v[nibbles[2]];
            break;

        case 0x4:
            // 0x8XY4 - vX is set to vX + vY. This DOES affect the carry flag
            result = v[nibbles[1]] + v[nibbles[2]];

            if (result > 255)
            {
                v[nibbles[1]] = result % 256;
                v[0xF] = 1;
            } else {
                v[nibbles[1]] = result;
                v[0xF] = 0;
            }
            break;

        case 0x5:
            // 0x8XY5 - vX is set to vX - vY. Carry is set to vX > vY
            result = v[nibbles[1]] - v[nibbles[2]];
            v[nibbles[1]] = result % 256;

            if (v[nibbles[1]] > v[nibbles[2]])
            {
                v[0xF] = 1;
            } else {
                v[0xF] = 0;
            }
            break;

        case 0x6:
            // 0x8XY6 - vX is set to vX >> 1. RIGHT shift
            testValue = v[nibbles[1]];
            v[nibbles[1]] = v[nibbles[1]] >> 1;

            // TODO make toggle for modern versions
            // original chip-8 sets vX to vY >> 1

            // vF is set to the bit that was shifted out
            if (testValue & 0x1 != 0)
            {
                v[0xF] = 1;
            } else {
                v[0xF] = 0;
            }
            break;

        case 0x7:
            // 0x8XY5 - vX is set to vY - vX. Carry is set to vY > vX
            result = v[nibbles[2]] - v[nibbles[1]];
            v[nibbles[1]] = result % 256;

            if (v[nibbles[2]] > v[nibbles[1]])
            {
                v[0xF] = 1;
            } else {
                v[0xF] = 0;
            }
            break;

        case 0xE:
            // 0x8XY6 - vX is set to vX << 1. LEFT shift
            testValue = v[nibbles[1]];
            v[nibbles[1]] = v[nibbles[1]] << 1;

            // TODO make toggle for modern versions
            // original chip-8 sets vX to vY << 1

            // vF is set to the bit that was shifted out
            if (testValue & 0xF != 0)
            {
                v[0xF] = 1;
            } else {
                v[0xF] = 0;
            }
            break;

        default:
            break;
        }
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

        int xCoord = v[nibbles[1]] % 64; // modulo 64 because the screen is oly 64 pixel long
        int yCoord = v[nibbles[2]] % 32; // modulo 32 because the screen is oly 32 pixel tall

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
            std::cout << "Pixel row: " << +row << std::endl;
            // draw left->right, each sprite is 8 bits long
            for(int x = 7; x >= 0; x--)
            {
                // mask out the specific pixel
                bool pixel = row & (0x01 << x);

                // error if drawing off screen
                int xIndex = xCoord + (7 - x);
                if (xIndex > 64) 
                {
                    std::cout << "Breaking from x overflow" << std::endl;
                    break;
                }

                // error if drawing off screen
                int yIndex = yCoord + y;
                if (yIndex > 32) 
                {
                    std::cout << "Breaking from y overflow" << std::endl;
                    break;
                }

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

        break;
    }
    case 0xE:
        /* code */
        break;

    case 0xF:
        // Memory Instructions
        // Based off the last two nibbles
        result = nibbles[2] << 4 | nibbles[3];
        switch (result)
        {
        case 0x1E:
            // 0xFX1E - Index += vX
            index += v[nibbles[1]];
            break;

        case 0x33:
            // 0xFX33 - splits the number at vX into three parts of a decimal number,
            // and stores it at I, I + 1, I + 2.
            // vX = 152, I = 100, I + 1 = 50, I + 2 = 2

            // copy into a temp value
            testValue = v[nibbles[1]];

            for (int i = 0; i < 3; i++)
            {
                mem.setAdress(index + i, testValue % 10);
                testValue = testValue / 10;
            }
            

        case 0x55:
            // 0xFX55 - store v0-vX in memory starting at Index
            // the original chip-8 incremented the index, modern don't
            // TODO add debug feature later for a toggle
            for (int i = 0; i < nibbles[1] + 1; i++)
            {
                mem.setAdress(index + i, v[i]);
            }
            break;

        case 0x65:
            // 0xFX55 - store v0-vX in memory starting at Index
            // the original chip-8 incremented the index, modern don't
            // TODO add debug feature later for a toggle
            for (int i = 0; i < nibbles[1] + 1; i++)
            {
                v[i] = mem.getAdress(index + i);
            }
            break;
            
        
        default:
            break;
        }
        break;

    default:
        // error, we got a bad opcode
        std::cout << "Unknown opcode: " << opcode << std::endl;
        return 1;
    } 

    return 0;
}

bool cpu::updateTimers()
{
    if (delay_timer > 0)
    {
        delay_timer--;
    }

    if (sound_timer > 0)
    {
        sound_timer--;
        return true;
    }

    return false;
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
