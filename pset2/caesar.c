#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[]){
        
        
        //valid argc 
        if (argc != 2)
        {
            printf("Enter only one argument.");
            return 1;
        }
        // key for caesar cipher encryption (want a usable value) between 0 and 25 (26 letters in alphabet)
        int key = atoi(argv[1])%26;
        
        // get user input and store in string variable
        printf("plaintext: ");
        string crypt = GetString();
        
        string LowerCaseAlphabet = "abcdefghijklmnopqrstuvwxyz";//so that we can pick one from this "list"
        string UpperCaseAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";//so that we can pick one from this "list"
        
        
        if(key == 0)
        {
            printf("Key is invalid.");        
            
        }
        
        
        
        // make a loop that goes over each letter of your string
        printf("ciphertext: ");//flush output, don't want a new line
        for(int i = 0, n = strlen(crypt); i < n; i++)
        {
            if(isalpha(crypt[i]))
            {
                if(isupper(crypt[i]))
                {
                    //want to wrap around here if sum of char and key is greater than 26
                    printf("%c", UpperCaseAlphabet[(crypt[i] - 65 + key) % 26]);//caesar algorithm, also 65 is A, so -65 to be at the beginning of the string UpperCaseAlphabet
                }
                else
                {
                    //in case of lower case (pun intended)
                    printf("%c", LowerCaseAlphabet[(crypt[i] - 97 + key) %26]);
                }
            }
            else{
                //non-alphabetical characters have to stay the samen, such as exclamation etc
                printf("%c", crypt[i]);
            }
            
        }
        
        
    printf("\n");//doesn't work?
}
