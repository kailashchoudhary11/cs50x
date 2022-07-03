// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

int count = 0;
bool isLoaded = false;
// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    int hashValue = hash(word);

    node *tmp = table[hashValue];

    while (tmp != NULL)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    char cpy[LENGTH + 1];
    strcpy(cpy, word);
    for (int i = 0; i < strlen(cpy); i++)
    {
        cpy[i] = tolower(cpy[i]);
    }

    int hashValue = (int)(cpy[0] - 97) % N;
    return hashValue;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *fptr = fopen(dictionary, "r");

    char word[LENGTH + 1];

    if (fptr == NULL)
    {
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    while (fscanf(fptr, "%s", word) != EOF)
    {
        int hashValue = hash(word);

        node *tmp = malloc(sizeof(node));

        if (tmp == NULL)
        {
            return false;
        }

        strcpy(tmp->word, word);

        tmp->next = table[hashValue];
        table[hashValue] = tmp;
        count++;
    }
    fclose(fptr);
    isLoaded = true;
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (!isLoaded)
    {
        return 0;
    }

    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    for (int i = 0; i < N; i++)
    {
        node *tmp = NULL;
        while (table[i] != NULL)
        {
            tmp = table[i]->next;

            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
