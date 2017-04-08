#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
 
 
int main(int argc, string argv[])
{
    
    
    if (argc != 2)
    {
        printf("need exactly one argument as key\n");
        return 1;
    }
    int place = 0;
    string k = argv[1];//argument
    int count = strlen(k);//length of argument

    // argument needs to be completely alphabetic
    for (int c = 0; c < count; c++)
    {
        if (!isalpha(argv[1][c]))//iterate over every character of the argument
        {
            printf("Error: enter an alphabetic key.\n");
            return 1;
        }
    }
    int key[count];//key with the same length as the length of the given argument
    
    for(int i = 0; i < count; i++)//iterate over every part of the argument and fill the key[]array with the right integers
    {   
        if(islower(k[i]))
        {
            key[i] = k[i] - 97;//these go inside key[]as integers.
        }
        if(isupper(k[i]))//these go inside key[]as integers.
        {
            key[i] = k[i] - 65;
        }
    }//key [] is now filled correctly but is not per sé the same length as the length of the input
    printf("plaintext: ");
    string input = GetString();//get input from user
    int inputlength = strlen(input);
    printf("ciphertext: ");
    for(int i = 0; i < inputlength; i++)//go over each letter of string
    {
        int c = 0;
        char charstring = input[i];
        
        
            if(islower(charstring))//lowercase case
            {
                c = (((int)charstring - 97)+ key[place]) % 26;//-97 because we need an alphabetical value for c
                c = c + 97;//so that we have the right ascii value
                printf("%c", (char)c);//115 = s, 114 = r, should be r (it doesn't overlap yet i think)

                
            }
            if(isupper(charstring))//uppercase case
            {
                c = (((int)charstring - 65)+ key[place]) % 26;//-65 because we need an alphabetical value for c
                c = c + 65;//so that we have the right ascii value
                printf("%c", (char)c);
                
            }
            else if (isalpha(charstring) == false)//if it's not alphabetical, print it out without modifying
            {
                printf("%c", (char)charstring);
            }
            place++;
            if(place == count)
            {
                place = 0;//reset place to 0 when place reaches the length of the key
                
            }
        
    }
    printf("\n");
    return 0;
    
}
