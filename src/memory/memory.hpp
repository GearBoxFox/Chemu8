#ifndef MEMORY_H
#define MEMORY_H

#define BYTE unsigned char
#define ADRESS unsigned short

class Memory
{
private:
    /* data */
    BYTE ram[4096];

    void loadFontData();
public:
    Memory();
    ~Memory();

    void setAdress(ADRESS adress, BYTE data);
    BYTE getAdress(ADRESS adress);
};

#endif
