#include "memory.hpp"

void Memory::setAdress(int adress, BYTE data) 
{
    ram[adress] = data;
}

BYTE Memory::getAdress(int adress) 
{
    BYTE data = ram[adress];
    return data;
}
