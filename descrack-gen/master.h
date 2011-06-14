#ifndef MASTER_H
#define MASTER_H

#include "entity.h"
#include <stdio.h>

class ChainGenerator;
class DictIterator;

class Master : public Entity
{
public:
    Master(int size, int rank);
    ~Master();

    void init(char** argv);
    int run(int argc, char** argv);

    void broadcastParams();

protected:
    ChainGenerator* chaingen;
    DictIterator* iterator;

    int m_advance_step;

    FILE* m_table_file;
    int m_chain_count;

    void sendWork(int proc, int* status);
    void recvChains(int proc, bool not_full_pkg = false);

    bool openFile(const char* filename);
    void flushFile();
    void closeFile();
};

#endif // MASTER_H
