#include "dictiterator.h"

#include <string.h>

DictIterator::DictIterator(const char* alphabet, int a_len, int min_len, int max_len)
{
    m_a_len = a_len;
    m_alphabet = new char[a_len];
    memcpy(m_alphabet, alphabet, a_len);

    m_min_len = min_len;
    m_max_len = max_len;

    m_state = new char[m_max_len];

    reset();
}

void DictIterator::initFromPlain(const char* plain)
{
    if(strlen(plain) < m_min_len)
        m_min_len = strlen(plain);
    else if(strlen(plain) > m_max_len)
        m_max_len = strlen(plain); //or should we fail in these cases?

    int i;
    for(i = 0; i < strlen(plain); i++)
    {
        for(int ch = 0; ch < m_a_len; ch++)
        {
            if(m_alphabet[ch] == plain[i])
                m_state[i] = ch + 1;
        }
    }
    for(i; i < m_max_len; i++)
        m_state[i] = 0x00;
}

void DictIterator::initFromState(const char* state)
{
    memcpy(m_state, state, m_max_len);
}

char* DictIterator::advance(int count, int* status /*= NULL*/)
{
    int rest;
    int state_start = 0;
    while(count > 0)
    {
        rest = count % m_a_len;
        count = count / m_a_len;

        m_state[state_start] += rest;

        if(m_state[state_start] >= m_a_len)
        {
            for(int i = state_start; i < m_max_len; i++)
            {
                if(m_state[i] - 1 < m_a_len)
                {
                    break;
                }
                else if(i >= m_max_len)
                {
                    if(status)
                        *status = 1;
                    m_state[i] = m_a_len;
                    count = 0;
                    break;
                }

                m_state[i+1] += m_state[i] / m_a_len;
                m_state[i] = 1;
            }
        }

        state_start++;
    }
}

char* DictIterator::advanceOne(int* status /*= NULL*/)
{
    //TODO: advanceOne
    return advance(1, status);
}

void DictIterator::getPlain(char* plain)
{
    int i;
    for(i = 0; i < m_max_len; i++)
    {
        if(m_state[i] == 0)
        {
            plain[i] = 0x00;
            break;
        }
        plain[i] = m_alphabet[m_state[i] - 1];
    }
    if(i < 10)
        plain[i] = 0x00;
}

void DictIterator::reset()
{
    for(int i = 0; i < m_min_len; i++)
    {
        m_state[i] = 1;
    }

    for(int i = m_min_len; i < m_max_len; i++)
    {
        m_state[i] = 0;
    }
}
