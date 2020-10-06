#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int index(float L, float S); //Returns Coleman-Liau index

int main(void)
{
    string text = get_string("Text: ");
    int letters = 0, sentences = 0, words = 0; //I might stop using make soon... default initialisation is 0

    //For loop iterates through text, includes delimiting '\0' to count final word
    for(int i=0; i<=strlen(text); i++){
        char iter = text[i];
        //If alphabetical char, increments letters
        if((iter >= 'a' && iter <= 'z') || (iter >= 'A' && iter<= 'Z')){
            letters++;
        }
        //If space, increments words (added EOS and newline functionality for final word / new paragraphs)
        if(iter == ' ' || iter == '\0' || iter == '\n'){
            words++;
        }
        //If relevant punctuation, increments sentences
        if(iter == '.' || iter == '?' || iter == '!'){
            sentences++;
        }
    }

    printf("Letters: %i\nSentences: %i\nWords: %i\n", letters, sentences, words);

    //Calculates average letters and words per 100 words
    float L = (float) letters/ (float) words * 100;
    float S = (float) sentences/ (float) words * 100;
    int grade = index(L, S);

    //Output matching spec
    if(grade < 1){
        printf("Before Grade 1\n");
        return 0;
    }
    else if(grade > 16){
        printf("Grade 16+\n");
        return 0;
    }
    else{
        printf("Grade %i\n", grade);
    }
}

int index(float L, float S)
{
    return round(0.0588 * L - 0.296 * S - 15.8);
}