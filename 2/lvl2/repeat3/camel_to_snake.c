#include<unistd.h>

int	main(int argc, char *argv[])
{
	int i = 0;
	char *str;

	(void)argc;
	str = argv[1];
	if (argc == 2 )
	{
		while (str[i])
		{
			if (str[i] >= 'A' && str[i] <= 'Z')
			{
				str[i] = str[i] + 32;
				write(1, "_", 1);
			}
			write(1, &str[i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return(0);
}