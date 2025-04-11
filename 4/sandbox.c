#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include <stdbool.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

void timeout_handler(int signum)
{
	(void)signum;
	exit (142);
}

int sandbox(void(*f)(void), unsigned int timeout, bool verbose)
{
	int	status;
	struct sigaction sa;
	pid_t	pid;
	
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		sa.sa_handler = timeout_handler;
		sa.sa_flags = 0;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGALRM, &sa, NULL);
		alarm(timeout);
		f();
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			return (0);
		if (WIFEXITED(status))
		{
			int ex_code = WEXITSTATUS(status);
			if (ex_code == 0)
			{
				if (verbose)
					printf("Nice function!\n");
				return (1);
			}
			else if (ex_code == 142)
			{
				if (verbose)
					printf("Bad function: timed out after %u seconds\n", timeout);
				return (0);
			}
			else
			{
				if (verbose)
					printf("Bad function: exited with code %d\n", ex_code);
				return (0);
			}
		}
		else if (WIFSIGNALED(status))
		{
			int sig = WTERMSIG(status);
			if (verbose)
				printf("Bad function: %d\n", sig);
			return (0);
		}
		else
			return (0);
	}
}
int main (void)
{
	return(0);
}