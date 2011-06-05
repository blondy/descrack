#ifndef MASTER_H
#define MASTER_H

#include "entity.h"

class ChainGenerator;
class DictIterator;

class Master : public Entity
{
public:
    Master(int size, int rank);
    ~Master();

    void init();
    int run(int argc, char** argv);

    void broadcastParams();

protected:
    ChainGenerator* chaingen;
    DictIterator* iterator;

    int m_advance_step;

    void sendWork(int proc, int* status);
    void recvChains(int proc, bool not_full_pkg = false);
};

#endif // MASTER_H
