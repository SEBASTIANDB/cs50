/**
 * Implements a dictionary's functionality.
 */
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "dictionary.h"
#define SIZE 100000
bool loaded = false;

//make the node struct as seen in class
typedef struct node//every node has a word and a pointer to the next word.
{
    char word[LENGTH+1];
    struct node * next;
    
}
node;//call it node
//create an empty hastable to put words in.

node * hashtable[SIZE];

//next we need to make a hash function(where do we store/search for a word in the hashtable)

int hash(const char*word)
{
    int hash = 0;
    int n;
    for(int i = 0; word[i]!='\0'; i++){
        if(!isalpha(word[i])){//if it's not alpha
            n = 27;
        }else{
            n = word[i] - 'a' + 1;//normal case
        }
        hash = ((hash << 3) + n) % SIZE;
    }
    return hash;//return spot
}
int dicSize = 0;//pun intended, used to store length of dictionary
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    //create temp with enough length to store longest word possible , also for lowercase
    char temp[LENGTH];
    int lengthOfWord = strlen(word);
    for(int i = 0; i<lengthOfWord; i++){
        temp[i] = tolower(word[i]);
    }
    temp[lengthOfWord] = '\0';
    //find location of the word in the hashtable by using hash function to search
    int loc = hash(temp);
    if(hashtable[loc] == NULL){
        
        return false;
    }
    //go to the location to compare the given word to the word that's in the hashtable at [loc]
    node* cursor = hashtable[loc];
    
    while(cursor != NULL){
        if (strcmp(temp, cursor->word)==0)//if both words are the same. strcmp return 0 when equal
        {
          return true;//equal  
        }
        
        cursor = cursor ->next;//cursor goes to next.
        
        
    }
    
    return false;//word not equal/found
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)//load dictionary, return false if failed
{
    // TODO
    char word[LENGTH];
    FILE* file = fopen(dictionary, "r");
    if(file == NULL){
        loaded = false;
        return false;//file not found
    }
    loaded = true;
    //load words into the hash table with certain format (every word on a new line)
    while(fscanf(file, "%s\n",word) != EOF)
    {
        dicSize++;
        node * newWord = malloc(sizeof(node));//new word has size of node, there's no overhead
        //copy words
        strcpy(newWord->word, word);//copy to newWord from word
        //where should the word go in the hastable ?
        int location = hash(word);//again, using hash to search for the hash
        //if it's empty there, store it. if not, search for next place
        if(hashtable[location] == NULL)
        {
            hashtable[location] = newWord;
            newWord->next = NULL;//let it point to nothing yet
        }
        else//if it's occupied, store it in whatever that occupying word is pointing to
        {
            newWord->next = hashtable[location];
            hashtable[location] = newWord;
        }
            
    }
    fclose(file);//close dictionary
    return loaded;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if(!(dicSize < 0)){
       return dicSize;
    }
    else{
        return 0;
    }
    
}
/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)//go over the entire dictionary and free all the cursors
{
    // TODO
    int location = 0;
    while(location < SIZE)//just to make sure we free absolutely everything
    {
        if(hashtable[location] == NULL)//if it's empty, goto next, it's already empty
        {
            location++;
        }
        else if(hashtable[location] != NULL)
        {
            while(hashtable[location]!= NULL){
                node * cursor = hashtable[location];//assign cursor to this spot and free it
                hashtable[location] = cursor->next;//hashtable[location = cursor.next reset pointer so that it points to the next spot where cursor will pass
                free(cursor);//free cursor
            }
            location++;//next
        }
    }
    return true;
    
}
