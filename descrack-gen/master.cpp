#include "master.h"

#include <string.h>
#include <mpi/mpi.h>

#include <chaingenerator.h>
#include <dictiterator.h>

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
    iterator = chaingen->createDictIterator();
}

void Master::broadcastParams()
{
    int params[4] = { m_alphabet_length, m_min_len, m_max_len, m_chain_length };

    MPI_Bcast(params, 4, MPI_INTEGER, 0, MPI_COMM_WORLD);
    MPI_Bcast(m_alphabet, m_alphabet_length, MPI_CHAR, 0, MPI_COMM_WORLD);
}

void Master::sendWork(int proc, int* status)
{
    static char workOp = 0x00;
    MPI_Send(&workOp, 1, MPI_CHAR, proc, 1338, MPI_COMM_WORLD);
    MPI_Send(iterator->getState(), m_max_len, MPI_CHAR, proc, 1338, MPI_COMM_WORLD);

    iterator->advance(100, status);
}

void Master::recvChains(int proc, bool not_full_pkg)
{
    int chain_count = 100;
    static char chains[2000]; //100 chains * 20 bytes per chain
    if(not_full_pkg)
    {
        MPI_Recv(&chain_count, 1, MPI_INTEGER, proc, 1338, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    MPI_Recv(chains, chain_count * 20, MPI_CHAR, proc, 1338, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    //save chains here
}

int Master::run(int argc, char** argv)
{
    init();
    broadcastParams();

    char opcode;
    MPI_Status status;

    int dict_status = 0;
    int finished_count = 0;

    while(finished_count < m_size - 1);
    {
        MPI_Recv(&opcode, 1, MPI_CHAR, MPI_ANY_SOURCE, 1337, MPI_COMM_WORLD, &status);
        switch(opcode)
        {
            case 0x00:
                if(dict_status == 0)
                {
                    sendWork(status.MPI_SOURCE, &dict_status);
                }
                else
                {
                    static char noMoreWorkOp = 0x01;
                    MPI_Send(&noMoreWorkOp, 1, MPI_CHAR, status.MPI_SOURCE, 1338, MPI_COMM_WORLD);
                    finished_count++;
                }
                break;
            case 0x01:
                recvChains(status.MPI_SOURCE);
                break;
            case 0x02:
                recvChains(status.MPI_SOURCE, true);
                break;
        }
    }
    return 0;
}
