#ifndef MEMORY_H
#define MEMORY_H
#define BYTE char

class Memory
{
private:
    /* data */
    BYTE ram[4096];
public:
    Memory();
    ~Memory();

    void setAdress(int adress, BYTE data);
    BYTE getAdress(int adress);
};

Memory::Memory(/* args */)
{
    // leave blank
}

Memory::~Memory()
{
    // leave blank
}

#endif
