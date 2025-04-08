#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_sort(char *str)
{
	int		i = 0;
	char	temp;
	while (i < (ft_strlen(str) - 1))
	{
		if (str[i] > str[i + 1])
		{
			temp = str[i];
			str[i] = str[i + 1];
			str[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
	return (str);
}

void	swap(char *a, char *b)
{
	char	temp = *a;
	*a = *b;
	*b = temp;
}

int		get_next_permutation(char *str, int len)
{
	int	i = len - 2;
	int	j;

	// Find the first decreasing element from right
	while (i >= 0 && str[i] >= str[i + 1])
		i--;
	if (i < 0)
		return (0);

	// Find the smallest element greater than str[i]
	j = len - 1;
	while (str[j] <= str[i])
		j--;
	// Swap them
	swap(&str[i], &str[j]);
	// Reverse the substring after position i
	int left = i + 1;
	int right = len - 1;
	while (left < right)
	{
		swap(&str[left], &str[right]);
		left++;
		right--;
	}

	return (1);
}

void	print_all_permutations(char *str)
{
	int len = ft_strlen(str);

	// Print the first (sorted) permutation
	puts(str);

	// Generate and print all subsequent permutations
	while (get_next_permutation(str, len))
		puts(str);
}

int		main(int ac, char **av)
{
	char	*sorted_str = NULL;

	if (ac != 2)
		return (1);
	else if (ft_strlen(av[1]) <= 1)
	{
		puts(av[1]);
		return (0);
	}
	sorted_str = ft_sort(av[1]);
	print_all_permutations(sorted_str);
	return (0);
}
