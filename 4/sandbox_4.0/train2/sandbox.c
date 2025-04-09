#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <signal.h>
#include <stdio.h>

void to_handler(int signum)
{
	(void)signum;
	exit(142);
}

int sandbox(void(*f)(void), unsigned int timeout, bool verbose)
{
	struct sigaction sa;
	int status;
	pid_t pid;
	
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		sa.sa_handler = to_handler;
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
		if (res < 0)
			return (-1);
		if (WIFEXITED(status))
		{
			int ex_stat = WEXITSTATUS(status);
			if (ex_stat == 0)
			{
				if (verbose)
					printf("Nice function\n");
				return (1);
			}
			else if (ex_stat == 142)
			{
				if (verbose)
					printf("Bad function: timed out after %u seconds\n", timeout);
				return (0);
			}
			else
			{
				if (verbose)
					printf("Bad function: exited with code %s\n", ex_stat);
				return (0);
			}
				
		}
		else if (WIFESIGNALED(status))
		{
			int sig = WTERMSIG(status);
			if (verbose)
				printf("Bad function: %s\n", strsignal(sig));
		}
	}
}
