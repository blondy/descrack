#ifndef ENTITY_H
#define ENTITY_H

// Sorry, can't think of a better name.

#define __VERBOSE__

class Entity
{
public:
    Entity(int size, int rank);

    virtual int run(int argc, char** argv) = 0;

protected:
    int m_size;
    int m_rank;
};

#endif // ENTITY_H
