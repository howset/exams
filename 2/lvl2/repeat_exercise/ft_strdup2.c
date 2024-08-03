#include <stdlib.h>

char	*ft_strdup(char *src)
{
	char *res;
	int i = 0;

	while (src[i])
		i++;
	res = malloc(sizeof(char) * (i+1));
	if (!res)
		return NULL;
	while (src[i])
	{
		res[i] = src[i];
		i++;
	}
	return (res);
}