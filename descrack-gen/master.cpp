#include "master.h"

#include <string.h>
#include <mpi/mpi.h>

#include <chaingenerator.h>
#include <dictiterator.h>

Master::Master(int size, int rank)
    : Entity(size, rank)
{
    m_chain_count = 0;
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

    m_chain_pkg_size = 500;
    m_advance_step = m_chain_pkg_size * m_chain_length;

    chaingen = new ChainGenerator(m_alphabet, m_min_len, m_max_len, m_chain_length);
    iterator = chaingen->createDictIterator();

    m_chain_buffer = new char[m_chain_pkg_size * 20];
}

void Master::broadcastParams()
{
    int params[5] = { m_alphabet_length, m_min_len, m_max_len, m_chain_length, m_chain_pkg_size };

    MPI_Bcast(params, 5, MPI_INTEGER, 0, MPI_COMM_WORLD);
    MPI_Bcast(m_alphabet, m_alphabet_length, MPI_CHAR, 0, MPI_COMM_WORLD);
}

void Master::sendWork(int proc, int* status)
{
#ifdef __VERBOSE__
    static char debugPlain[10];
    iterator->getPlain(debugPlain);
    printf("[master] sending work to %d, chains from %s\n", proc, debugPlain);
#endif

    static char workOp = 0x00;
    MPI_Send(&workOp, 1, MPI_CHAR, proc, 1338, MPI_COMM_WORLD);
    MPI_Send(iterator->getState(), m_max_len, MPI_CHAR, proc, 1338, MPI_COMM_WORLD);

    iterator->advance(m_advance_step, status);

#ifdef __VERBOSE__
    if(*status != 0)
        printf("[master] exceeded dict\n");
#endif
}

void Master::recvChains(int proc, bool not_full_pkg)
{
    int chain_count = m_chain_pkg_size;
    if(not_full_pkg)
    {
        MPI_Recv(&chain_count, 1, MPI_INTEGER, proc, 1338, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if(chain_count > m_chain_pkg_size)
        {
            //wtf I dont want your chains
            return;
        }
    }
#ifdef __VERBOSE__
    printf("[master] receiving %d chains from %d\n", chain_count, proc);
#endif

    MPI_Recv(m_chain_buffer, chain_count * 20, MPI_CHAR, proc, 1338, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    m_chain_count += chain_count;

    //save chains here
    fwrite(m_chain_buffer, chain_count, 20, m_table_file);
    flushFile();
}

void Master::flushFile()
{
    fseek(m_table_file, 0, SEEK_SET);
    fwrite(&m_chain_count, sizeof(m_chain_count), 1, m_table_file);
    fseek(m_table_file, 0, SEEK_END);
    fflush(m_table_file);

    printf("[master] Flushing, now: %d chains\n", m_chain_count);
}

int Master::run(int argc, char** argv)
{
    init();
    broadcastParams();

    char opcode;
    MPI_Status status;

    int dict_status = 0;
    int finished_count = 0;

    m_table_file = fopen(argv[1], "w+b");
    fwrite(&m_chain_count, sizeof(m_chain_count), 1, m_table_file);

    while(finished_count < m_size - 1)
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

    fclose(m_table_file);
    return 0;
}
