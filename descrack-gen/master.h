#ifndef MASTER_H
#define MASTER_H

#include "entity.h"

class ChainGenerator;

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

    char* m_alphabet;
    int m_alphabet_length;

    int m_min_len, m_max_len;

    int m_chain_length;
};

#endif // MASTER_H
