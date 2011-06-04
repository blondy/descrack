#include <descrackcore.h>
#include <mpi/mpi.h>

#include "slave.h"
#include "master.h"

#include <chaingenerator.h>
#include <stdio.h>

#include <dictiterator.h>

#include <string.h>
#include <crypt.h>

int main(int argc, char *argv[])
{
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

    MPI_Finalize();

    return ret;
}
