#include <unistd.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	int	i = 0;
	int	j = 0;

	if (argc == 2)
	{
		while (argv[1][i])
			i++;
		printf("first i: %d\n", i);
		while (argv[1][i] == ' ' || argv[1][i] == '\t')
		{
			i--;
			j = i;
		}
		printf("second i: %d\n", i);
		printf("j: %d\n", i);
		while (argv[1][i] != ' ' || argv[1][i] != '\t')
			i--;
		i++;
		printf("third i: %d\n", i);
		while (i != j)
		//while (argv[1][i])
		{
			write(1, &argv[1][i], 1);
			i++;
		}
		printf("last i: %d\n", i);
	}
	write(1, "\n", 1);
	return (0);
}