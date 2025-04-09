#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include <stdbool.h>
#include <signal.h>
#include <stdio.h>

void	timeout(int sig)
{
	(void)sig;
	exit (142);
}

int sandbox(void(*f)(void), unsigned int timeout, bool verbose)
{
	struct sigaction sa;
	int	status;
	pid_t	pid;
	
	pid = fork();
	if (pid < 0)
		return (0);
	else if (pid == 0)
	{
		sa.sa_handler = timeout;
		sa.sa_flags = 0;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGALRM, &sa, NULL);
		alarm(timeout);
		f();
		exit (EXIT_SUCCESS);
	}
	else
	{
		int	res = waitpid(pid, &status, 0);
		if (res == -1)
			return (-1);
		if (WIFEXITED(status))
		{
			int ex_stat = WEXITSTATUS(status);
			if (ex_stat == 0)
				return (1);
			else if (ex_stat == 142)
				return (0);
			else
				return (0);
		}
		else if (WIFSIGNALED(status))
		{
			int sig = WTERMSIG(status);
			if (verbose)
				printf ("%s\n", strsignal(sig));
			return (0);
		}
		
	}
}
