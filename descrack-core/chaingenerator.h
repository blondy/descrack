#ifndef CHAINGENERATOR_H
#define CHAINGENERATOR_H

#include <stdint.h>

class DictIterator;

class ChainGenerator
{
public:
    ChainGenerator(const char* alphabet, int min_len, int max_len, int chain_length);
    ~ChainGenerator();

    //Returns crypt(3) hash from text.
    char* getHash(const char* text);

    //Reduction function, reduces hash to new plaintext and salt
    void reduce(const char* hash, int function, char* res_salt, char* res_text, bool last = false);

    //Generates rainbow table chain.
    void generateChain(const char* plain, char* result);

    DictIterator* createDictIterator();

    static char* salt_alphabet;
    static int salt_a_len;

protected:
    int getLetterNum(unsigned char c);
    void generateCaches();

    char* m_alphabet;
    int m_alphabet_length;

    int m_min_len, m_max_len;

    int m_chain_length;

    //Caches
    char m_char_map[256];

};

#endif // CHAINGENERATOR_H
