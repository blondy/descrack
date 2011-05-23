#include "chaingenerator.h"

#include <stdlib.h>
#include <math.h>

#include <string.h>
#include <stdio.h>

ChainGenerator::ChainGenerator(const char* alphabet, int min_len, int max_len)
{
    m_alphabet_length = strlen(alphabet);
    m_alphabet = new char[m_alphabet_length];
    strcpy(m_alphabet, alphabet);

    m_min_len = min_len;
    m_max_len = max_len;

    generateCaches();
}

ChainGenerator::~ChainGenerator()
{
    delete m_pow_map;
}

char* ChainGenerator::getPlain(uint64_t idx)
{
    char* plain = new char[m_max_len+1];
    for(int i = m_max_len; i >= 0; i--)
    {
        int num = idx / m_pow_map[i];
        idx = idx % m_pow_map[i];
        if(num != 0)
            plain[i] = m_alphabet[num - 1];
        else
            plain[i] = 0x00;
    }
    return plain;
}

uint64_t ChainGenerator::getIdx(const char* plain)
{
    uint64_t ret = 0;
    for(int i = 0; i < strlen(plain); i++)
    {
        ret += m_pow_map[i] * (getLetterNum(plain[i]) + 1);
    }

    return ret;
}

char* ChainGenerator::getHash(const char* text)
{
    return NULL;
}

char* ChainGenerator::reduce(const char* hash, int function)
{
    return NULL;
}

char* ChainGenerator::generateChain(const char* plain)
{

}

int ChainGenerator::getLetterNum(const char c)
{
    return m_char_map[c];
}

void ChainGenerator::generateCaches()
{
    //Charmap
    memset(m_char_map, 0x00, 255);
    for(int i = 0; i < m_alphabet_length; i++)
        m_char_map[m_alphabet[i]] = i;

    //powmap
    m_pow_map = new uint64_t[m_max_len+1];
    m_pow_map[0] = 1;
    for(int i = 1; i <= m_max_len; i++)
    {
        m_pow_map[i] = 1;
        for(int j = 0; j < i; j++)
        {
            m_pow_map[i] *= m_alphabet_length+1;
        }
    }
}
