#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include <stdbool.h>
#include <signal.h>
#include <stdio.h>

#include <string.h>
#include <errno.h>

int	g_to;

void	handle_timeout(int sig)
{
	if (sig == SIGALRM)
		g_to = 1;
}

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	int status;
	pid_t pid;
	struct sigaction sa;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		f();
		exit(0);
	}
	sa.sa_handler = handle_timeout;
	sigaction(SIGALRM, &sa, NULL);
	alarm(timeout);
	if (waitpid(pid, &status, 0) == -1) // if its a bad ft
	{
		while (1)
		{
			if (errno == EINTR) // waitpid interupted by signal
			{
				if (g_to) // if timeout went off
				{
					if (verbose)
						printf("Bad function: timed out after %u seconds\n", timeout);
					kill(pid, SIGKILL);
					if (waitpid(pid, &status, NULL) == -1)
						return (-1);
					return (0);
				}
				continue;
			}
			else
				return (-1);
		}
	}
	if (WIFSIGNALED(status))
	{
		int	exit_code = WTERMSIG(status);
		if (verbose)
			printf("Bad function: %s\n", strsignal(exit_code));
		return (0);
	}
	if (WIFEXITED(status))
	{
		int	exit_code = WEXITSTATUS(status);
		if (exit_code)
		{
			if (verbose)
				printf("Bad function: exited with code %d\n", exit_code);
			return (0);
		}
		else
		{
			if (verbose)
				printf("Nice function!\n");
			return (1);
		}
	}
	return (-1);
}



// A nice function
void good_function(void)
{
    // does nothing bad
}

// A function that exits with non-zero code
void bad_exit_function(void)
{
    exit(42);
}

// A function that causes a segfault
void segfault_function(void)
{
    int *ptr = NULL;
    *ptr = 1;
}

// A function that takes too long
void timeout_function(void)
{
    sleep(10);
}

int main(void)
{
    printf("Testing good_function:\n");
    sandbox(good_function, 3, true);

    printf("\nTesting bad_exit_function:\n");
    sandbox(bad_exit_function, 3, true);

    printf("\nTesting segfault_function:\n");
    sandbox(segfault_function, 3, true);

    printf("\nTesting timeout_function:\n");
    sandbox(timeout_function, 3, true);

    return 0;
}
