#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

void timeout_handler(int sig)
{
	(void)sig;
	exit(142);
}

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t pid;
	int status;
	struct sigaction sa;

	pid = fork();
	if (pid < 0)
	{
		if (verbose) //maybe not neccessary
			printf("Error: fork failed: %s\n", strerror(errno));
		return -1;
	}
	if (pid == 0)
	{
		sa.sa_handler = timeout_handler;
		sa.sa_flags = 0;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGALRM, &sa, NULL);
		alarm(timeout);
		f(); //execute function
		exit(EXIT_SUCCESS); //if function returns normally, exit success
	}
	else
	{
		int result = waitpid(pid, &status, 0);
		if (result < 0) //waitpid error
		{
			if (verbose) //maybe not neccessary
				printf("Error: waitpid failed: %s\n", strerror(errno));
			return -1;
		}
		// Check how the child process terminated
		if (WIFEXITED(status))
		{
			int exit_code = WEXITSTATUS(status);
			if (exit_code == 0) //function exited normally (code 0)
			{
				if (verbose)
					printf("Nice function!\n");
				return 1;
			}
			else if (exit_code == 142) //function timed out
			{
				if (verbose)
					printf("Bad function: timed out after %u seconds\n", timeout);
				return 0;
			}
			else //function with non-zero exit code
			{
				if (verbose)
					printf("Bad function: exited with code %d\n", exit_code);
				return 0;
			}
		}
		else if (WIFSIGNALED(status)) //function terminated by signal
		{
			int sig = WTERMSIG(status);
			if (verbose)
				printf("Bad function: %s\n", strsignal(sig));
			return 0;
		}
		else
		{
			if (verbose) //maybe not neccessary
				printf("Bad function: unknown termination reason\n");
			return 0;
		}
	}
}