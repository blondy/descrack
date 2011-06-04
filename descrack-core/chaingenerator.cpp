#include "chaingenerator.h"

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <algorithm> //std::min/max

#include <crypt.h>

#include "dictiterator.h"

char* ChainGenerator::salt_alphabet = "abcdefghijklmnopqrstuwxyzABCDEFGHIJKLMNOPQRSTUWXYZ./";
int ChainGenerator::salt_a_len = strlen(ChainGenerator::salt_alphabet);

ChainGenerator::ChainGenerator(const char* alphabet, int min_len, int max_len, int chain_length)
{
    m_alphabet_length = strlen(alphabet);
    m_alphabet = new char[m_alphabet_length];
    strcpy(m_alphabet, alphabet);

    m_min_len = std::max(min_len, 2);
    m_max_len = std::max(m_min_len, max_len);

    m_chain_length = chain_length;

    generateCaches();
}

ChainGenerator::~ChainGenerator()
{

}


char* ChainGenerator::getHash(const char* text)
{
    return NULL;
}

void ChainGenerator::reduce(const char* hash, int function, char* res_salt, char* res_text)
{
    res_salt[0] = salt_alphabet[(hash[0] ^ 0x13 ^ (unsigned char)function) % salt_a_len];
    res_salt[1] = salt_alphabet[(hash[1] ^ 0x37 ^ (unsigned char)function) % salt_a_len];

    unsigned int len_diff = m_max_len - m_min_len;

    unsigned int res_len;
    if(len_diff == 0)
        res_len = m_max_len;
    else
        res_len = (unsigned int)hash[12] % (len_diff + 1);

    int i;
    for(i = 0; i < m_min_len + res_len; i++)
    {
        res_text[i] = m_alphabet[(unsigned int)(hash[2+i] ^ (unsigned char)(i * 0x11) ^ (unsigned char)function) % m_alphabet_length];
    }

    res_text[i] = 0x00;
}

void ChainGenerator::generateChain(const char* plain, char* result)
{
    char salt[3];
    char text[10]; //1 byte extra so we don't have to bound check strlen plain

    memcpy(salt, plain, 2);
    salt[2] = 0x00;

    memcpy(text, plain+2, strlen(plain+2));
    text[strlen(plain+2)] = 0x00;

    for(int i = 0; i < m_chain_length; i++)
    {
        char* hash = crypt(text, salt);
        reduce(hash, i, salt, text);
    }

    memcpy(result, salt, 2);
    memcpy(result+2, text, 8);
}

int ChainGenerator::getLetterNum(unsigned char c)
{
    return m_char_map[(int)c];
}

void ChainGenerator::generateCaches()
{
    //Charmap
    memset(m_char_map, 0x00, 255);
    for(int i = 0; i < m_alphabet_length; i++)
        m_char_map[(int)m_alphabet[i]] = i;
}

DictIterator* ChainGenerator::createDictIterator()
{
    return new DictIterator(m_alphabet, m_alphabet_length, m_min_len, m_max_len);
}
