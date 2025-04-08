#include <stdio.h>
#include <stdlib.h>

//copilot sonnet
void find_subsets(int *arr, int n, int *subset, int subset_size, int index, int target_sum) {
    int sum = 0;
    for (int i = 0; i < subset_size; i++) {
        sum += subset[i];
    }
    if (sum == target_sum) {
        for (int i = 0; i < subset_size; i++) {
            printf("%d ", subset[i]);
        }
        printf("$\n");
    }
    for (int i = index; i < n; i++) {
        subset[subset_size] = arr[i];
        find_subsets(arr, n, subset, subset_size + 1, i + 1, target_sum);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    int target_sum = atoi(argv[1]);
    int n = argc - 2;
    int *arr = (int *)malloc(n * sizeof(int));
    if (!arr) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 2]);
    }

    int *subset = (int *)malloc(n * sizeof(int));
    if (!subset) {
        free(arr);
        return 1;
    }

    find_subsets(arr, n, subset, 0, 0, target_sum);

    free(arr);
    free(subset);
    return 0;
}