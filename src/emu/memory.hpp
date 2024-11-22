#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>

class chipMemory
{
private:
    /* data */
    unsigned char ram[4096];

    void loadFontData();
public:
    chipMemory();
    ~chipMemory();

    void setAdress(unsigned short adress, unsigned char data);
    unsigned char getAdress(unsigned short adress);
};

#endif
