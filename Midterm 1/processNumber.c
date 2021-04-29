#include <stdio.h>
#include <math.h>

/*
 * Name: Michael Anderson
 * Student Email: manderson113@student.gsu.edu
 */

#define true 1
#define false 0

int main(int argc, char *argv[])
{
  char *digits = argv[1];
  int num = atoi(digits);
  int result = (num<<3) + ~num;
  printf("(%d<<3) + ~(%d) = %d\n", num, num, result); 
  
  size_t size = strlen(digits);
  int isBinary = true;
  int negative = (num < 0);
  int binToDec=0;
  int power=0;
  int i;
  int start = negative ? 1 : 0;
  for (i=strlen(digits)-1; i>=start && isBinary; i--)
  {
    char digit = digits[i];
    if (digit == '1')
    {
      binToDec += (int) pow(2,power);
    }
    else if (digit != '0')
    {
      isBinary = false;
    }
    power++;
  }

  if (isBinary)
  {
    printf("%db = %s%dd\n",
      num,
      negative ? "-" : "",
      binToDec);
  }
  
  power=0;
  int* decToBin[32];
  for(i=31; i>=0; i--)
  {
    decToBin[31-i]=((num>>i) & 1);
  }
  i=0;
  while (decToBin[i]==0)
  {
    i++;
  }
  printf("%dd = ", num);
  while (i<32)
  {
    printf("%d",decToBin[i]);
    i++;
  }
  printf("b\n");

  return 0;
}

