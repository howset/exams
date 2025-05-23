#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int picoshell(char **cmds[])
{
	int i;
	int prev_fd;
	int fd[2];
	pid_t pid;
	int status;
	
	i = 0;
	prev_fd = 0;
	while (cmds[i])
	{
		if (cmds[i + 1])
			pipe(fd);
		pid = fork();
		if (pid == -1)
		{
			close(fd[0]);
			close(fd[1]);
			return (1);
		}
		else if (pid == 0)
		{
			if (prev_fd != 0)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (cmds[i + 1])
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(EXIT_FAILURE);
		}
		else
		{
			if (prev_fd != 0)
				close(prev_fd);
			if (cmds[i + 1])
			{
				close(fd[1]);
				prev_fd = fd[0];
			}
		}
		i++;
	}
	while (wait(&status) > 0)
	{
		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
			return (1);
	}
	return (0);
}
