#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

// Timeout handler for the child process
void timeout_handler(int sig) {
    (void)sig;
    exit(142); // Special exit code for timeout
}

int sandbox(void (*f)(void), unsigned int timeout, bool verbose) {
    pid_t pid;
    int status;
    struct sigaction sa;

    // Fork a child process
    pid = fork();
    if (pid < 0) {
        // Fork failed
        if (verbose)
            printf("Error: fork failed: %s\n", strerror(errno));
        return -1;
    }

    if (pid == 0) {
        // Child process
        // Set up timeout alarm
        memset(&sa, 0, sizeof(sa));
        sa.sa_handler = timeout_handler;
        sigaction(SIGALRM, &sa, NULL);
        alarm(timeout); // Set alarm to trigger after timeout seconds

        // Execute the function
        f();

        // If the function returns normally, exit with success
        exit(0);
    } else {
        // Parent process
        int result = waitpid(pid, &status, 0);
        if (result < 0) {
            // Error in waitpid
            if (verbose)
                printf("Error: waitpid failed: %s\n", strerror(errno));
            return -1;
        }

        // Check how the child process terminated
        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            if (exit_code == 0) {
                // Function exited normally with code 0
                if (verbose)
                    printf("Nice function!\n");
                return 1;
            } else if (exit_code == 142) {
                // Function timed out
                if (verbose)
                    printf("Bad function: timed out after %u seconds\n", timeout);
                return 0;
            } else {
                // Function exited with a non-zero exit code
                if (verbose)
                    printf("Bad function: exited with code %d\n", exit_code);
                return 0;
            }
        } else if (WIFSIGNALED(status)) {
            // Function was terminated by a signal
            int sig = WTERMSIG(status);
            if (verbose)
                printf("Bad function: %s\n", strsignal(sig));
            return 0;
        } else {
            // Other termination reason (should not happen)
            if (verbose)
                printf("Bad function: unknown termination reason\n");
            return 0;
        }
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Declare the sandbox function
int sandbox(void (*f)(void), unsigned int timeout, bool verbose);

// Test functions
void nice_function(void) {
    printf("This is a nice function.\n");
}

void bad_function_segfault(void) {
    int *ptr = NULL;
    *ptr = 42; // Causes a segmentation fault
}

void bad_function_timeout(void) {
    while (1) {
        sleep(1); // Infinite loop
    }
}

void bad_function_exit_code(void) {
    exit(42); // Exits with a non-zero code
}

int main(void) {
    printf("Testing nice_function:\n");
    sandbox(nice_function, 5, true);

    printf("\nTesting bad_function_segfault:\n");
    sandbox(bad_function_segfault, 5, true);

    printf("\nTesting bad_function_timeout:\n");
    sandbox(bad_function_timeout, 2, true);

    printf("\nTesting bad_function_exit_code:\n");
    sandbox(bad_function_exit_code, 5, true);

    return 0;
}