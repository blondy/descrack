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

    char* getPlain();

    void reset();
private:
    char* m_alphabet;
    int m_a_len;

    int m_min_len;
    int m_max_len;

    char* m_state;

    int m_state_start;
};

#endif // DICTITERATOR_H
