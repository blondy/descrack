#ifndef SLAVE_H
#define SLAVE_H

#include "entity.h"

class ChainGenerator;
class DictIterator;

class Slave : public Entity
{
public:
    Slave(int size, int rank);
    ~Slave();

    int run(int argc, char **argv);

    void recvParams();
    void getToWork();
protected:
    ChainGenerator* chaingen;
    DictIterator* iterator;
};

#endif // SLAVE_H
