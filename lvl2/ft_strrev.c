char *ft_strrev(char *str)
{
	char	temp;
	int	i = 0;
	int	j = 0;

	while (str[i])
		i++;
	i--;
	while (j < i)
	{
		temp = str[j];
		str[j] = str[i];
		str[i] = temp;
		j++;
		i--;
	}
	return (str);
}

#include <stdio.h>
int	main(void)
{
	char	res[] = "Dogdog catcat";
	ft_strrev(res);
	printf("Res: %s\n", res);
	return (0);
}