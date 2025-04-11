#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include <stdbool.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

void	timeout_handler(int signum)
{
	(void)signum;
	exit (142);
}

int sandbox(void(*f)(void), unsigned int timeout, bool verbose)
{
	struct sigaction sa;
	pid_t	pid;
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
		exit (EXIT_SUCCESS);
	}
	else
	{
		int res = waitpid(pid, &status, 0);
		if (res < 0)
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
					printf("Bad function: timed out after %u seconds\n", timeout);
				return (0);
			}
			else
			{
				if (verbose)
					printf("Bad function: exited with code %d\n", exit_code);
				return (0);
			}
		}
		if (WIFSIGNALED(status))
		{
			int sig = WTERMSIG(status);
			if (verbose)ou will find in this directory a file main.c which contain something to help you
			test your function.

				printf("Bad function: %s\n", strsignal(sig));
			return (0);
		}
	}
	return (0);
}
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

// Declare the sandbox function
int sandbox(void(*f)(void), unsigned int timeout, bool verbose);

// Sample function that runs successfully
void successful_function(void)
{
    printf("This function runs successfully.\n");
}

// Sample function that runs indefinitely (to test timeout)
void infinite_loop_function(void)
{
    while (1)
        ;
}

// Sample function that causes a segmentation fault
void segfault_function(void)
{
    int *ptr = NULL;
    *ptr = 42; // Dereferencing a NULL pointer
}

int main(void)
{
    printf("Testing successful function:\n");
    sandbox(successful_function, 5, true);

    printf("\nTesting infinite loop function (timeout):\n");
    sandbox(infinite_loop_function, 2, true);

    printf("\nTesting segmentation fault function:\n");
    sandbox(segfault_function, 5, true);

    return 0;
}