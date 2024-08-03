#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	int av1 = atoi(argv[1]);
	int av3 = atoi(argv[3]);

	if (argc == 4)
	{
		if (argv[2][0] == '+')
			printf("%d", (av1 + av3));
		else if (argv[2][0] == '-')
			printf("%d", (av1 - av3));
		else if (argv[2][0] == '*')
			printf("%d", (av1 * av3));
		else if (argv[2][0] == '/')
			printf("%d", (av1 / av3));
		else if (argv[2][0] == '%')
			printf("%d", (av1 % av3));
	}
	printf("\n");
	return(0);
}