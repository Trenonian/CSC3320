#include <stdio.h>

int main(int argc, char** argv) {
  if (argc < 2)
  {
    printf("Please include valid file as an argument.\n");
    return 1;
  }
  FILE *inputFile;
  inputFile = fopen(argv[1], "r");
  if (inputFile == NULL)
  {
    printf("%s is not a valid file.\n", argv[0]);
    return 1;
  }
  const int CAPS_DIFF = ('a' - 'A');
  const int A_CHAR = 'A';
  const int Z_CHAR = 'Z';
  int letters[26] = {0};
  int character;
  int most = 0;
  int mostPosition = -1;
  do
  {
    character = fgetc(inputFile);
    character = (character > Z_CHAR) ? (character - CAPS_DIFF) : character;
    if ( character >= A_CHAR && character <= Z_CHAR )
    {
      int position = character - A_CHAR;
      letters[position] += 1;
      int count = letters[position];
      if (count > most)
      {
        most = count;
        mostPosition = position;
      }
    }
  } while (character != EOF);
  printf("The most frequent letter is '%c'. It appeared %d times.\n", mostPosition+A_CHAR, most);
  return 0;
}
