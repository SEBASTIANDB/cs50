#include <stdio.h>
#include <cs50.h>
#include <math.h>


int GetPositiveInteger(void);

int main(void){
 int spaces = 0;//number of spaces
 int hashes = 0;//number of hashhes

 printf("Input:\n");
 int c = GetPositiveInteger();
 for (int i = 1; i<=c; i++) {
  hashes = i + 1;
  spaces = c-hashes+1;
  printf("%.*s", spaces, "                                          ");
  printf("%.*s", hashes, "############################################");//hashes = precision, ################### is argument that has to be formatted
  printf("\n");
}
}
int GetPositiveInteger(void){
  int x;
  do{
   printf("Height?\n");
   x = GetInt();
  }
  while (x < 0 || x >= 24); 
  return x; 

}