#include "master.h"

#include <string.h>
#include <mpi/mpi.h>

#include <chaingenerator.h>


Master::Master(int size, int rank)
    : Entity(size, rank)
{
}

Master::~Master()
{
    delete chaingen;
}

void Master::init()
{
    m_alphabet = "ABCDEFGHIJKLMNOPQRSTUWXYZ";
    m_alphabet_length = strlen(m_alphabet);

    m_min_len = 3;
    m_max_len = 6;

    m_chain_length = 3;

    chaingen = new ChainGenerator("ABCDEFGHIJKLMNOPQRSTUWXYZ", 3, 6, 3);
}

void Master::broadcastParams()
{
    MPI_Bcast(&m_alphabet_length, 1, MPI_INTEGER, 1337, MPI_COMM_WORLD);
    MPI_Bcast(m_alphabet, m_alphabet_length, MPI_CHAR, 1338, MPI_COMM_WORLD);
    int params[3] = { m_min_len, m_max_len, m_chain_length };
    MPI_Bcast(params, 3, MPI_INTEGER, 1339, MPI_COMM_WORLD);
}

int Master::run(int argc, char** argv)
{
    broadcastParams();
    return 0;
}
