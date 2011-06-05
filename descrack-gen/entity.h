#ifndef ENTITY_H
#define ENTITY_H

// Sorry, can't think of a better name.

//Constants and defines go here
#define __VERBOSE__

class Entity
{
public:
    Entity(int size, int rank);
    virtual ~Entity();

    virtual int run(int argc, char** argv) = 0;

protected:
    int m_size;
    int m_rank;

    char* m_alphabet;
    int m_alphabet_length;

    int m_min_len, m_max_len;

    int m_chain_length;

    int m_chain_pkg_size;
    char* m_chain_buffer;
};

#endif // ENTITY_H
