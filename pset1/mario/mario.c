#include <stdio.h>
#include <cs50.h>

void pyramid(int n);

int main(void)
{
    int height;
    do
    {
        height = get_int("Size: ");
    }
    while(height<1 || height>8);
    pyramid(height);
}

void pyramid(int n)
{
    for(int i=0; i<n; i++){
        //Prints leading whitespace
        for(int j=0; j<n-i-1; j++){
            printf(" ");
        }
        //Prints first pyramid
        for(int j=0; j<=i; j++){
            printf("#");
        }
        //Prints space between pyramids
        printf("  ");
        //Prints second pyramid
        for(int j=0; j<=i; j++){
            printf("#");
        }
        printf("\n");
    }
}