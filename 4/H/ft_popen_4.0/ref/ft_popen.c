#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

int ft_popen(const char *file, const char *argv[], char type)
{
	int fd[2];
	pid_t pid;
	int fd_to_return;

	if (type != 'r' && type != 'w')
		return (-1);
	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1) //Fork error
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	else if (pid == 0) //Child process
	{
		if (type == 'r')
		{
			close(fd[0]); //Child outputs to pipe, so close read end
			if (dup2(fd[1], STDOUT_FILENO) == -1) //Redirect stdout to write end of pipe
				exit(EXIT_FAILURE);
		}
		else
		{
			close(fd[1]); //Child reads from pipe, so close write end
			if (dup2(fd[0], STDIN_FILENO) == -1) //Redirect stdin to read end of pipe
				exit(EXIT_FAILURE);
		}
		if (type == 'r') //Close the duplicates
			close(fd[1]);
		else
			close(fd[0]);
		execvp(file, (char *const *)argv); //Exec the command
		exit(EXIT_FAILURE); //If execvp returns, it means error
	}
	else //Parent process
	{
		if (type == 'r')
		{
			close(fd[1]); //Parent reads from pipe, so close write end
			fd_to_return = fd[0];
		}
		else
		{
			close(fd[0]); //Parent writes to pipe, so close read end
			fd_to_return = fd[1];
		}
		return (fd_to_return);
	}
}

// GPT generated main to test
#include <stdio.h>
#include <fcntl.h>

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
        //printf("%s", line);
        ft_putstr(line);
		free(line);
    }
    close(fd1);
    
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