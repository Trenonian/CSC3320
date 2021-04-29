#include<stdio.h>

/* Name: Michael Anderson
 * Student Email: manderson113@student.gsu.edu
 */

void split_time(long, int*, int*, int*);

int main()
{
	int n, hr, min, sec;
	printf("Enter seconds: ");
	scanf("%ld", &n);

	split_time(n, &hr, &min, &sec);

	printf("Converted format: %d hour %d mins %d secs\n",
		hr, min, sec);

	return 0;
}

void split_time(long total_sec, int *hr, int *min, int *sec)
{
	*hr = total_sec / 3600;
	total_sec %= 3600;
	*min = total_sec / 60;
	*sec = total_sec % 60;
}
