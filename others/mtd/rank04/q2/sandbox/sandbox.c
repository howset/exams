#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

#define	INTERNAL_ERROR -1
#define	BAD_FUNCTION 0
#define NICE_FUNCTION 1


void timeout_handler(int signum) {
	/*
	this do-nothing handler is needed to override SIG_DFL of SIGALRM, which is:
	1. printf("Alarm clock\n");
	2. exit(142); (bc 128 + SIGALRM, which SIGALRM == 14, ergo 128 + 14)
	*/

    (void)signum;
}

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t	pid, w;
	int		wstatus;

	pid = fork();
	if (pid == -1)
		return INTERNAL_ERROR;
	if (pid == 0)
	{
		alarm(timeout);
		f();
		exit(0);
	}
	else
	{
		// "do-nothing" sa_handler overrides SIG_DFL
		struct sigaction sa;
        sa.sa_handler = timeout_handler;
        sigaction(SIGALRM, &sa, NULL);

		alarm(timeout); // will interrupt syscall such as waitpid() to ret -1
		w = waitpid(pid, &wstatus, WUNTRACED);
		if (w == -1)
		{
			if (errno == EINTR)
			{
				if (verbose)
					printf("Bad function: timed out after %d seconds\n", timeout);
				return BAD_FUNCTION;
			}
			printf("Uninterpreted -1 returned by waitpid()\n");
			return INTERNAL_ERROR;
		}
		if (WIFEXITED(wstatus))
		{
			if (WEXITSTATUS(wstatus) == 0)
			{
				if (verbose)
					printf("Nice function!\n");
				return NICE_FUNCTION;
			}
			if (verbose)
				printf("Bad function: exited with code %d\n", WEXITSTATUS(wstatus));
			return BAD_FUNCTION;
		}
		if (WIFSIGNALED(wstatus))
		{
			if (WTERMSIG(wstatus) == SIGALRM)
			{
				if (verbose)
					printf("Bad function: timed out after %d seconds\n", timeout);
				return BAD_FUNCTION;
			}
			if (verbose)
				printf("Bad function: %s\n", strsignal(WTERMSIG(wstatus)));
			return BAD_FUNCTION;
		}
		printf("Bad: Unspecified termination\n");
		return BAD_FUNCTION;
	}
}

void ignores_alarm(void)
{
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;  // Ignore SIGALRM in the child
    sigaction(SIGALRM, &sa, NULL);

    sleep(15);
}

int	main(void)
{
	sandbox(ignores_alarm, 2, true);
}