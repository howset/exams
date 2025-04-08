// Solution for ft_popen

#include <unistd.h>
#include <stdlib.h>

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
	if (pid == -1) // Error forking
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	else if (pid == 0) // Child process
	{
		if (type == 'r')
		{
			close(fd[0]); // Child outputs to pipe, so close read end
			if (dup2(fd[1], STDOUT_FILENO) == -1) // Redirect stdout to write end of pipe
				exit(EXIT_FAILURE);
		}
		else
		{
			close(fd[1]); // Child reads from pipe, so close write end
			if (dup2(fd[0], STDIN_FILENO) == -1) // Redirect stdin to read end of pipe
				exit(EXIT_FAILURE);
		}
		if (type == 'r') // Close the duplicate
			close(fd[1]);
		else
			close(fd[0]);
		execvp(file, (char *const *)argv); // Execute the command
		exit(EXIT_FAILURE); // If execvp returns, it means there was an error
	}
	else // Parent process
	{
		if (type == 'r')
		{
			close(fd[1]); // Parent reads from pipe, so close write end
			fd_to_return = fd[0];
		} else
		{
			close(fd[0]); // Parent writes to pipe, so close read end
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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*read_line(int fd, char *stock);
char	*extract_line(char *stock);
char	*clean_up(char *stock);

// Simple get_next_line implementation for the example
/* null_malloc -> just malloc and initialize the var with \0 */
char	*null_malloc(size_t nmemb, size_t size)
{
	char			*res;

	res = malloc(nmemb * size);
	if (!res)
		return (NULL);
	res[0] = '\0';
	return (res);
}

size_t	ft_strlen(const char *str)
{
	size_t	counts;

	counts = 0;
	while (str[counts] != '\0')
	{
		counts++;
	}
	return (counts);
}

/* freebuf_join -> just ft_join and free s1 (stock) */
char	*freebuf_join(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = null_malloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!res)
		return (NULL);
	res[0] = '\0';
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	free(s1); // just necessary to avoid leaks
	return (res);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (0);
}

char	*get_next_line(int fd)
{
	char		*extracted;
	static char	*stock = NULL; // declare a static variable and initialize
	char		*remains;

	if (fd < 0 || BUFFER_SIZE <= 0) // just a control sequence for invalid fd & BUFFER_SIZE to return NULL
	{
		if (stock != NULL) // stock was declared and initialized as NULL, if somehow it is not, then free and return NULL
			free(stock);
		return (NULL);
	}
	stock = read_line(fd, stock); // call read_line on fd and stock [1]
	if (!stock) // control if the above function fails
		return (NULL);
	extracted = extract_line(stock); // extract a line (anything up to \n) from stock [2]. At this point extracted is the return value of the get_next_line function
	remains = clean_up(stock); // however, stock still contains extracted, so some clean up is in order, to prepare it for the next call of the function [3]
	stock = remains; // stock is empty, and set to be remains
	return (extracted);
}

char	*read_line(int fd, char *stock) // [1]
{
	int		bytes;
	char	*line_fr_read;

	if (!stock) // on first run, stock should be NULL, so this should evaluate to TRUE
		stock = null_malloc(1, sizeof(char)); // if TRUE then allocate something ('\0', via null_malloc)
	line_fr_read = null_malloc(BUFFER_SIZE + 1, sizeof(char)); // allocate line_fr_read according to the defined BUFFER_SIZE, + 1 for the termination
	if (!line_fr_read) // control sequence
		return (NULL);
	bytes = 1; // initialize as one to make sure the following loop can be entered
	while (!ft_strchr(stock, '\n') && bytes != 0) // the loop evaluates when there is no '\n' in stock, and read is successful
	{
		bytes = read(fd, line_fr_read, BUFFER_SIZE); // calls read with a count of BUFFER_SIZE to the buffer area line_fr_read
		if (bytes == -1) // control sequence if read fails, free stock and the buffer and return NULL
		{
			free(stock);
			free(line_fr_read);
			return (NULL);
		}
		line_fr_read[bytes] = '\0'; // terminate the buffer area
		stock = freebuf_join(stock, line_fr_read); // join stock (initially empty) and buffer line_fr_read
	} // this loop keeps going to fill stock until there is \n (including any trailing characters, if any exist/included). Repeated calls to read overwrites the buffer (line_fr_read), so there is no need to do anything.
	free(line_fr_read); // since stock already contains the buffer line_fr_read, it can be freed (avoid leaks)
	return (stock); // and stock is returned
}

char	*extract_line(char *stock) // [2]
{
	size_t	i;
	char	*extracted;

	i = 0;
	if (!stock[i]) // control. Not really sure why [0], but francinette fails on empty file
		return (NULL);
	while (stock[i] != '\n' && stock[i]) // increment i up to \n to get size
		i++;
	extracted = null_malloc(i + 2, sizeof(char)); // allocate size of extracted according to i, + 2 to include \n and \0
	if (!extracted) // control
		return (NULL);
	i = 0; // reuse the same counter
	while (stock[i] && stock[i] != '\n') // copy stock to extracted up to \n (right before \n)
	{
		extracted[i] = stock[i];
		i++;
	}
	if (stock[i] == '\n') // copy the \n
	{
		extracted[i] = stock[i];
		i++;
	}
	extracted[i] = '\0'; // then terminate with \0
	return (extracted); // returns extracted
}

char	*clean_up(char *stock) // [3]
{
	int		i;
	int		j;
	char	*remains;

	i = 0;
	while (stock[i] != '\0' && stock[i] != '\n') // increment counter until the \n is encountered
		i++;
	if (stock[i] == '\0') // control sequence if there is no more \n (e.g end of file/EOF)
	{
		free(stock);
		return (NULL);
	}
	remains = null_malloc(ft_strlen(stock) - i + 1, sizeof(char)); // allocate remains -> length of stock - extracted [2]
	if (!remains) // control if null_malloc fails
	{
		free(stock);
		return (NULL);
	}
	i++;
	j = 0;
	while (stock[i] != '\0') // copy (stock-extracted) to remains
		remains[j++] = stock[i++];
	remains[j] = '\0'; // terminate remains
	free(stock); // clean stock, because remains is returned and will be put into stock in the get_next_line function 
	return (remains);
}

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
    
    // printf("\nExample 2: Writing to 'grep hello' command\n");
    // printf("------------------------------------------\n");
    // int fd2 = ft_popen("grep", (const char *[]){"grep", "hello", NULL}, 'w');
    // if (fd2 == -1) {
    //     printf("Error opening pipe for writing\n");
    //     return 1;
    // }
    
    // // Write some test data to the grep command
    // write(fd2, "hello world\n", 12);
    // write(fd2, "goodbye world\n", 14);
    // write(fd2, "hello again\n", 12);
    // close(fd2);  // Close to signal EOF to grep
    
    // printf("\nThe grep command only printed lines containing 'hello'\n");
    
    return 0;
}