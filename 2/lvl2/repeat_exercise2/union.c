#include <unistd.h>
int	main(int argc, char *argv[])
{
	int	i;
	int *lookup[256] = {};

	if (argc == 3)
	{
		i = 0;
		while (argv[1][i])
		{
			lookup[(int)argv[1][i]] = (int *)1;
			i++;
		}
		i = 0;
		while (argv[2][i])
		{
			lookup[(int)argv[2][i]] = (int *)1;
			i++;
		}
		i = 0;
		while (argv[1][i])
		{
			if (lookup[(int)argv[1][i]])
			{
				write(1, &argv[1][i], 1);
				lookup[(int)argv[1][i]] = (int *)0;
			}
			i++;
		}
		i = 0;
		while (argv[2][i])
		{
			if (lookup[(int)argv[2][i]])
			{
				write(1, &argv[2][i], 1);
				lookup[(int)argv[2][i]] = (int *)0;
			}
			i++;
		}
	}	
	write(1, "\n", 1);
	return(0);
}