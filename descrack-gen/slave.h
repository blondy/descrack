#ifndef SLAVE_H
#define SLAVE_H

#include "entity.h"

class Slave : public Entity
{
public:
    Slave(int size, int rank);
    ~Slave();

    int run(int argc, char **argv);

    void recvParams();
protected:
    char* m_alphabet;
    int m_alphabet_length;

    int m_min_len, m_max_len;

    int m_chain_length;
};

#endif // SLAVE_H
