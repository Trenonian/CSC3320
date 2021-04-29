#include <stdio.h>

/*
 * Name: Michael Anderson
 * Student Email: manderson113@student.gsu.edu
 */

int main(void)
{
  int firstThree, secondThree, lastFour;
  printf(“Enter phone number [(999)999-9999]: “);
  scanf(“(%d)%d-%d”, &firstThree, &secondThree, &lastFour);
  printf(“You entered %d-%d-%d\n”, firstThree, secondThree, lastFour);
}
