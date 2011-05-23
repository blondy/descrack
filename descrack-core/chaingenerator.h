#ifndef CHAINGENERATOR_H
#define CHAINGENERATOR_H

#include <stdint.h>

class ChainGenerator
{
public:
    ChainGenerator(const char* alphabet, int min_len, int max_len);
    ~ChainGenerator();

    char* getPlain(uint64_t idx);
    uint64_t getIdx(const char* plain);

    //Returns crypt(3) hash from text.
    char* getHash(const char* text);

    //Reduction function, reduces hash to index.
    char* reduce(const char* hash, int function);

    //Generates rainbow table chain.
    char* generateChain(const char* plain);

protected:
    int getLetterNum(const char c);
    void generateCaches();

    char* m_alphabet;
    int m_alphabet_length;

    int m_min_len, m_max_len;

    //Caches
    uint64_t* m_pow_map;
    char m_char_map[256];

};

#endif // CHAINGENERATOR_H
