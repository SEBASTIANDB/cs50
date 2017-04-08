#include <stdio.h>
#include <cs50.h>
#include <math.h>


int getPositiveInteger(void);

int main(void)
{
   int bottles = 0;
   int Minutes = getPositiveInteger();
   printf("Minutes: %i\n", Minutes);
   bottles = ((Minutes * 1.5) * 128) / 16;
   printf("Bottles: %i\n", bottles);

}

int getPositiveInteger(void)
{
    int x = 0;
    do
    {
        printf("how many minutes did you shower ? \n");
        x = get_int();
    }while(x < 0);//keep asking until x is positive
    
    return x;
}

