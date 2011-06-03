#include "slave.h"

#include <mpi/mpi.h>

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


}

int Slave::run(int argc, char **argv)
{
    recvParams();

    return 0;
}
