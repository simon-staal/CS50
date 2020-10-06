#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long card;
    card = get_long("Number: ");
    int count = 0;
    while(card){
        card /= 10;
        count++;
    }
    printf("%i\n", count);
    int a1, a2 = 10;
    a1 = 1%2;
    printf("%i\n", a1);

}