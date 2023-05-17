// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include<strings.h>
#include<stdlib.h>
#include<string.h>

#include "dictionary.h"
unsigned int sizenum;


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hashvalue=hash(word);
    node *tra=table[hashvalue];
    while(tra!=NULL)
    {
        if(strcasecmp(tra->word,word)==0)
        {
            return true;
        }
        else{
            tra=tra->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *infile = fopen(dictionary, "r");
    if (!infile)
    {
        printf("Error opening file!\n");
        return false;
    }

    char name[LENGTH+1];
    while (fscanf(infile, "%s", name) != EOF)
    {
        node *wordname=malloc(sizeof(node));
        if(wordname==NULL)
        {
            return false;
        }
        strcpy(wordname->word,name);
        int hashvalue=hash(name);

        if (table[hashvalue]==NULL)
        {
            wordname->next=NULL;
        }
        else
        {
            wordname->next=table[hashvalue];
        }
        table[hashvalue]=wordname;


        sizenum++;

    }
    fclose(infile);


    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return sizenum;
}



// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i=0;i<N;i++)
    {
        node* trav=table[i];

        while((trav->next)!=NULL)
        {
            node* temp=trav->next;
            free(trav);
            trav=temp;
        }

        free(trav);

    }

    return true;

}
