#include "slave.h"

#include <mpi/mpi.h>
#include <stdio.h>
#include <string.h>

#include <chaingenerator.h>
#include <dictiterator.h>

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

    m_alphabet = new char[m_alphabet_length+1];
    m_alphabet[m_alphabet_length] = 0x00;

    MPI_Bcast(m_alphabet, m_alphabet_length, MPI_CHAR, 0, MPI_COMM_WORLD);

    chaingen = new ChainGenerator(m_alphabet, m_min_len, m_max_len, m_chain_length);
    iterator = chaingen->createDictIterator();

    printf("sup im %d and ill crunch: %d %d %d %d\n", m_rank, m_alphabet_length, m_min_len, m_max_len, m_chain_length);
}

void Slave::getToWork()
{
    char* state = new char[m_max_len];
    MPI_Recv(state, m_max_len, MPI_CHAR, 0, 1338, MPI_COMM_WORLD, MPI_IGNORE_STATUS);
    iterator->initFromState(state);

    int chains_count = 100;
    static char chains[2000];

    int iter_status = 0;
    char* chainPtr = chains;
    for(int i = 0; i < chains_count; i++)
    {
        iterator->getPlain(chainPtr);
        chaingen->generateChain(chainPtr, chainPtr + 10);
        chainPtr += 20;

        //Warning: not a bug!
        //when iterator returns "1" (end of dictionary), we still have one chain to generate
        if(iter_status == 1)
            break;
        iterator->advanceOne(&iter_status);
    }


    delete state;
}

int Slave::run(int argc, char **argv)
{
    recvParams();

    static char iWantWorkOp = 0x00;
    char opbuffer;

    for(;;)
    {
        MPI_Send(&iWantWorkOp, 1, MPI_CHAR, 0, 1337, MPI_COMM_WORLD);
        MPI_Recv(&opbuffer, 1, MPI_CHAR, 0, 1338, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if(opbuffer == 0x00)
        {

        }
        else
        {
            //no more work
            break;
        }
    }

    return 0;
}
