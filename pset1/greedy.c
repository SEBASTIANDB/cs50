#include <stdio.h>
#include <cs50.h>
#include <math.h>

float GetPositiveFloat(void)
{
 float n;
    do
    {
        printf("O hai, ow much is owed ?");
       n = GetFloat();
    }
   while (n < 0);
    return n;
}

int main(void)
{
    int coins = 0;
  
    
    printf("How much change is owed? \n");
    float c = GetPositiveFloat();
    int change = round(c * 100);
    

    while(change % 25 >= 0 && change >= 25 && change > 0){
        change -= 25;
        coins++;
    }
    
     while(change % 10 >= 0 && change >= 10 && change > 0){
        change -= 10;
        coins++;
    }
    
     while(change % 5 >= 0 && change >= 5 && change > 0){
        change -= 5;
        coins++;
    }
    
    while(change % 1 == 0 && change >= 1 && change > 0){
        change -= 1;
        coins++;
    }
    

printf("%i\n",coins);
    
}
