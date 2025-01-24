/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nryser <nryser@student.42lausanne.ch>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:30:00 by nryser            #+#    #+#             */
/*   Updated: 2024/11/28 17:55:11 by nryser           ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*ft_strchr(char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return s;
        s++;
    }
    return NULL;
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	while (n--)
		((char *)dst)[n] = ((char *)src)[n];  // Change n-1 to n
	return dst;
}


size_t ft_strlen(char *s)
{
	size_t len;
	for(len = 0; *s; s++)len++;
	return len;
}



int str_append_mem(char **s1, char *s2, size_t size2)
{
    size_t size1 = (*s1) ? ft_strlen(*s1) : 0;  // Change to Ensure *s1 is properly handled
    char *tmp = malloc(size1 + size2 + 1);
    if (!tmp)
        return 0;

    // If *s1 is not NULL, copy the previous contents
    if (*s1)
	{
        ft_memcpy(tmp, *s1, size1);
		free(*s1);
	}
    // Copy new string or char
    ft_memcpy(tmp + size1, s2, size2);
    tmp[size1 + size2] = '\0';


    *s1 = tmp;

    return 1;
}

//we dont need this 2 functions
// int	str_append_str(char **s1, char *s2)
// {
// 	return str_append_mem(s1, s2, ft_strlen(s2));
// }

// void	*ft_memmove(void *dest, const void *src, size_t n)
// {
// 	if (dest > src)
// 		return ft_memcpy(dest, src, n);
// 	else if (dest == src)
// 		return dest;
// 	for(size_t i = ft_strlen((char*)src) - 1; i >= 0; i--)
// 		((char *)dest)[i] = ((char *)src)[i];
// 	return dest;

// }

#include "get_next_line.h"

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1] = {0};
    static size_t buffer_pos = 0;
    static size_t buffer_len = 0;
    char *line = NULL;
    //size_t line_len = 0;
    ssize_t bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    while (1)
    {
        // If there's data remaining in the buffer, append it to line
        if (buffer_pos < buffer_len)
        {
            char c = buffer[buffer_pos++];
            if (!str_append_mem(&line, &c, 1))
			{
				free(line);
				return NULL;
			}
			//line_len++;

			// If we encounter a newline, return the line
			if (c == '\n')
				return line;
		}
		else
		{
			// No more data in the buffer, read more from the file
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read < 0)  // Error reading file
			{
				free(line);
				return NULL;
			}
			if (bytes_read == 0)  // EOF reached
			{
				if (line)  // Return any line content read so far
					return line;
				return NULL;  // Return NULL if no data was read
			}

			// New data read, reset buffer position and store the length
			buffer_pos = 0;
			buffer_len = bytes_read;
		}
	}
}

