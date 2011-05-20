#ifndef CHAINGENERATOR_H
#define CHAINGENERATOR_H

class ChainGenerator
{
public:
    ChainGenerator();

    //Changes index to plaintext.
    char* getPlain(int index);

    //Returns crypt(3) hash from text.
    char* getHash(const char* text);

    //Reduction function, reduces hash to index.
    int reduce(const char* hash, int function);

    //Generates rainbow table chain.
    void generateChain(int index, char** ret_first, char** ret_second);

private:
    char* m_alphabet;
    int m_alphabet_length;
};

#endif // CHAINGENERATOR_H
