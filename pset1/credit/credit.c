#include <stdio.h>
#include <cs50.h>

int digit(long n); //Returns number of digits in a long
bool isvalid(long n); //Returns true if number passes Luhn's Algorithm

int main(void)
{
    long card;
    card = get_long("Number: ");
    int length = digit(card);
    //Ignores numbers of incorrect sizes
    if(length!=13 && length!=15 && length!=16){
        printf("INVALID\n");
        return 0;
    }
    //Ignores numbers which fail Luhn's Algorithm
    if(!isvalid(card)){
        printf("INVALID\n");
        return 0;
    }
    //Only AMEX cards have a length of 15
    if(length==15){
        //Extracts front 2 digits
        card /= 1e13;
        //Ensures front 2 digits match AMEX
        if(card==34 || card==37){
            printf("AMEX\n");
            return 0;
        }
        else{
            printf("INVALID\n");
            return 0;
        }
    }
    //Only VISA cards have length 13
    if(length==13){
        //Extracts front digit
        card /= 1e12;
        //Ensures front digit matches VISA
        if(card==4){
            printf("VISA\n");
            return 0;
        }
        else{
            printf("INVALID\n");
            return 0;
        }
    }
    //Both Visa and Mastercard cards have a length of 16
    if(length==16){
        //Extracts front 2 digits
        card /= 1e14;
        //Checks if matches mastercard options outlined in spec
        if(card==51 || card==52 || card==53 || card==54 || card==55){
            printf("MASTERCARD\n");
            return 0;
        }
        //Checks if front digit matches Visa
        else if((card/10)==4){
            printf("VISA\n");
            return 0;
        }
        else{
            printf("INVALID\n");
            return 0;
        }
    }
    printf("ERROR\n");
    return 1;
}

int digit(long n)
{
    int count = 0;
    //Continues to loop whilst n!=0, incrementing count for each digit included in n
    while(n){
        count++;
        n /= 10;
    }
    return count;
}

bool isvalid(long n)
{
    int digit, sum = 0; //Because otherwise the -Werror flag cucks me (pretty sure the default intialised values are the same as in c++ = 0)
    int i = 1;
    //Loops through each digit of n, adding it to sum following Luhn's Algorithm
    while(n){
        digit = n%10;
        if(i%2){
            sum += digit;
        }
        else{
            digit *= 2;
            //Adds digits of product to sum, not product itself
            while(digit){
                sum += digit%10;
                digit /= 10;
            }
        }
        n /= 10;
        i++;
    }
    //Checks if sum ends with 0;
    if(sum%10==0){
        return true;
    }
    else{
        return false;
    }
}