#include <stdio.h>
#include <stdlib.h>

void	print_nums(int *candidates, int size)
{
	int	i = -1;

	while (++i < size)
	{
		if (candidates[i] >= 0)
			printf("%d ", candidates[i]);
	}
	printf("\n");
}

void	process(int target, int aggr_solution, int *nums, int *candidates, int idx, int size)
{
	if (idx == size)
	{
		if (aggr_solution == target)
			print_nums(candidates, size);
		return ;
	}
	if (aggr_solution >= target) // backtracking optimization
		return ;
	int	i = idx;
	while (i < size)
	{
		candidates[i] = nums[i];
		process(target, aggr_solution + nums[i], nums, candidates, ++idx, size);
		candidates[i] = -1;
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc < 3)
		return (1);
	int	target = atoi(argv[1]);

	int	size = argc - 2;
	int	nums[size];
	int	candidates[size];
	int	i = -1;
	while (++i < size)
	{
		nums[i] = atoi(argv[i + 2]);
		candidates[i] = -1;
	}
	process(target, 0, nums, candidates, 0, size);
}