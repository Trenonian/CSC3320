#include <stdio.h>
#include <string.h>

/* Name: Michael Anderson
 * Student Email: manderson113@student.gsu.edu
 */

char* strcpy (char*, const char*);

int main()
{
	const int wordSize = 20+1;
	char smallest_word[wordSize];
	char largest_word[wordSize];
	char input_word[wordSize];
	int first = 1;
	while (1)
	{
		printf("Enter a word: ");
		scanf("%s", input_word);
		if (first || strcmp(input_word, smallest_word) < 0)
		{
			strcpy(smallest_word, input_word);
		}
		if (first || strcmp(input_word, largest_word) > 0)
		{
			strcpy(largest_word, input_word);
		}
		first = 0;
		if (strlen(input_word) == 4) { break; }
	}
	printf("\n");
	printf("Smallest word: %s\n", smallest_word);
	printf("Largest word: %s\n", largest_word);
}

char* strcpy (char* strDest, const char* strSrc)
{
	int i=0;
	while (strSrc[i] != '\0')
	{
		strDest[i] = strSrc[i];
		i++;
	}
	strDest[i] = '\0';
	return strDest;
}
