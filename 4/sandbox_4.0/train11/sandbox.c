#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include <stdbool.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int g_flag;

void timeout_handler(int signum)
{
	if (signum == SIGALRM)
		g_flag = 0;
}

int sandbox(void(*f)(void), unsigned int timeout, bool verbose)
{
	struct sigaction sa;
	int status;
	pid_t pid;
	
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		f();
		exit(EXIT_SUCCESS);
	}
	sa.sa_handler = timeout_handler;
	sigaction(SIGALRM, &sa, NULL);
	alarm(timeout);
	if (waitpid(pid, &status, 0) == -1)
	{
		while (1)
		{
			if (errno == EINTR)
			{
				if (g_flag)
				{
					if (verbose)
						printf("%u\n", timeout);
					kill(pid, SIGKILL);
					if (waitpid(pid, &status, 0))
						return (-1);
					return (0);
				}
				continue;
			}
			else
				return (-1);
		}
	}
	if (WIFEXITED(status))
	{
		int ex_code = WEXITSTATUS(status);
		if (ex_code == 0)
		{
			if (verbose)
				printf("Nice!\n");
			return (1);
		}
		else
		{
			if (verbose)
				printf("%d\n", ex_code);
			return (0);
		}
	}
	if (WIFESIGNALED(status))
	{
		int sig_code = WTERMSIG(status);
			printf("%s\n", strsignal(sig_code));
		return (0);
	}
	return (-1);
}
