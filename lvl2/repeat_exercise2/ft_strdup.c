#include <stdlib.h>

char	*ft_strdup(char *src)
{
	int	i;
	char *res;

	i = 0;
	while (src[i])
		i++;
	res = malloc (sizeof(char) * (i + 1));
	i = 0;
	while (src[i])
	{
		res[i] = src[i];
		i++;
	}
	return(res);
}

#include <stdio.h>
#include <string.h>
int	main(void)
{
	printf("rl_strdup: %s\n", strdup("DogCat"));
	printf("ft_strdup: %s\n", ft_strdup("DogCat"));
}