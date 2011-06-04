#include "dictiterator.h"

#include <string.h>

#include "chaingenerator.h"

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
    //Warning: this is broken because it doesn't support salt
    //fix if you want to use this :P

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

    int a_len_for_letter;

    while(count > 0)
    {
        rest = count % m_a_len;
        count = count / m_a_len;

        m_state[state_start] += rest;

        if(state_start < 2)
            a_len_for_letter = ChainGenerator::salt_a_len;
        else
            a_len_for_letter = m_a_len;

        if(m_state[state_start] >= a_len_for_letter)
        {
            for(int i = state_start; i < m_max_len; i++)
            {
                if(i < 2)
                    a_len_for_letter = ChainGenerator::salt_a_len;
                else
                    a_len_for_letter = m_a_len;

                if(m_state[i] - 1 < a_len_for_letter)
                {
                    break;
                }
                else if(i >= m_max_len)
                {
                    if(status)
                        *status = 1;
                    m_state[i] = a_len_for_letter;
                    count = 0;
                    break;
                }

                m_state[i+1] += m_state[i] / a_len_for_letter;
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

        if(i < 2)
            plain[i] = ChainGenerator::salt_alphabet[m_state[i] - 1];
        else
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
