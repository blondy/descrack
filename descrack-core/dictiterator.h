#ifndef DICTITERATOR_H
#define DICTITERATOR_H

#include <stdlib.h>

class DictIterator
{
public:
    DictIterator(const char* alphabet, int a_len, int min_len, int max_len);

    void initFromPlain(const char* plain);
    void initFromState(const char* state);

    char* advance(int count, int* status = NULL);
    char* advanceOne(int* status = NULL);

    void getPlain(char* plain);

    void reset();

    char* getState() { return m_state; }
private:
    char* m_alphabet;
    int m_a_len;

    int m_min_len;
    int m_max_len;

    char* m_state;
};

#endif // DICTITERATOR_H
