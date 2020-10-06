// Implements a dictionary's functionality

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 65536;

// Hash table
node *table[N] = {NULL};

//Counter that tracks number of words stored in dictionary
unsigned int size_of = 0;

void free_list(node *list)
{
    if(list->next != NULL){
        free_list(list->next);
    }
    free(list);
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //Creates a temporary string with lowercase characters
    char tmp[LENGTH + 1];
    strcpy(tmp, word);
    for(int i = 0; tmp[i]; i++){
        tmp[i] = tolower(tmp[i]);
    }
    //Now that characters are all lowercase the same hash can be found
    node *n = table[hash(tmp)];
    while(n != NULL){
        if(strcmp(tmp, n->word) == 0){
            return true;
        }
        if(strcmp(tmp, n->word) < 0){ //If word is smaller than word in dictionary and has found no matches -> not in dictionary
            return false;
        }
        n = n->next;
    }
    return false;
}

// Hashes word to a number using djb2 algorithm
unsigned int hash(const char *word)
{
    uint16_t h = 5381;
    unsigned const char *us;

    //Ensures elements of word are treated as >=0
    us = (unsigned const char *) word;

    while (*us != '\0'){
        h = ((h << 5) + h) + *us; /* hash * 33 + c */
        us++;
    }
    return h;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *in = fopen(dictionary, "r");
    if(in == NULL){
        return false;
    }
    int index = 0;
    char word[LENGTH + 1] = "";
    for (int c = fgetc(in); c != EOF; c = fgetc(in)){
        if(c != '\n'){
            word[index] = c;
            index++;
        }
        else{
            index = 0;
            int h = hash(word);
            node *tmp = table[h];
            if(tmp == NULL){
                node *w = malloc(sizeof(node));
                if(w == NULL){
                    return false;
                }
                strcpy(w->word, word);
                w->next = NULL;
                table[h] = w;
                size_of++;
                memset(word, 0, LENGTH + 1);
            }
            else{
                while(tmp->next != NULL){
                    tmp = tmp->next;
                }
                node *w = malloc(sizeof(node));
                if(w == NULL){
                    return false;
                }
                strcpy(w->word, word);
                w->next = NULL;
                tmp->next = w;
                size_of++;
                memset(word, 0, LENGTH + 1);
            }
        }
    }
    fclose(in);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return size_of;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for(int i = 0; i < N; i++){
        if(table[i] != NULL){
            free_list(table[i]);
        }
    }
    return true;
}
