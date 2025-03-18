#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	picoshell(char **cmds[]);

int	main(int argc, char **argv)
{
	int	cmds_size = 1;
	char	***cmds = NULL;
	int	ret;

	// count pipes to deduce how many ***cmds, then malloc
	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "|"))
			cmds_size++;
	}
	cmds = calloc(cmds_size + 1, sizeof(char **));
	if (!cmds)
	{
		dprintf(2, "Malloc error: %m\n");
		return 1;
	}
	cmds[cmds_size] = NULL;

	cmds[0] = argv + 1;
	int cmds_i = 1;
	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "|"))
		{
			cmds[cmds_i] = argv + i + 1;
			argv[i] = NULL;
			cmds_i++;
		}
	}
	ret = picoshell(cmds);
	if (ret)
		perror("picoshell");
	free(cmds);
	return ret;
}
