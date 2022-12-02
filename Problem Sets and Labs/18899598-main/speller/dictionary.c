// Implements a dictionary's functionality
#include<stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include<string.h>
#include<strings.h>

#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
//MAX length of a word= 45, max value of word = 'Z' = 90
//highest sum of characters in word that can be achieved = 45 * 90 = 4050
const unsigned int N = 4050;

// Hash table
node *table[N];

void printing();

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int start_point = hash(word); // Get the initial pointer of a linked list from hash table
    node *starting_thread = table[start_point]; //initialize the pointer for the linked list

    while (starting_thread != NULL)
    {
        //Traversing the linked list to check if word is present
        if (strcasecmp(starting_thread -> word, word) == 0) //compare withoud being sensitive to cases.
        {
            return true;
        }
        //next node
        else
        {
            starting_thread = starting_thread -> next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int sum = 0;
    int n = strlen(word);
    //Take sum of all integer values of the characters present in a word
    for (int i = 0; i < n; i++)
    {
        sum = sum + (int)toupper(word[i]);
        //printf("word= %d, sum = %d\n", word[i], sum);
    }
    // Return the sum for the integer value of characters
    //Linked list will be created for all words having same "sum" at same index of table.
    return sum;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the file
    FILE *raw = fopen(dictionary, "r");

    // Initialize single word to max length in order to save it in hash map
    char single_word[LENGTH + 1];

    int count = 1;
    // Check if file is read correctly or not
    if (raw == NULL)
    {
        printf("ERROR\n");
        return false;
    }
    else
    {
        //while (fgets(single_word, LENGTH + 1, raw))

        // fscanf() get us the stream till new word or end of file (EOF)
        while (fscanf(raw, "%s", single_word) == 1) // && count < 553)
        {
            //printf("Count: %d, LEN: %lu, %s\n",count, strlen(single_word), single_word);
            count++;

            //initialize temp node for storing single word
            node *temp = malloc(sizeof(node));
            if (temp == NULL)
            {
                return false;
            }

            // use function strcpy as the string cannot be directly assigned.
            strcpy(temp -> word, single_word);
            // if not initialized to NULL gives valgrind error.
            temp -> next = NULL;

            // hash() gives us the entry point to linked list out of 26 different linked list
            int hash_point = hash(single_word);
            //printf("LOAD-> hash_point = %u, word = %s\n", hash_point, single_word);

            //For initial thread creation for each hash point (total 26)
            if (table[hash_point] == NULL)
            {
                table[hash_point] = temp;

            }
            else
            {
                //Inserting node at start as inserting node at end takes traversal of complete linked list.
                temp -> next = table[hash_point];
                table[hash_point] = temp;
            }
        }
        //printing();
        fclose(raw);
        return true;
    }
    return false;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    //node *counting = table[0];
    long int count = 0;

    for (int i = 0; i < N; i++)
    {
        //initialize node
        node *counting = table[i];
        while ((counting != NULL))
        {
            count++;
            //printf("COUNT= %ld, %s\n",count, counting -> word);
            //counting moves to next element till NULL in each of the 26 threads
            counting = counting -> next;
        }
    }
    //printf("\n*****\nCOUNT= %ld\n*****\n", count);
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        // For each of the 26 thread we have to free the nodes
        while (table[i] != NULL)
        {
            //Move a step ahead before freeing the current node
            node *temp1 = table[i] -> next;
            //Free current node
            free(table[i]);
            //Assign next node to current node
            table[i] = temp1;
        }
    }


    // Check if all nodes in table[26] are NULL
    for (int i = 0; i < N; i++)
    {
        if (table[i] == NULL)
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}


//Prints the linked list loaded in memory by traversing the complete linked list
// in each of the 26 thread.
void printing(node *table_1)
{
    int count = 1;
    for (int i = 0; i < N; i++)
    {
        node *printing = table[i];

        //If the table[i] is NULL i.e no linked list is present for this thread
        if (table[i] == NULL)
        {
            printf("At i=%d -> NULL\n", i);
        }

        else
        {
            while (printing != NULL)
            {
                printf("count= %d, I= %d, %s\n", count, i, printing -> word);
                printing = printing -> next;
                count++;
            }
        }
    }
    return;
}
