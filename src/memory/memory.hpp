#ifndef MEMORY_H
#define MEMORY_H
#define BYTE char

class memory
{
private:
    /* data */
    BYTE ram[4096];
public:
    memory();
    ~memory();

    void setAdress(int adress, BYTE data);
    BYTE getAdress(int adress);
};

memory::memory(/* args */)
{
    // leave blank
}

memory::~memory()
{
    // leave blank
}

#endif
