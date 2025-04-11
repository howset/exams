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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Declare the sandbox function
int sandbox(void (*f)(void), unsigned int timeout, bool verbose);

// ===== Test Functions =====

// Nice functions
void nice_function(void) {
    printf("This is a nice function that returns normally\n");
}

void nice_function_with_work(void) {
    printf("Working...\n");
    for (int i = 0; i < 3; i++) {
        printf("Step %d completed\n", i + 1);
        sleep(1);
    }
    printf("Work completed successfully\n");
}

// Bad functions
void bad_function_segfault(void) {
    printf("About to cause a segmentation fault...\n");
    int *ptr = NULL;
    *ptr = 42; // This will cause a segmentation fault
}

void bad_function_abort(void) {
    printf("About to abort...\n");
    abort();
}

void bad_function_exit_code(void) {
    printf("About to exit with code 42...\n");
    exit(42);
}

void bad_function_timeout(void) {
    printf("About to enter an infinite loop...\n");
    while (1) {
        sleep(1);
        printf("Still running...\n");
    }
}

void bad_function_signal(void) {
    printf("About to raise SIGFPE...\n");
    raise(SIGFPE); // Floating point exception
}

// Main function to test sandbox
int main(void) {
    int result;
    bool verbose = true;
    
    printf("\n===== Testing Nice Functions =====\n");
    
    printf("\n1. Testing nice_function:\n");
    result = sandbox(nice_function, 5, verbose);
    printf("Result: %d (Expected: 1)\n", result);
    
    printf("\n2. Testing nice_function_with_work:\n");
    result = sandbox(nice_function_with_work, 5, verbose);
    printf("Result: %d (Expected: 1)\n", result);
    
    printf("\n===== Testing Bad Functions =====\n");
    
    printf("\n3. Testing bad_function_segfault:\n");
    result = sandbox(bad_function_segfault, 5, verbose);
    printf("Result: %d (Expected: 0)\n", result);
    
    printf("\n4. Testing bad_function_abort:\n");
    result = sandbox(bad_function_abort, 5, verbose);
    printf("Result: %d (Expected: 0)\n", result);
    
    printf("\n5. Testing bad_function_exit_code:\n");
    result = sandbox(bad_function_exit_code, 5, verbose);
    printf("Result: %d (Expected: 0)\n", result);
    
    printf("\n6. Testing bad_function_timeout:\n");
    result = sandbox(bad_function_timeout, 2, verbose);
    printf("Result: %d (Expected: 0)\n", result);
    
    printf("\n7. Testing bad_function_signal:\n");
    result = sandbox(bad_function_signal, 5, verbose);
    printf("Result: %d (Expected: 0)\n", result);
    
    return 0;
}