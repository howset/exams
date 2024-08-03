#include <stdlib.h>

int     *ft_range(int start, int end)
{
	int n;
	int *array;
	int step;
	int i;

	if ((end - start) < 0)
		n = -(end - start);
	else
		n = (end - start);
	array = malloc(sizeof(int) * (n + 1));
	if (start < end)
		step = -1;
	else
		step = 1;
	i = 0;
	while (i < (n + 1))
	{
		array[i] = end;
		end = end + step;
		i++;
	}
	return(array);
}

#include <stdio.h>
int	main(void)
{
	int i = 0;
	int *fr;

	fr = ft_range(5, -1);
	while(i < 7)
	{
		printf("%d\n", fr[i++]);
	}
}