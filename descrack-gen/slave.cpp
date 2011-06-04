#include "slave.h"

#include <mpi/mpi.h>
#include <stdio.h>
#include <string.h>

Slave::Slave(int size, int rank)
    : Entity(size, rank)
{
    m_alphabet = NULL;
}

Slave::~Slave()
{
    if(m_alphabet)
        delete m_alphabet;
}

void Slave::recvParams()
{
    int params[4];
    MPI_Bcast(params, 4, MPI_INTEGER, 0, MPI_COMM_WORLD);

    m_alphabet_length = params[0];
    m_min_len = params[1];
    m_max_len = params[2];
    m_chain_length = params[3];

    m_alphabet = new char[m_alphabet_length];

    MPI_Bcast(m_alphabet, m_alphabet_length, MPI_CHAR, 0, MPI_COMM_WORLD);

    printf("sup im %d and ill crunch: %d %d %d %d\n", m_rank, m_alphabet_length, m_min_len, m_max_len, m_chain_length);
}

int Slave::run(int argc, char **argv)
{
    recvParams();

    return 0;
}
