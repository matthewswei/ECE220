/*
  This program calculates the values in a row of Pascal's Triangle given a user input for which row to print out.
  The first row is 0, the second is 1, the third is 2, etc.
  Algorithm:
    Used binomial coefficeint to caluclate the value of a certain position in the row. Specifically n!/(k!(n-k)!)
    where n is the row number and k is the position in the row currently being printed. The equation is put through
    a for loop and stops once it reaches the row value. There is an exception at its inital condition at k = 0, so 
    that was taken into account in this program as well.

  Matthew Shuyu Wei
  partners: mswei2, bmaedge2
  Febuary 12, 2022

*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
  //Initializes variables
  int row;  //Row is n in equation
  unsigned long num = 1;

  //Gets which row to print from user
  printf("Enter a row index: ");
  scanf("%d",&row);

  for (int i=0; i<=row; i++) {
    //Prints 1 for first value in row
    if (i==0) {
      printf("1 ");
      continue;
    }
    //Calculates and prints number at the ith position (k in equation)
    num = num*(row + 1 - i)/i;
    printf("%lu ", num);
  }

  return 0;
}
