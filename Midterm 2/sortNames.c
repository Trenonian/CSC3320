#include <stdio.h>

/*
 * Name: Michael Anderson
 * Student Email: manderson113@student.gsu.edu
 */

// simple enum for the sorting order
typedef enum sorting
{
	ascending = 1,
	descending = 2
} sorting;

// returns the sorting order derived from
sorting getOrder(char*);

// sorts the array
// (pointer to array, size of array, desired order)
void sort_alphabetic(char**, size_t, sorting);

// sorts the array using quicksort
void quicksort(char**, char**, char**, sorting);

// returns the location of the pivot
// all elements to the left are lower than ray[pivot]
// all elements to the right are higher than ray[pivot]
char** partition(char**, char**, char**, sorting);

// swaps two strings
void swap(char**, char**);

// prints the given array
void print_array(char**, size_t);

// the +1 is for the null character '\0'
#define MAX_NAME_SIZE 20 + 1

void main(int argc, char *argv[])
{
	char* evalArray[] = {
		"Systems",
		"Programming",
		"Deep",
		"Learning",
		"Internet",
		"Things",
		"Robotics",
		"Course"
	};

	char** evalArrayPointer = evalArray;
	size_t size = (sizeof(evalArray))/(sizeof(evalArray[0]));

	int inputProvided = 0;
	sorting order = 0;

	// attempts to read the desired sorting order from the command line arguments
	if (argc > 1) {
		order = getOrder(argv[1]);
	}

	// if the desired order couldn't be discerned, ask user
	while (!order)
	{
		char input[1];
		printf("(A)scending or (D)escending? ");
		scanf("%s",  input);
		order = getOrder(input);
	}
	
	printf("\nUnsorted array:\n");
	print_array(evalArrayPointer, size);

	sort_alphabetic(evalArrayPointer, size, order);

	if (order == ascending) {
		printf("Ascending:\n");
	} else {
		printf("Descending:\n");
	}

	print_array(evalArrayPointer, size);
}

sorting getOrder(char* str)
{
	sorting order = 0;
	size_t i = 0;
	// skip past '-' in the cases of '-a' or '-d'
	if (str[0] == '-') {
		i++;
	}
	if (str[i] == 'a' || str[i] == 'A') {
		order = ascending;
	} else if (str[i] == 'd' || str[i] == 'D') {
		order = descending;
	}
	return order;
}

void sort_alphabetic(char** ray, size_t size, sorting order)
{
	// pass the array, the location of the first element,
	// the location of the last element, and the desired order
	quicksort(ray, ray, ray+size-1, order);
}

void quicksort(char** ray, char** low, char** high, sorting order)
{
	if (low >= high) { return; } // nothing to sort here
	
	// after this, the pivot will be in the right place,
	// with everything else being in the correct 'half'
	char** pivot = partition(ray, low, high, order);

	// sort each 'half'
	quicksort(ray, low, pivot-1, order);
	quicksort(ray, pivot+1, high, order);
}

char** partition(char** ray, char** low, char** high, sorting order)
{
	// use the last element in this section as the pivot
	char* pivotValue = *high;
	char** pivotIndex = low;
	char** index;
	// work from the left,
	// making sure everything to the left of the pivotIndex should be there
	// swaps if it needs to
	for (index = low; index <= high; index++)
	{
		int cmp = strcasecmp(*index, *high);
		if ((order == ascending && cmp<0) || (order == descending && cmp>0))
		{
			swap(index, pivotIndex);
			pivotIndex++;
		}
	}
	swap(pivotIndex, high);
	return pivotIndex;
}

void swap(char** a, char** b)
{
	char* temp = *a;
	*a = *b;
	*b = temp;
}

void print_array(char** ray, size_t size)
{
	if (size <= 0) { return; }
	char **p;
	for (p = &ray[0]; p < &ray[size]; p++)
	{
		printf("%s\n", *p);
	}
	printf("\n");
}
