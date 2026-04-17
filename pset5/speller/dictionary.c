// Author: Marko Solajic
// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
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
const unsigned int N = 143000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *cursor = table[index];
    if (cursor == NULL)
    {
        return false;
    }
    while (strcasecmp(word, cursor->word) != 0)
    {
        cursor = cursor->next;
        if (cursor == NULL)
        {
            return false;
        }
    }
    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long sum = 0;
    const int constant = 7;
    unsigned long var = 1;
    // TODO: Improve this hash function
    for (int i = 0; i < strlen(word); i++)
    {
        sum += toupper(word[i]) * var;
        var *= constant;
    }
    return sum % N;
}

int dict_size = 0;
bool loaded = false;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        loaded = false;
        return false;
    }

    // Read each word in the file
    char word[LENGTH + 1];
    while (fscanf(source, "%s", word) != EOF)
    {
        // Add each word to the hash table
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(source);
            loaded = false;
            return false;
        }
        strcpy(new_node->word, word);
        int index = hash(word);
        new_node->next = table[index];
        table[index] = new_node;
        dict_size += 1;
    }

    // Close the dictionary file
    fclose(source);
    loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (loaded == true)
    {
        return dict_size;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *cursor;
    node *tmp;
    // TODO
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        tmp = table[i];
        while (cursor != NULL)
        {
            cursor = cursor->next;
            if (tmp == NULL)
            {
                return false;
            }
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
