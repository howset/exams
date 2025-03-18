#include <stdio.h>
#include <stdlib.h>

void	solve(int *str, int col);
void	ft_swap(int i,int idx, int *arr);
void	print_array(int *str);
int		checker(int *arr);

int n;

int	main(int argc, char *argv[])
{
	int	i;

	i = 0;
	if (argc == 2)
	{
		int n = atoi(argv[1]);
		int str[100];
		while(i < n + 1)
		{
			str[i - 1] = i;
			i++;
		}
		solve(str, 0);
	}
	return (0);
}

void	solve(int *str, int col)
{
	int	i;
	//int n;

	if (col == n - 1)
	{
		//if(checker(str))
		//if(chekcer(arr, n))
			print_array(str);
	}
	i = col;
	while (i < n)
	{
		ft_swap(i, col, str);
		solve(str, col + 1);
		ft_swap(i, col, str);
		i++;
	}
}

void	ft_swap(int i,int idx, int *arr)
{
	int	tmp;

	tmp = arr[i];
	arr[i] = arr[idx];
	arr[idx] = tmp;
}

void	print_array(int *str)
{
	int	i;
	//int n;

	i = 0;
	while (i < n)
	{
		printf("%d", str[i]);
		i++;
	}
	printf("\n");
}

int		checker(int *arr)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = i + 1;
		while (j < n)
		{
			if (arr[i] == arr[j] + (j - i) || arr[i] == arr[j] - (j - i))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}