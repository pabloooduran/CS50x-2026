// Implements a dictionary's functionality
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 5000;

//Number of words in the dictionary
unsigned int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int index = hash(word);
    node *p = table[index];
    while (p != NULL)
    {
        if (strcasecmp(p->word, word) == 0)
            return true;
        p = p->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int value = 0;

    for (int i = 0; word[i] != '\0'; i++)
        value = value * 31 + tolower(word[i]);

    return value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
        return false;
    char buffer[LENGTH + 1];
    while (fscanf(file, "%s", buffer) != EOF)
    {
        node *p = malloc(sizeof(node));
        if (p == NULL)
        {
            return false;
        }
        strcpy(p->word, buffer);
        p->next = NULL;
        unsigned int index = hash(buffer);
        p->next = table[index];
        table[index] = p;
        word_count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node* next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }
    return true;
}
