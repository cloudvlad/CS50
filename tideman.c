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
bool check_cycle(int w, int l);

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
    // And restart voter's preferences counter
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
    if (rank == 0)
    {
        // Give on every voting position -1 index (not )
        for (int i = 0; i < candidate_count; i++)
        {
            ranks[i] = -1;
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            for (int j = 0; j < candidate_count; j++)
            {

                //If the person is already voted for this person
                if (ranks[j] == i)
                {
                    printf("\nAlready voted for this candidate!\n");
                    return false;
                }
            }
            ranks[rank] = i;
            return true;
        }
    }


    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (i == j)
            {
                continue;
            } //No one prefer one candidate over themself

            preferences[ranks[i]][ranks[j]] += 1;
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {

            printf("%d ", preferences[i][j]);
        }
        printf("\n");
    }



    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (i == j)
            {
                continue;
            }

            if (preferences[i][j] >= preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
            }
            else
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
            }
            pair_count = pair_count + 1;
        }
    }
    printf("\nUnsorted pairs:\n");
    for (int i = 0; i <  pair_count; i++)
    {
        printf("(%d - %d) = %d\n", pairs[i].winner, pairs[i].loser, preferences[pairs[i].winner][pairs[i].loser]);
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair winner_swap, loser_swap;
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                winner_swap = pairs[i];
                loser_swap = pairs[i];

                pairs[i] = pairs[j];
                pairs[i] = pairs[j];

                pairs[j] = winner_swap;
                pairs[j] = loser_swap;
            }
        }
    }

    printf("\nSorted pairs:\n");
    for (int i = 0; i <  pair_count; i++)
    {
        printf("(%d - %d) = %d\n", pairs[i].winner, pairs[i].loser, preferences[pairs[i].winner][pairs[i].loser]);
    }


    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int w = pairs[i].winner;//winner
        int l = pairs[i].loser;//loser


        if (!check_cycle(w, l))
        {
            locked[w][l] = true;
        }
        else
        {
            locked[w][l] = false;
        }
    }


    for (int i = 0; i < candidate_count; i++)
    {
        printf("\n");
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                printf("t ");
            }

            if (locked[i][j] == false)
            {
                printf("f ");
            }
        }
    }
    return;
}

// If it sees node, that it pass before, means there is a cycle
bool check_cycle(int w, int l)
{
    if (w == l)
    {
        return true; //There is cycle
    }

    for (int c = 0; c < candidate_count; c++) //Che
    {
        if (locked[c][w])
        {
            if (check_cycle(c, l))
            {
                return true;
            }
        }
    }
    return false; //There is no cycle
}




// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                break;
            }

            if (j == (candidate_count - 1))
            {
                printf("\n%s\n", candidates[i]);
            }
        }
    }
    return;
}







/*for(int i = 0; i < candidate_count; i++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
            if(locked[i][j]==true)
            {
                printf("t ");
            }

            if(locked[i][j]==false)
            {
                printf("f ");
            }
        }
        printf("\n");
    }//SHOW LOCKED PAIRS*/



