#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
    // Check the input name from the voter and if matching with a candidate, record it as the ith preference
    // Example: [Bob, Alice, Charlie] --> ranks[0] is 1, ranks[1] is 0, ranks[2] is 2
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i; // sets rank[0] to 1 --> [1, 0 , 2]
            return (true);
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Now we have the result from a voter, we have to record this into a 2d array somehow...
    // preferences[MAXi][MAXj] is the number of voters who prefer i over j
    // create empty preferences if not set yet
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] == NULL)
            {
                preferences[i][j] = 0;
            }
        }
    }
    
    // ranks = [2, 0, 1]
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    /* print for testing
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("preferences[%d][%d] is: %d\n",i,j,preferences[i][j]);
        }
    }
    */

    // return nothing because update to global var?
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // so we have a pairs[3] array because there is AB AC and BC
    // this should represent all the arrows on the graph (3)
    // the arrows have a sender and receiver aka winner and loser
    // so we need to loop over preferences[i][j] and construct into pairs[3]
    pair_count = 0;
    
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // do we still need to initialize the preferences array?
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// swap function for pair structs
void swap(pair *a, pair *b)
{
    pair temp = *a;
    *a = *b;
    *b = temp;
}

// Sort pairs in decreasing order by strength of victory

void sort_pairs(void)
{
    // fill array with winner preferences
    int strength[pair_count];

    for (int i = 0; i < pair_count; i++)
    {
        strength[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }

    //sorting function
    while (1)
    {
        int swapped = 0;

        for (int i = 0; i < pair_count - 1; i++)
        {
            for (int j = i + 1; j < pair_count; j++)
            {
                if (strength[i] < strength[j])
                {
                    //sorting pairs
                    pair tmp = pairs[i];
                    pairs[i] = pairs[j];
                    pairs[j] = tmp;

                    //sorting strength
                    int tmp2 = strength[j];
                    strength[j] = strength[i];
                    strength[i] = tmp2;
                }
            }
        }

        if (swapped == 0)
        {
            break;
        }
    }
    return;
}

// helper function for lock pairs
bool makes_circle(int cycle_start, int loser)
{
    if (loser == cycle_start)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (makes_circle(cycle_start, i))
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        // need check mechanism for loop before adding the TRUE tag
        if (!makes_circle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // we can loop over the locked pairs and the column that does not have a true is the source of the graph?
    for (int i = 0; i < candidate_count; i++)
    {
        int col_total = 0;
        int cand_index = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            col_total += (int) locked[j][i]; // reverse j and i because we want cols, not rows
        }
        if (col_total == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

