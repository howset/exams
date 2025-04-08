#include <stdlib.h>
#include <stdio.h>

void print_sets_of_specific_sum(
	int *s,
	int len,
	int depth,
	int n,
	int *fixed_size_set,
	int set_idx)
{
	if (depth <= 0)
		return;
	for (int i = 0; i < len; i++) {
		fixed_size_set[set_idx] = s[i];
		if (depth == 1 && fixed_size_set[set_idx] == n) {
			for (int j = 0; j < set_idx + 1; j++) {
				if (j != 0)
					printf(" ");
				printf("%d", fixed_size_set[j]);
			}
			printf("\n");
		} else
			print_sets_of_specific_sum(
				s   + i + 1,
				len - i - 1,
				depth - 1,
				n - s[i],
				fixed_size_set,
				set_idx + 1);
	}
}

int main(int ac, char **av) {
	if (ac < 3)
		return 1;
	int n = atoi(av[1]);
	int s[ac - 2];
	for (int i = 2; i < ac; i++) {
		s[i - 2] = atoi(av[i]);
	}
	for (int depth = 1; depth < ac - 1; depth++) { 
		int fixed_size_set[depth];
		print_sets_of_specific_sum(
			s,
			ac - 2,
			depth,
			n,
			fixed_size_set,
			0);
	}
	if (n == 0)
		printf("\n");
	return 0;
}