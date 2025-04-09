#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

// Declare the sandbox function
int sandbox(void(*f)(void), unsigned int timeout, bool verbose);

// ---- NICE FUNCTIONS ----

// Simple function that returns normally
void nice_function(void) {
    printf("This is a nice function that returns normally\n");
}

// Function that does some work but finishes in time
void nice_function_with_work(void) {
    printf("Working...\n");
    for (int i = 0; i < 3; i++) {
        printf("Step %d completed\n", i + 1);
        sleep(1);
    }
    printf("Work completed successfully\n");
}

// ---- BAD FUNCTIONS ----

// Function that segfaults
void bad_function_segfault(void) {
    printf("About to cause a segmentation fault...\n");
    int *ptr = NULL;
    *ptr = 42; // This will cause a segmentation fault
}

// Function that aborts
void bad_function_abort(void) {
    printf("About to abort...\n");
    abort();
}

// Function that exits with non-zero status
void bad_function_exit_code(void) {
    printf("About to exit with code 42...\n");
    exit(42);
}

// Function that times out
void bad_function_timeout(void) {
    printf("About to enter an infinite loop...\n");
    while (1) {
        sleep(1);
        printf("Still running...\n");
    }
}

// Function that raises a signal
void bad_function_signal(void) {
    printf("About to raise SIGILL...\n");
    raise(SIGILL); // Illegal instruction
}

// Main function to demonstrate sandbox
int main(int argc, char *argv[]) {
    int result;
    bool verbose = true;

	(void)argc;
	(void)argv;

    printf("\n=== Testing nice functions ===\n");

    printf("\n1. Testing nice_function:\n");
    result = sandbox(nice_function, 5, verbose);
    printf("Result: %d (expected: 1)\n", result);

    printf("\n2. Testing nice_function_with_work:\n");
    result = sandbox(nice_function_with_work, 5, verbose);
    printf("Result: %d (expected: 1)\n", result);

    printf("\n=== Testing bad functions ===\n");

    printf("\n3. Testing bad_function_segfault:\n");
    result = sandbox(bad_function_segfault, 5, verbose);
    printf("Result: %d (expected: 0)\n", result);

    printf("\n4. Testing bad_function_abort:\n");
    result = sandbox(bad_function_abort, 5, verbose);
    printf("Result: %d (expected: 0)\n", result);

    printf("\n5. Testing bad_function_exit_code:\n");
    result = sandbox(bad_function_exit_code, 5, verbose);
    printf("Result: %d (expected: 0)\n", result);

    printf("\n6. Testing bad_function_timeout:\n");
    result = sandbox(bad_function_timeout, 3, verbose);
    printf("Result: %d (expected: 0)\n", result);

    printf("\n7. Testing bad_function_signal:\n");
    result = sandbox(bad_function_signal, 5, verbose);
    printf("Result: %d (expected: 0)\n", result);

    return 0;
}