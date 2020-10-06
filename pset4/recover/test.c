#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i = 111;
    unsigned char a = 0xe1;
    char* ext = ".jpg";
    char name[8];
    sprintf(name, "%03i.jpg", i);
    printf("%s\n", name);
    printf("%x\n", name[9]);

}