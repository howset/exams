int	max(int* tab, unsigned int len)
{
	int	res;
	unsigned int i;

	if (len == 0 || !tab)
		return(0);
	i = 0;
	res = tab[i];
	while (i < len)
	{
		if (res < tab[i])
			res = tab[i];
		i++;
	}
	return(res);
}

#include <stdio.h>
int	main(void)
{
	int i = 7;
	int tab[] = {};

	while (i < 6)
	{
		printf("%d\n", tab[i]);
		i++;
	}
	printf("max: %d\n", max(tab, 0));
}