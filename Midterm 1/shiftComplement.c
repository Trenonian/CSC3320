#include <stdio.h>

/*
 * Name: Michael Anderson
 * Student Email: manderson113@student.gsu.edu
 */

int main(int argc, char *argv[])
{
  int num = atoi(argv[1]);
  int result = (num<<3) + ~num;
  printf("%d<<3 = %d\n", num, num<<3);
  printf("~%d = %d\n", num, ~num);
  printf("(%d<<3)+~%d = %d\n", num, num, result); 
  return result;
}

