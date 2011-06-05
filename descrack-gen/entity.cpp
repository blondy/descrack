#include "entity.h"

#include <string.h>

Entity::Entity(int size, int rank)
{
    m_size = size;
    m_rank = rank;

    m_chain_buffer = NULL;
}

Entity::~Entity()
{
    if(m_chain_buffer)
        delete m_chain_buffer;
}
