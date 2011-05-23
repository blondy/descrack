#include <descrackcore.h>
#include <mpi/mpi.h>

#include "slave.h"
#include "master.h"

#include <chaingenerator.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    ChainGenerator g("abcdefghijklmnopqrstuvwxyz ", 3, 5);
    uint64_t ab = g.getIdx("zzz");
    char* ab_ = g.getPlain(ab);
    printf("%d = %s", (int)ab, ab_);

#if 0
    MPI_Init(&argc, &argv);

    int size, rank;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    Entity* entity;
    if(rank == 0)
    {
        entity = new Master(size, rank);
    }
    else
    {
        entity = new Slave(size, rank);
    }

    int ret = entity->run(argc, argv);
    delete entity;
    return ret;
#endif
}
