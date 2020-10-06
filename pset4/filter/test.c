#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(void)
{
    float counter = 0.0;
    for(int i = 0; i < 10; i++){
        counter++;
    }
    printf("%f\n", counter);
}