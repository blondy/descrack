#ifndef MASTER_H
#define MASTER_H

#include "entity.h"

class Master : public Entity
{
public:
    Master(int size, int rank);

    int run(int argc, char** argv);
};

#endif // MASTER_H
