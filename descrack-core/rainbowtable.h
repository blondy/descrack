#ifndef RAINBOWTABLE_H
#define RAINBOWTABLE_H

#include <fstream>

enum RainbowTableMode_t
{
    TABLE_WRITE,
    TABLE_READ
};

class RainbowTable
{
public:
    RainbowTable(const char* filename, RainbowTableMode_t mode);
    ~RainbowTable();

    void addChain(const char* first, const char* second);
    bool getChain(char** first, char** second);

    void reset();

private:
    std::fstream m_stream;
};

#endif // RAINBOWTABLE_H
