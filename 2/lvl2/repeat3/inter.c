#include <unistd.h>

int main(int argc, char *argv[])
{
	int i = 0;
	int j = 0;
	int *lookup[256] = {};

	while (argv[1][i])
	{
		while (argv[2][j])
		{
			if (argv[1][i] == argv[2][j] && !lookup[(int)argv[2][j]])
			{
				lookup[(int)argv[2][j]];
				write(1, &argv[2][j], 1);
			}
			j++;
		}
		i++;
	}
	
}