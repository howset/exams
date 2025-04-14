#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include <stdbool.h>
#include <signal.h>
#include <stdio.h>

#include <string.h>
#include <errno.h>

int sandbox(void(*f)(void), unsigned int timeout, bool verbose);

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