/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameechan <ameechan@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:19:56 by ameechan          #+#    #+#             */
/*   Updated: 2024/12/27 18:59:56 by ameechan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//CAUTION: memmem() cannot be used anymore!
//allowed functions as of Nov 21 2024:
//strlen, printf, perror, read, malloc, calloc, realloc, free

/*
Write a program that takes one and only one parameter `s`.

The program should take the standard output and replace
every instance of `s` inside it with a corresponding number of "*".
It should then print it to the standard output and return 0.

If the program encounters an error when executing malloc or read,
it should output "Error: " followed by the corresponding error code,
to the standard error output and return 1.

Your program is generally equivalent to the
filter.sh shell script we have provided.

If the program is run with no parameter,
an empty parameter, or multiple parameters,
it should return 1.

Usage:
$> echo testa | ./filter est | cat -e
t***a$

$> echo 1234512345 | ./filter 234 | cat -e
1***51***5$


*/


int	handle_error()
{
	perror("Error"); //(perrror automatically adds a colon and a space after the error message)
	return (1);
}

int	strings_match(char *buf, char *ndl, size_t len)
{
	size_t	i = 0;

	while (i < len)
	{
		if (buf[i] != ndl[i]) //return false as soon as two characters don't match
			return (0);
		i++;
	}
	return (1);//	both strings match, return 1
}

int	main(int ac, char **av)
{
	char	*buf;
	int		buffer_size = 20;
	int		total_read = 0;
	int		bytes_read = 0;

	if (ac != 2 || av[1] == 0) //if empty paramater, no parameter or multiple parameters return 1
		return (1);
	buf = malloc(buffer_size); //allocate memory for buf
	if (!buf)
		return(handle_error());

	//read in a loop appending to buf with each iterration until 0 (end of file)
	//add total_size to buffer each loop to ensure read doesn't overwrite data already stored in buf
	//substract total_size from buffer size to ensure you don't read out of bounds
	while ((bytes_read = read(0, buf + total_read, buffer_size - total_read)) > 0)
	{
		total_read += bytes_read;//		keep track of total_size

//											dynamically allocate more memory to buf
		if (total_read >= buffer_size)//	if total_size goes over max capacity
		{
			buffer_size *= 2;
			buf = realloc(buf, buffer_size);
			if (!buf)
				return(handle_error());
		}
	}
	//return an error if read returned -1
	if (bytes_read < 0)
		return(handle_error());

	//Null terminate string captured from stdin
	buf[total_read] = '\0';

	int i = 0;
	while (buf[i]) //loop through buf until end of string
	{
		if (strings_match(&buf[i], av[1], strlen(av[1]))) //if strings match, replace with stars
		{
			int	j = 0;
			while (j < (int)strlen(av[1])) //strlen retruns size_t, cast to int to avoid warning
			{
				buf[i + j] = '*';
				j++;
			}
			i += j;
		}
		else	//otherwise continue to next character
		{
			i++;
		}
	}
	//print buf to stdout
	printf("%s", buf);
	return (0);
}


// to compile use gcc -Wall -Wextra -Werror -o program filter.c
// to run use ./program <needle> < files/test1.txt

