#include <stdio.h>
#include "dictionary.h"
#include <stdint.h>

unsigned int hash(const char *word);

int main(void)
{
    char *word = "Hello";
    uint16_t h = 0xffff;
    h += 1;
    printf("%u\n", h);
    h = hash(word);
    printf("%u\n", h);
    h = hash(word);
    printf("%u\n", h);
}

unsigned int hash(const char *word)
{
    uint16_t hash = 5381;
    unsigned const char *us;

    us = (unsigned const char *) word;

    while (*us != '\0'){
        hash = ((hash << 5) + hash) + *us; /* hash * 33 + c */
        us++;
    }
    return hash;
}

unsigned int hash_m(const char *word)
{
    uint16_t h = 0;
    unsigned const char *us;

    //Ensures elements of word are treated as >=0
    us = (unsigned const char *) word;

    //Iterates through string
    while(*us != '\0'){
        h = h * MULTIPLIER + *us;
        us++;
    }
    return h;
}