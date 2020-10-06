#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
//Comparison function for qsort
int comp (const void *a, const void *b);
//Checks whether locked contains a cycle, depth tracks the numbers of edges traversed, should always called with 0
bool is_cyclic(int row, int depth);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        record_preferences(ranks);
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for(int i = 0; i < candidate_count; i++){
        if(strcmp(candidates[i], name) == 0){
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //Iterates through ranks in loosing order, updates all elements matching the looser's column
    for(int i = candidate_count-1; i >= 0; i--){
        for(int j = 0; j < candidate_count; j++){
            //If the element in the matching column of the row we are currently on is non-zero, it means we've looped through it before => looser
            if(preferences[j][j] == 0){
                preferences[j][ranks[i]]++;
            }
        }
    }
    //Resets all matching indices to 0 for next prefence evaluation
    for(int i = 0; i < candidate_count; i++){
        preferences[i][i] = 0;
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //Loops through preference array, skipping previously checked indices to add pairs
    for(int i = 0; i < candidate_count; i++){
        for(int j = i+1; j < candidate_count; j++){
            if(preferences[i][j] > preferences[j][i]){
                pairs[pair_count] = (pair){i, j};
                pair_count++;
            }
            else if(preferences[i][j] < preferences[j][i]){
                pairs[pair_count] = (pair){j, i};
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    qsort(pairs, pair_count, sizeof(*pairs), comp);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for(int i = 0; i < pair_count; i++){
        int a = pairs[i].winner;
        int b = pairs[i].loser;
        locked[a][b] = 1;
        if(is_cyclic(a, 0)){ //If a cycle is created, edge is removed
            locked[a][b] = 0;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    //The matching column of the winner of an election contains only 0s
    for(int j = 0; j < MAX; j++){
        bool w = 0;
        for(int i = 0; i < MAX; i++){
            if(locked[i][j]){
                w = 0;
                break;
            }
            w = 1;
        }
        if(w){
            printf("%s\n", candidates[j]);
            return;
        }
    }
    printf("Error: No winner found\n");
    return;
}

int comp (const void *a, const void *b)
{
    pair f = *((pair*)a);
    pair s = *((pair*)b);
    //Weighting of the victory for both pairs
    int w_f = preferences[f.winner][f.loser]-preferences[f.loser][f.winner];
    int w_s = preferences[s.winner][s.loser]-preferences[s.loser][s.winner];
    //We want descending order of strength
    if(w_f < w_s){
        return 1;
    }
    if(w_f > w_s){
        return -1;
    }
    return 0;
}

bool is_cyclic(int row, int depth)
{
    //If the recursion depth is greater than the maximum we must have a loop
    if(depth >= MAX){
        return true;
    }
    for(int j = 0; j < MAX; j++){
        if(locked[row][j]){
            if(is_cyclic(j, depth+1)){
                return true;
            }
        }
    }
    return false;
}