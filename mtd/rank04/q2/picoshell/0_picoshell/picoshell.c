#include <stdio.h>

#include <unistd.h> // dup2, pipe, close, fork, exit
#include <stdlib.h>
#include <sys/wait.h> // wait

/*
int	execvp(const char *file, char *const argv[]);
int	execve(const char *pathname, char *const argv[], char *const envp[]);
*/
int	picoshell(char **cmds[])
{
	int	cmds_size = 0;
	int	i = -1;

	while (cmds[++i])
		cmds_size++;

	pid_t	pid[cmds_size], w[cmds_size];
	int	fds[cmds_size - 1][2];
	i = -1;
	while (++i < cmds_size)
	{
		if (i != cmds_size - 1)
		{
			if (pipe(fds[i]) == -1)
				return 1;
		}
		pid[i] = fork();
		if (pid[i] < 0)
			return 1;
		if (pid[i] == 0)
		{
			if (i == 0)
			{
				if (dup2(fds[i][1], STDOUT_FILENO) == -1)
					return 1;
				if (close(fds[i][1] == -1))
					return 1;
				execvp(cmds[i][0], cmds[i]);
			}
			if (i == cmds_size - 1)
			{
				if (dup2(fds[i - 1][0], STDIN_FILENO) == -1)
					return 1;
				if (close(fds[i - 1][0]) == -1)
					return 1;
				execvp(cmds[i][0], cmds[i]);
			}
			else if (i > 0)
			{
				if (dup2(fds[i - 1][0], STDIN_FILENO) == -1) // in-pipe
					return 1;
				if (close(fds[i - 1][0]) == -1)
					return 1;
				if (dup2(fds[i][1], STDOUT_FILENO) == -1) // out-pipe
					return 1;
				if (close(fds[i][1]) == -1)
					return 1;
				execvp(cmds[i][0], cmds[i]);
			}
		}
		else
		{
			if (i == 0)
			{
				if (close(fds[i][1]) == -1)
					return 1;
			}
			if (i == cmds_size - 1)
			{
				if (close(fds[i - 1][0]) == -1)
					return 1;
			}
			else if (i > 0)
			{
				if (close(fds[i][1]) == -1 || close(fds[i - 1][0]) == -1)
					return 1;
			}
			wait(&w[i]);
		}
	}
	return 0;
}
