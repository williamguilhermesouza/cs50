// Implements a dictionary's functionality

#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
# include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// global variable for size
int size_l = 0;

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

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int hashed = hash(word);
    node *n = table[hashed];
    if (strcasecmp(word, n->word) == 0)
    {
        return true;
    }

    while (n->next != NULL)
    {
        n = n->next;

        if(strcasecmp(word, n->word) == 0)
        {
            return true;
        }


    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;

    hash = tolower(word[0]) - 97;

    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char *buffer = malloc(LENGTH);
    if (buffer == NULL)
    {
        return false;
    }

    while (fscanf(file, "%s", buffer) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, buffer);
        size_l++;

        int hashed = hash(buffer);
        n->next = table[hashed];
        table[hashed] = n;

    }
    fclose(file);
    free(buffer);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return size_l;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *tmp;
    node *cursor;

    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        tmp = cursor;

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
        free(cursor);
    }
    return true;
}
