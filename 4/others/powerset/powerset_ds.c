#include <stdio.h>
#include <stdlib.h>

// Function to print a subset
void print_subset(int *subset, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", subset[i]);
    }
    printf("\n");
}

// Recursive function to generate subsets and check their sum
void generate_subsets(int *set, int set_size, int *subset, int subset_size, int target_sum, int index) {
    // Base case: if the current subset sum equals the target sum, print it
    if (target_sum == 0) {
        print_subset(subset, subset_size);
        return;
    }

    // Try adding each element to the subset
    for (int i = index; i < set_size; i++) {
        if (set[i] > target_sum) {
            continue; // Skip elements larger than the remaining sum
        }

        // Add the current element to the subset
        subset[subset_size] = set[i];

        // Recur with the remaining sum and next index
        generate_subsets(set, set_size, subset, subset_size + 1, target_sum - set[i], i + 1);
    }
}

// Main function
int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <n> <set elements...>\n", argv[0]);
        return 1;
    }

    // Parse the target sum
    int target_sum = atoi(argv[1]);

    // Parse the set of integers
    int set_size = argc - 2;
    int *set = (int *)malloc(set_size * sizeof(int));
    if (set == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < set_size; i++) {
        set[i] = atoi(argv[i + 2]);
    }

    // Allocate memory for the subset
    int *subset = (int *)malloc(set_size * sizeof(int));
    if (subset == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        free(set);
        return 1;
    }

    // Generate and print all subsets with the target sum
    generate_subsets(set, set_size, subset, 0, target_sum, 0);

    // Free allocated memory
    free(set);
    free(subset);

    return 0;
}