#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //Check usage
    if(argc != 2){
        printf("Usage: ./recover FILENAME\n");
        return 1;
    }
    //Open file
    FILE *file = fopen(argv[1], "r");
    if(!file){
        printf("File could not be opened\n");
        return 1;
    }
    int i = 0;
    unsigned char buffer[512];
    while(1){
        fread(buffer, 512, 1, file);
        if(feof(file)){
            break;
        }
        //Creates new jpeg file
        char filename[8];
        //Checks first 4 bytes of buffer to match JPEG signature
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3]>>4 == 0xe){
            //Updates filename
            sprintf(filename, "%03i.jpg", i);
            i++;
            FILE *jpeg = fopen(filename, "w");
            fwrite(buffer, 1, 512, jpeg);
            fclose(jpeg);
        }
        else{
            //Only appends bits once first jpeg signature has been found
            if(i > 0){
                FILE *jpeg = fopen(filename, "a");
                fwrite(buffer, 1, 512, jpeg);
                fclose(jpeg);
            }
        }
    }
    fclose(file);
}
