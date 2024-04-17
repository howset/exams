#include <unistd.h>

int	main(int argc, char *argv[])
{
	int	i = 0;
	char *str;

	str = argv[1];
	if (argc == 2)
	{
		while (str[i] == 32 || str[i] == 9)
			i++;
		while ((str[i] != 32 && str[i] != 9) && str[i])
			write(1, &str[i++], 1);
	}
	write(1, "\n", 1);
	return(0);
}