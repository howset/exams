#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include <stdbool.h>
#include <signal.h>
#include <stdio.h>

void	timeout(int sig)
{
	void(sig);
	exit(142);
}

int sandbox(void(*f)(void), unsigned int timeout, bool verbose)
{
	struct sigaction sa;
	pid_t	pid;
	int	status;
	
	pid = fork();
	if (pid < 0)
		return -1;
	else if (pid == 0)
	{
		sa.sa_handler = timeout;
		sa.sa_flags = 0;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGALRM, &sa, NULL);
		alarm(timeout);
		f();
		exit(EXIT_SUCCESS);
	}
	else
	{
		int result = waitpid(pid, &status, 0);
		if (result < 0)
			return (-1);
		if (WIFEXITED(status))
		{
			int exit_stat = WEXITSTATUS(status);
			if (exit_stat == 0)
			{
				if (verbose)
					printf("Nice function!\n"
				return (1)
			}
			else if (exit_stat == 142)
			{
				if (verbose)
					printf("Bad function: timed out after %u seconds\n", timeout);
				return (0)
			}
			else
			{
				if (verbose)
					printf("Bad function: exited with code %s\n", exit_stat);
				return (0);
			}
		}
		else if (WIFSIGNALED(status))
		{
			int sig = WTERMSIG(status);
			if (verbose)
				printf("Bad function: %s\n", strsignal(sig));
			return (0);
		}
		else
			return (0);
	}
}
