#include <stdio.h>
#include "dictionary.h"
#include <stdint.h>

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


int main(void)
{
    printf("%lu\n", sizeof(node));
}