#include <unistd.h>

int	main(int argc, char *argv[])
{
	int	i;
	int	j;

	if (argc == 2)
	{
		i = 0;
		j = 0;
		while (argv[1][i])
		{
			if (argv[1][i] == ' ' && (argv[1][i+1] > 32 && argv[1][i+1] < 127))
				j = i + 1;
			i++;
		}
		while ((argv[1][j] > 32 && argv[1][j] < 127))
		{
			write(1, &argv[1][j], 1);
			j++;
		}
	}
	write(1, "\n", 1);
	return(0);
}