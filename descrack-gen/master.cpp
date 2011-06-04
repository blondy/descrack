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

    m_chain_length = 4;

    chaingen = new ChainGenerator("ABCDEFGHIJKLMNOPQRSTUWXYZ", m_min_len, m_max_len, m_chain_length);
}

void Master::broadcastParams()
{
    int params[4] = { m_alphabet_length, m_min_len, m_max_len, m_chain_length };

    MPI_Bcast(params, 4, MPI_INTEGER, 0, MPI_COMM_WORLD);
    MPI_Bcast(m_alphabet, m_alphabet_length, MPI_CHAR, 0, MPI_COMM_WORLD);
}

int Master::run(int argc, char** argv)
{
    init();
    broadcastParams();
    return 0;
}
