char	*ft_strrev(char *str)
{
	int	i;
	int	j;
	char temp;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	i--;
	while (j < i)
	{
		temp = str[j];
		str[j] = str[i];
		str[i] = temp;
		i--;
		j++;
	}
	return(str);
}

#include <stdio.h>
int	main(void)
{
	char res[] = "DogCat";
	printf("ft_strrev: %s\n", ft_strrev(res));
}