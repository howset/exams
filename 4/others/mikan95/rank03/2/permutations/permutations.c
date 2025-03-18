#include <stdio.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	swap(char *a, char *b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

char	*ft_sort(char *str)
{
	for (int i = 0; str[i]; i++)
		for (int j = i + 1; str[j]; j++)
			if (str[i] > str[j])
				swap(&str[i], &str[j]);
	return (str);
}

int	next_permutation(char *str, int len)
{
	int i = len - 2, j = len - 1;
	while (i >= 0 && str[i] >= str[i + 1]) i--;
	if (i < 0) return (0);
	while (str[j] <= str[i]) j--;
	swap(&str[i], &str[j]);
	for (int left = i + 1, right = len - 1; left < right; left++, right--)
		swap(&str[left], &str[right]);
	return (1);
}

int	main(int ac, char **av)
{
	if (ac != 2) return (1);
	int len = ft_strlen(av[1]);
	char *str = ft_sort(av[1]);
	write(1, str, len);
	write(1, "\n", 1);
	while (next_permutation(str, len))
	{
		write(1, str, len);
		write(1, "\n", 1);
	}
	return (0);
}


// to compile use gcc -Wall -Wextra -Werror -o program permutations.c
// to run use ./program abc
// leaks --atExit -- ./program abc
