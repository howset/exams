#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int ft_popen(const char *file, const char *argv[], char type)
{
	int	fd[2];
	pid_t	pid;
	
	if (type != 'r' && type != 'w')
		return (-1);
	pipe(fd);
	pid = fork();
	if (pid < 0)
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
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}
		execvp(file, (char *const *)argv);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (type == 'r')
		{
			close(fd[1]);
			return (fd[0]);
		}
		else
		{
			close(fd[0]);
			return (fd[1]);
		}
	}
}
