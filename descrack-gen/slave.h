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

    char* m_alphabet;
    int m_alphabet_length;

    int m_min_len, m_max_len;

    int m_chain_length;
};

#endif // SLAVE_H
