#include <stdlib.h>

char    *ft_strdup(char *src)
{
	int i = 0;
	char *dst;

	while (src[i])
		i++;
	dst = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return(dst);
}