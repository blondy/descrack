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

    if(argc != 7)
    {
        printf("Usage: mpiexec -n [processors_count] [filename] -c [alphabet] [min_length] [max_length] [chain_length] [chain_package_size]\n");
        return -1;
    }
    else{
        int i;
        for(i=1; i<argc; i++){
            switch(i){
                case 1:
                    if(strcmp("-c",argv[i]) != 0){
                        printf("There must be flag -c not %s which stands for configure.\n", argv[i]);
                    }
                    break;
                /*case 2:
                    if(strlen(argv[i]) != strlen(trim(argv[i]))){ //no trim function in c++;(
                        printf("Alphabet cannot have white space characters.\n");
                    }
                    break;*/
                case 3:
                    if(atoi(argv[i]) == NULL || atoi(argv[i]) < 2 || atoi(argv[i]) > atoi(argv[i+1]) || atoi(argv[i]) > strlen(argv[i-1])){
                        printf("Minimal length of the alphabet input set of characters must be at least 2 and smaller/equal than maximal length.\n");
                    }
                    break;
                case 4:
                    if(atoi(argv[i]) == NULL || atoi(argv[i]) > strlen(argv[i-2]) || atoi(argv[i]) < atoi(argv[i-1])){
                        printf("Maximal length of the alphabet input set of characters must be smaller/equal to alphabet length and greater/equal than minimal length.\n");
                    }
                    break;
                case 5:
                    if(atoi(argv[i]) == NULL){
                        printf("Chain length must be an integer number.\n");
                    }
                    break;
                case 6:
                    if(atoi(argv[i]) == NULL){
                        printf("Chain package size must be an integer number.\n");
                    }
                    break;
            }
        }
    }

    int ret = entity->run(argc, argv);
    delete entity;

    MPI_Finalize();

    return ret;
}
