#include <cs50.h>
#include <stdio.h>
#include<string.h>

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
bool check_cycle(int winner, int loser);

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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            //printf("Candidate: %s, Rank: %i\n", candidates[i], ranks[rank]);
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO

    //int length = (&ranks)[1] - ranks;//sizeof(ranks) / sizeof(ranks[0]);
    //printf("Length of Ranks: %i\n", candidate_count);

    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i; j < candidate_count; j++)

        {
            if (ranks[i] != ranks[j])
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
                // Update "pair" according to preferences count
                // and increment "pair_count"
            {
                pairs[pair_count].winner =  i;
                pairs[pair_count].loser = j;
                pair_count ++;
            }
            else if (preferences[i][j] < preferences [j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count ++;
            }

        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int vote_strength[pair_count];

    // Create vote strength array based on preferences
    for (int i = 0; i < pair_count; i++)
    {
        vote_strength[i] = preferences[pairs[i].winner][pairs[i].loser];
    }


    // Selection Sort based on vote strength
    int i, j;
    for (i = 0; i < pair_count; i++)
    {
        int max = vote_strength[i], max_index = i;
        bool swap = false;
        for (j = i + 1; j < pair_count; j++)
        {
            if (max < vote_strength[j])
            {
                max = vote_strength[j];
                max_index = j;
                swap = true;
            }
        }

        if (swap)
        {
            int temp = vote_strength[i];
            vote_strength[i] = max;
            vote_strength[max_index] = temp;
            pair temp2 = pairs[i];
            pairs[i] = pairs[max_index];
            pairs[max_index] = temp2;
        }

    }
    return;
}

bool check_cycle(int winner, int loser)
{
    bool status = true;

    // Continue searching for pairs until condition is satisfied
    while (status && winner != loser)
    {
        bool check = false;
        for (int i = 0; i < candidate_count; i++) //For all candidates
        {
            if (locked[i][winner] == true) // If the pair is already locked
            {
                check = true;
                winner = i; // Update winner to backtrack
            }

        }

        if (!check) // If no locked pair is found
        {
            status = false;
        }
    }

    if (winner == loser) // If the cycle is present
    {
        return true;
    }

    return false;

}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    for (int i = 0; i < pair_count; i++)
    {
        int loser = pairs[i].loser, winner = pairs[i]. winner;
        if (!check_cycle(winner, loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;

        }
    }
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        bool check_rows = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                check_rows = false;
                break;
            }
        }

        if (check_rows == true)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}