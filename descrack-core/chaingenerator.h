#ifndef CHAINGENERATOR_H
#define CHAINGENERATOR_H

#include <stdint.h>

class DictIterator;

class ChainGenerator
{
public:
    ChainGenerator(const char* alphabet, int min_len, int max_len, int chain_length);
    ~ChainGenerator();

    //Reduction function, reduces hash to new plaintext and salt
    void reduce(const char* hash, int function, char* res_salt, char* res_text, bool last = false);

    //Generates rainbow table chain.
    void generateChain(const char* plain, char* result);

    DictIterator* createDictIterator();

    static char* salt_alphabet;
    static int salt_a_len;

protected:
    char* m_alphabet;
    int m_alphabet_length;

    int m_min_len, m_max_len;

    int m_chain_length;

};

#endif // CHAINGENERATOR_H
