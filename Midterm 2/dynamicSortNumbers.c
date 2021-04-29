#include <stdio.h>
#include <stdlib.h>

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
void sort_numeric(double*, size_t, sorting);

// sorts the array using quicksort
void quicksort(double*, double*, double*, sorting);

// returns the location of the pivot
// all elements to the left are lower than ray[pivot]
// all elements to the right are higher than ray[pivot]
double* partition(double*, double*, double*, sorting);

// swaps two elements in an array of doubles
void swap(double*, double*);

// prints the given array
void print_array(double*, size_t);

void main(int argc, char *argv[])
{
	const size_t INITIAL_COUNT = 10;
	const double GROWTH_FACTOR = 1.5;

	double *ray;
	size_t max_size = INITIAL_COUNT;
	ray = malloc(max_size * sizeof(double));
	size_t size = 0;

	printf("Please enter any amount of doubles, 0 to quit:\n");

	size_t index = 0;
	double val = 0;
	do
	{
		scanf("%lf",&val);
		if (val != 0)
		{
			ray[index] = val;
			index++;
			size++;
			if (size >= max_size)
			{
				max_size *= GROWTH_FACTOR;
				double *newray = (double*)realloc(ray, max_size * sizeof(double));
				if (newray == NULL)
				{
					printf("Error allocating memory\n");
					return;
				} else {
					ray = newray;
				}
			}
		}
	} while (val != 0);

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
	
	//printf("\nUnsorted array:\n");
	//print_array(ray, size);

	if (order == ascending) {
		printf("Ascending:\n");
		sort_numeric(ray, size, ascending);
	} else {
		printf("Descending:\n");
		sort_numeric(ray, size, descending);
	}

	print_array(ray, size);
	free(ray);
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

void sort_numeric(double* ray, size_t size, sorting order)
{
	// pass the array, the location of the first element,
	// the location of the last element, and the desired order
	quicksort(ray, ray, ray+size-1, order);
}

void quicksort(double* ray, double* low, double* high, sorting order)
{
	if (low >= high) { return; } // nothing to sort here
	
	// after this, the pivot will be in the right place,
	// with everything else being in the correct 'half'
	double* pivot = partition(ray, low, high, order);
	// sort each 'half'
	quicksort(ray, low, pivot-1, order);
	quicksort(ray, pivot+1, high, order);
}

double* partition(double* ray, double* low, double* high, sorting order)
{
	// use the last element in this section as the pivot
	double pivotValue = *high;
	double* pivotIndex = low;
	double* index;
	// work from the left,
	// making sure everything to the left of the pivotIndex should be there
	// swaps if it needs to
	for (index = low; index <= high; index++)
	{
		if ((order == ascending && *index < pivotValue) || (order == descending && *index > pivotValue))
		{
			swap(index, pivotIndex);
			pivotIndex++;
		}
	}
	swap(pivotIndex, high);
	return pivotIndex;
}

void swap(double* a, double* b)
{
	double temp = *a;
	*a = *b;
	*b = temp;
}

void print_array(double* ray, size_t size)
{
	if (size <= 0) { return; }
	double* p;
	for (p = ray; p<&ray[size]; p++)
	{
		printf("%f\n", *p);
	}
	printf("\n");
}
