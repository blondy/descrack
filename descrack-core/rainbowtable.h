#ifndef RAINBOWTABLE_H
#define RAINBOWTABLE_H

#include <fstream>

class RainbowTable
{
public:
    RainbowTable(const char* filename, int mode);
    ~RainbowTable();

    void addChain(const char* first, const char* second);
    bool getChain(char** first, char** second);

    void reset();

private:
    std::fstream m_stream;
};

#endif // RAINBOWTABLE_H
