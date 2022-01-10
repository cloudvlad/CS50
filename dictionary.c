// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>// For strcasecmp()
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
const unsigned int N = 26;

// Hash table
node *table[N];

int d_counter = 0;// Dictionary counter

// Hashes word to a number
unsigned int hash(const char *word)
{
    return (int)tolower(word[0]) - 97;
}


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int bi = hash(word);

    node *cur = table[bi];

    FILE *endfile = fopen("stats.txt", "w");
    while (cur != NULL)
    {
        if (strcasecmp(cur->word, word) == 0)
        {
            fclose(endfile);
            return true;
        }
        cur = cur->next;
    }

    fprintf(endfile, "%s\n", word);
    fclose(endfile);
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *d_file = fopen(dictionary, "r");
    if (d_file == NULL)
    {
        printf("No such file\n");
        return false;
    }

    char word[LENGTH + 1];

    for (int i = 0; i < N; i++)
    {
        printf("%s", (char *)table[i]);
    }

    unsigned int bi;// Bucket index

    while (fscanf(d_file, "%s", word) != EOF)
    {
        struct node *n = (node *)malloc(sizeof(node));// Create node
        if (n == NULL)
        {
            printf("No nodes\n");
            return false;
        }

        strcpy(n->word, word);

        bi = hash(word);// Hash the word

        n->next = table[bi];
        table[bi] = n;

        d_counter = d_counter + 1;

    }

    fclose(d_file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return d_counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *cur = NULL;

    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            cur = table[i]->next;
            free(table[i]);
            table[i] = cur;
        }
    }

    return true;
}
