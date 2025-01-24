/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nryser <nryser@student.42lausanne.ch>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:27:03 by nryser            #+#    #+#             */
/*   Updated: 2024/11/19 17:28:34 by nryser           ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */



#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Failed to open file");
        return 1;
    }

    printf("File opened successfully.\n");

    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Read line: %s\n", line ? line : "No line read");

        free(line);
    }

    printf("End of file or error.\n");
    close(fd);
    return 0;
}

//to make it work put this command :
// gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line.h  main.c -o gnl

// to run it put this command :
// ./gnl test.txt

//to check leaks put this command :
// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./gnl test.txt

