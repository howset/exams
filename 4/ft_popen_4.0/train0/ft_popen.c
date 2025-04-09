#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int ft_popen(const char *file, const char *argv[], char type)
{
	int	fd[2];
	pid_t	pid;
	int	fd_ret;

	if (type != 'r' && type != 'w')
		return (-1);
	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	else if (pid == 0)
	{
		if (type == 'r')
		{
			close(fd[0]);
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				exit(EXIT_FAILURE);
		}
		else if (type == 'w')
		{
			close(fd[1]);
			if (dup2(fd[0], STDIN_FILENO) == -1)
				exit(EXIT_FAILURE);
		}
		if (type == 'r')
			close(fd[1]);
		else
			close(fd[0]);
		execvp(file, (char* const*) argv);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (type == 'r')
		{
			close (fd[1]);
			fd_ret = fd[0];
		}
		else
		{
			close (fd[0]);
			fd_ret = fd[1];
		}
		return (fd_ret);
	}
}