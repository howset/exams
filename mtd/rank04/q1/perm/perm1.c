// done in 20 minutes

#include <stdio.h>
#include <stdbool.h>

int	ft_strlen(char *s)
{
	int	i = -1;

	while (s[++i])
		;
	return (i);
}

void	bubble_sort(char *set, int size)
{
	int	i;
	int	j;
	char	tmp;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size - 1)
		{
			if (set[j] > set[j + 1])
			{
				tmp = set[j + 1];
				set[j + 1] = set[j];
				set[j] = tmp;
			}
		}
	}
}

void	process(char *set, int size, char *tmp, bool *placed, int idx)
{
	if (idx == size)
	{
		printf("%s\n", tmp);
		return ;
	}
	int	i = -1;
	while (++i < size)
	{
		if (placed[i])
			continue ;
		tmp[idx] = set[i];
		placed[i] = true;
		process(set, size, tmp, placed, idx + 1);
		placed[i] = false;
	}
}

int	main(int argc, char **argv)
{
	int	size;

	if (argc != 2)
		return (1);
	size = ft_strlen(argv[1]);

	char	set[size];
	char	tmp[size + 1];
	bool	placed[size];
	int	i = -1;

	while (++i < size)
	{
		set[i] = argv[1][i];
		placed[i] = false;
	}
	tmp[i] = '\0';
	bubble_sort(set, size);
	process(set, size, tmp, placed, 0);
}
