#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>

#define BYTE unsigned char
#define ADRESS unsigned short

class chipMemory
{
private:
    /* data */
    BYTE ram[4096];

    void loadFontData();
public:
    chipMemory();
    ~chipMemory();

    void setAdress(ADRESS adress, BYTE data);
    BYTE getAdress(ADRESS adress);
};

#endif
