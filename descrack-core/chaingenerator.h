#ifndef CHAINGENERATOR_H
#define CHAINGENERATOR_H

class ChainGenerator
{
public:
    ChainGenerator();

    //Returns crypt(3) hash from text.
    char* getHash(const char* text);

    //Reduction function, reduces hash to index.
    char* reduce(const char* hash, int function);

    //Generates rainbow table chain.
    char* generateChain(const char* plain);

private:
    char* m_alphabet;
    int m_alphabet_length;
};

#endif // CHAINGENERATOR_H
