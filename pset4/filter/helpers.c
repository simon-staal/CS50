#include "helpers.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

// Convert image to grayscale using weighted method
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            BYTE avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width/2; j++){
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width-j-1];
            image[i][width-j-1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Creates a copy of the image to read values from
    RGBTRIPLE copy[height][width];
    memcpy(copy, image, sizeof(RGBTRIPLE)*height*width);
    //Iterates through the array
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            //Initialises average RGB values
            WORD avgR = 0;
            WORD avgG = 0;
            WORD avgB = 0;
            //Ensures that grid around pixel are within bounds of image
            int startx = (i == 0)?0:i-1;
            int starty = (j == 0)?0:j-1;
            int endx = (i == height-1)?height-1:i+1;
            int endy = (j == width-1)?width-1:j+1;
            //Iterates through grid, updating RGB values
            float n = 0;
            for(int x = startx; x <= endx; x++){
                for(int y = starty; y <= endy; y++){
                    avgR += copy[x][y].rgbtRed;
                    avgG += copy[x][y].rgbtGreen;
                    avgB += copy[x][y].rgbtBlue;
                    n++;
                }
            }
            //Updates the values in the image with average RGB values
            image[i][j].rgbtRed = round(avgR/n);
            image[i][j].rgbtGreen = round(avgG/n);
            image[i][j].rgbtBlue = round(avgB/n);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Creates a copy of the image to read values from
    RGBTRIPLE copy[height][width];
    memcpy(copy, image, sizeof(RGBTRIPLE)*height*width);
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            //Initialises Gx and Gy RGB values
            float Gx_b = 0;
            float Gy_b = 0;
            float Gx_r = 0;
            float Gy_r = 0;
            float Gx_g = 0;
            float Gy_g = 0;
            //Updates Gx and Gy for top left pixel
            if(i != 0 && j != 0){
                Gx_b += copy[i-1][j-1].rgbtBlue*-1;
                Gy_b += copy[i-1][j-1].rgbtBlue*-1;
                Gx_r += copy[i-1][j-1].rgbtRed*-1;
                Gy_r += copy[i-1][j-1].rgbtRed*-1;
                Gx_g += copy[i-1][j-1].rgbtGreen*-1;
                Gy_g += copy[i-1][j-1].rgbtGreen*-1;
            }
            //Updates Gy for top middle pixel
            if(i != 0){
                Gy_b += copy[i-1][j].rgbtBlue*-2;
                Gy_r += copy[i-1][j].rgbtRed*-2;
                Gy_g += copy[i-1][j].rgbtGreen*-2;
            }
            //Updates Gx and Gy for top right pixel
            if(i != 0 && j != (width-1)){
                Gx_b += copy[i-1][j+1].rgbtBlue;
                Gy_b += copy[i-1][j+1].rgbtBlue*-1;
                Gx_r += copy[i-1][j+1].rgbtRed;
                Gy_r += copy[i-1][j+1].rgbtRed*-1;
                Gx_g += copy[i-1][j+1].rgbtGreen;
                Gy_g += copy[i-1][j+1].rgbtGreen*-1;
            }
            //Updates Gx for middle left pixel
            if(j != 0){
                Gx_b += copy[i][j-1].rgbtBlue*-2;
                Gx_r += copy[i][j-1].rgbtRed*-2;
                Gx_g += copy[i][j-1].rgbtGreen*-2;
            }
            //Updates Gx for middle right pixel
            if( j != (width-1)){
                Gx_b += copy[i][j+1].rgbtBlue*2;
                Gx_r += copy[i][j+1].rgbtRed*2;
                Gx_g += copy[i][j+1].rgbtGreen*2;
            }
            //Updates Gx and Gy for bottom left pixel
            if(i != (height-1) && j != 0){
                Gx_b += copy[i+1][j-1].rgbtBlue*-1;
                Gy_b += copy[i+1][j-1].rgbtBlue;
                Gx_r += copy[i+1][j-1].rgbtRed*-1;
                Gy_r += copy[i+1][j-1].rgbtRed;
                Gx_g += copy[i+1][j-1].rgbtGreen*-1;
                Gy_g += copy[i+1][j-1].rgbtGreen;
            }
            //Updates Gy for bottom middle pixel
            if(i != (height-1)){
                Gy_b += copy[i+1][j].rgbtBlue*2;
                Gy_r += copy[i+1][j].rgbtRed*2;
                Gy_g += copy[i+1][j].rgbtGreen*2;
            }
            //Updates Gx and Gy for bottom right pixel
            if(i != (height-1) && j != (width-1)){
                Gx_b += copy[i+1][j+1].rgbtBlue;
                Gy_b += copy[i+1][j+1].rgbtBlue;
                Gx_r += copy[i+1][j+1].rgbtRed;
                Gy_r += copy[i+1][j+1].rgbtRed;
                Gx_g += copy[i+1][j+1].rgbtGreen;
                Gy_g += copy[i+1][j+1].rgbtGreen;
            }
            int B = round(sqrt(pow(Gx_b, 2)+pow(Gy_b, 2)));
            int R = round(sqrt(pow(Gx_r, 2)+pow(Gy_r, 2)));
            int G = round(sqrt(pow(Gx_g, 2)+pow(Gy_g, 2)));
            image[i][j].rgbtBlue = (B > 255)?255:B;
            image[i][j].rgbtRed = (R > 255)?255:R;
            image[i][j].rgbtGreen = (G > 255)?255:G;
        }
    }
    return;
}
