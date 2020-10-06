#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void); //Updated to include voter count to optimise performance -- UPDATE: NOT POSSIBLE >:(

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for(int i = 0; i < candidate_count; i++){
        if(strcmp(candidates[i].name, name) == 0){
            candidates[i].votes++;
            return 1;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int max = 0;
    //Iterates through candidates to find the highest number of votes
    for(int i = 0; i < candidate_count; i++){
        if(candidates[i].votes > max){
            max = candidates[i].votes;
        }
        /*
        if(max>(voter_count/2)){ //If a candidate has more than half the available votes they must be the only winner
            printf("%s\n", candidates[i].name);
            return;
        }
        Can't include additional parameters into the declaration of print_winner without check50 breaking ;(
        RIP my optimisation
        */
    }
    //Prints any candidates who's vote total matches the maximum number of votes
    for(int i = 0; i < candidate_count; i++){
        if(candidates[i].votes == max){
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}

