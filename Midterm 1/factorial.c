#include <stdio.h>

/*
 * Name: Michael Anderson
 * Student Email: manderson113@student.gsu.edu
 */

unsigned long factorial(int num)
{
  if (num <= 1)
    return 1;
  return num*factorial(num-1);
}

int main(int argc, char *argv[])
{
  int num = atoi(argv[1]);
  num = (num < 0) ? 0 : num;
  unsigned long fac = factorial(num);
  printf("%d! = %ld\n", num, fac);
  return fac;
}

