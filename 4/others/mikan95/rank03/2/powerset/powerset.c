//shortest version:

#include <stdio.h>
#include <stdlib.h>

void find_subsets(int *set, int size, int target, int *subset, int subsize, int idx)
{
	if (idx == size)
	{
		int sum = 0;
		for (int i = 0; i < subsize; i++)
			sum += subset[i];
		if (sum == target)
		{
			for (int i = 0; i < subsize; i++)
				printf("%d ", subset[i]);
			printf("\n");
		}
		return;
	}
	subset[subsize] = set[idx];
	find_subsets(set, size, target, subset, subsize + 1, idx + 1);
	find_subsets(set, size, target, subset, subsize, idx + 1);
}

int main(int argc, char **argv)
{
	if (argc < 3) return 1;
	int target = atoi(argv[1]);
	int size = argc - 2;
	int *set = malloc(size * sizeof(int));
	int *subset = malloc(size * sizeof(int));
	if (!set || !subset) return free(set), free(subset), 1;
	for (int i = 0; i < size; i++)
		set[i] = atoi(argv[i + 2]);
	find_subsets(set, size, target, subset, 0, 0);
	free(set), free(subset);
	return 0;
}

// gcc -Wall -Werror -Wextra -o powerset powerset.c
// valgrind --leak-check=full ./powerset 5 1 2 3 4 5

// //Complete code for explaining the powerset of a set of numbers
// #include <stdio.h>
// #include <stdlib.h>

// void find_subsets(int *set, int size, int target, int *subset, int subsize, int idx) {
//     int sum = 0;

//     // Calculate the sum of the current subset
//     for (int i = 0; i < subsize; i++)
//         sum += subset[i];

//     // Print the subset if the sum matches the target
//     if (sum == target) {
//         for (int i = 0; i < subsize; i++)
//             printf("%d ", subset[i]);
//         printf("\n");
//     }

//     // If we have processed all elements, stop recursion
//     if (idx == size)
//         return;

//     // Include the current element in the subset
//     subset[subsize] = set[idx];
//     find_subsets(set, size, target, subset, subsize + 1, idx + 1);

//     // Exclude the current element from the subset
//     find_subsets(set, size, target, subset, subsize, idx + 1);
// }

// int main(int argc, char **argv) {
//     if (argc < 3)  // Validate input
//         return 1;

//     int target = atoi(argv[1]);  // Parse the target sum
//     int size = argc - 2;         // Determine the size of the set

//     // Allocate memory for the set and subset
//     int *set = malloc(size * sizeof(int));
//     int *subset = malloc(size * sizeof(int));
//     if (!set || !subset) {
//         free(set);  // Free allocated memory (if any) before exiting
//         free(subset);
//         return 1;
//     }

//     // Parse the set elements
//     for (int i = 0; i < size; i++)
//         set[i] = atoi(argv[i + 2]);

//     // Find and print subsets
//     find_subsets(set, size, target, subset, 0, 0);

//     // Free allocated memory
//     free(set);
//     free(subset);

//     return 0;
// }

