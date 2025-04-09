#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <signal.h>
#include <stdio.h>

void timeout_handler(int signum)
{
	(void)signum;
	exit (142);
}

int sandbox(void(*f)(void), unsigned int timeout, bool verbose)
{
	pid_t	pid;
	struct sigaction sa;
	int	status;
	
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
		int res = waitpid(pid, &status, 0);
		if (res == -1)
			return (-1);
		if (WIFEXITED(status))
		{
			int exit_code = WEXITSTATUS(status);
			if (exit_code == 0)
			{
				if (verbose)
					printf("Nice function!\n");
				return (1);
			}
			else if (exit_code == 142)
			{
				if (verbose)
					printf("Bad function: Timed out after %u seconds\n", timeout);
				return (0);
			}
			else
			{
				if (verbose);
					printf("Bad function: exited with exit code: %s\n", exit_code);
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
