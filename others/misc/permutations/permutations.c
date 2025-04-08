#include <unistd.h>
//#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	swap(char *c1, char *c2)
{
	char	temp;

	temp = *c1;
	*c1 = *c2;
	*c2 = temp;
}

char	*sorting(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if(str[i] > str[j])
				swap(&str[i], &str[j]);
			j++;
		}
		i++;
	}
	return (str);
}

int	next_perm(char *str, int len)
{
	int	i;
	int	j;
	int	left;
	int	right;

	i = len - 2;
	while (i >=0 && str[i] >= str[i + 1])
		i--;
	if (i < 0)
		return (0);
	j = len - 1;
	while (str[j] <= str[i])
		j--;
	swap(&str[i], &str[j]);
	left = i + 1;
	right = len -1;
	while (left < right)
	{
		swap(&str[left], &str[right]);
		left++;
		right--;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	int	len;
	char *str;
	
	if (argc != 2)
		return (1);
	len = ft_strlen(argv[1]);
	str = sorting(argv[1]);
	write(1, str, len);
	write(1, "\n", 1);
	//printf("%s\n", str);
	while (next_perm(str, len))
	{
		write(1, str, len);
		write(1, "\n", 1);
		//printf("%s\n", str);
	}
	return (0);
}