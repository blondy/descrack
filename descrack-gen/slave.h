#ifndef SLAVE_H
#define SLAVE_H

#include "entity.h"

class Slave : public Entity
{
public:
    Slave(int size, int rank);

    int run(int argc, char **argv);
};

#endif // SLAVE_H
