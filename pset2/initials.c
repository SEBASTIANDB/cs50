#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    string s = GetString();//ask name
    
    printf("%c", toupper(s[0]));//print char of first letter of the name(char, touppercase)
    
    for (int i = 0,n = strlen(s);i < n;i++)//iterat
    {
        if(s[i] == ' '){
            printf("%c",toupper(s[i+1]));//print second char ,one place to the right of the space(char, touppercase)
        }
    }
    printf("\n");
}