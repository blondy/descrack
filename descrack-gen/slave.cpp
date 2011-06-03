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
    MPI_Bcast(&m_alphabet_length, 1, MPI_INTEGER, 1337, MPI_COMM_WORLD);
    m_alphabet = new char[m_alphabet_length];
    MPI_Bcast(m_alphabet, m_alphabet_length, MPI_CHAR, 1338, MPI_COMM_WORLD);
    int params[3];
    MPI_Bcast(params, 3, MPI_INTEGER, 1339, MPI_COMM_WORLD);
    m_min_len = params[0];
    m_max_len = params[0];
    m_chain_length = params[0];

    printf("sup im %d and ill crunch: %d %d %d %d\n", m_rank, m_alphabet_length, m_min_len, m_max_len, m_chain_length);
}

int Slave::run(int argc, char **argv)
{
    recvParams();

    return 0;
}
