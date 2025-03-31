// GPT generated main to test
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

// Declare the ft_popen function
int ft_popen(const char *file, const char *argv[], char type);

// Simple ft_putstr implementation
void ft_putstr(char *str)
{
    while (*str)
        write(1, str++, 1);
    write(1, "\n", 1);
}

int main(void)
{
    printf("Example 1: Reading output from 'ls -la' command\n");
    printf("------------------------------------------------\n");
    int fd1 = ft_popen("ls", (const char *[]){"ls", "-la", NULL}, 'r');
    if (fd1 == -1) {
        printf("Error opening pipe for reading\n");
        return 1;
    }
    char *line;
    while ((line = get_next_line(fd1))) {
        ft_putstr(line);
		free(line);
    }
    close(fd1);
    
	printf("Example 1.5: Reading output from 'ls' command\n");
    printf("------------------------------------------------\n");
    int fd3 = ft_popen("ls", (const char *[]){"ls", NULL}, 'r');
    if (fd3 == -1) {
        printf("Error opening pipe for reading\n");
        return 1;
    }
	char *line2;
    while ((line2 = get_next_line(fd3))) {
        ft_putstr(line2);
		free(line2);
    }
    close(fd3);

    printf("\nExample 2: Writing to 'grep hello' command\n");
    printf("------------------------------------------\n");
    int fd2 = ft_popen("grep", (const char *[]){"grep", "hello", NULL}, 'w');
    if (fd2 == -1) {
        printf("Error opening pipe for writing\n");
        return 1;
    }
    
    // Write some test data to the grep command
    write(fd2, "hello world\n", 12);
    write(fd2, "goodbye world\n", 14);
    write(fd2, "hello again\n", 12);
    close(fd2);  // Close to signal EOF to grep
    
    printf("\nThe grep command only printed lines containing 'hello'\n");
    
    return 0;
}