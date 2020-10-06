#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    //Ensures appropriate number of command-line argumanets are provided
    if(argc != 2){
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];
    //Ensures key is correctly sized
    if(strlen(key) != 26){
        printf("Key must contain 26 characters\n");
        return 1;
    }
    //Iterates through key, converting all characters to uppercase and ensureing no invalid characters were inputted
    for(int i = 0; i < 26; i++){
        if(!isalpha(key[i])){
            printf("Invalid key character at index: %i\n", i);
            return 1;
        }
        key[i] = toupper(key[i]);
        char *pos = strrchr(key, key[i]); //Finds last occurence of char in string
        if(pos!=&key[i]){ //If positions don't match, there must be a duplicate char in the key
            printf("Key contains duplicate character: %c\n", key[i]);
            return 1;
        }
    }
    //Prompts user for input
    string plain = get_string("plaintext: ");

    //Iterates through input, converting alphabetical characters based on input key
    for(int i = 0, n = strlen(plain); i < n; i++){
        char a = plain[i];
        if(isalpha(a)){
            if(isupper(a)){
                plain[i] = key[a-65];
            }
            else{
                plain[i] = tolower(key[a-97]);
            }
        }
    }
    printf("ciphertext: %s\n", plain);
}