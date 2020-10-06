#include <stdio.h>
#include <string.h>

int main(void)
{
    for(int i = 0; i<26; i++){
        char a = i+65;
        printf("Char %c: %i\n", a, i+65);
    }
    for(int i = 0; i<26; i++){
        char a = i+97;
        printf("Char %c: %i\n", a, i+97);
    }
}