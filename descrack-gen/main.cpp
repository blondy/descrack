#include <descrackcore.h>
#include <mpi/mpi.h>

#include "slave.h"
#include "master.h"

#include <chaingenerator.h>
#include <stdio.h>

#include <dictiterator.h>

int main(int argc, char *argv[])
{
    DictIterator dictit("abc", 3, 3, 5);
    for(int i = 0; i < 50; i++)
    {
        dictit.advance(i);
        printf("%s; ", dictit.getPlain());
        dictit.reset();
    }

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
