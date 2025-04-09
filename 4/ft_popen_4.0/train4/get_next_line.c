/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:47:05 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/02/19 15:50:21 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *stock);
char	*extract_line(char *stock);
char	*clean_up(char *stock);

char	*get_next_line(int fd)
{
	char		*extracted;
	static char	*stock = NULL;
	char		*remains;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (stock != NULL)
			free(stock);
		return (NULL);
	}
	stock = read_line(fd, stock);
	if (!stock)
		return (NULL);
	extracted = extract_line(stock);
	remains = clean_up(stock);
	stock = remains;
	return (extracted);
}

char	*read_line(int fd, char *stock)
{
	int		bytes;
	char	*line_fr_read;

	if (!stock)
		stock = null_malloc(1, sizeof(char));
	line_fr_read = null_malloc(BUFFER_SIZE + 1, sizeof(char));
	if (!line_fr_read)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(stock, '\n') && bytes != 0)
	{
		bytes = read(fd, line_fr_read, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(stock);
			free(line_fr_read);
			return (NULL);
		}
		line_fr_read[bytes] = '\0';
		stock = freebuf_join(stock, line_fr_read);
	}
	free(line_fr_read);
	return (stock);
}

char	*extract_line(char *stock)
{
	size_t	i;
	char	*extracted;

	i = 0;
	if (!stock[i])
		return (NULL);
	while (stock[i] != '\n' && stock[i])
		i++;
	extracted = null_malloc(i + 2, sizeof(char));
	if (!extracted)
		return (NULL);
	i = 0;
	while (stock[i] && stock[i] != '\n')
	{
		extracted[i] = stock[i];
		i++;
	}
	if (stock[i] == '\n')
	{
		extracted[i] = stock[i];
		i++;
	}
	extracted[i] = '\0';
	return (extracted);
}

char	*clean_up(char *stock)
{
	int		i;
	int		j;
	char	*remains;

	i = 0;
	while (stock[i] != '\0' && stock[i] != '\n')
		i++;
	if (stock[i] == '\0')
	{
		free(stock);
		return (NULL);
	}
	remains = null_malloc(ft_strlen(stock) - i + 1, sizeof(char));
	if (!remains)
	{
		free(stock);
		return (NULL);
	}
	i++;
	j = 0;
	while (stock[i] != '\0')
		remains[j++] = stock[i++];
	remains[j] = '\0';
	free(stock);
	return (remains);
}

/*
#include <stdio.h>

int main(void)
{
	int	fd;
	char	*line = NULL;
	int	lines;

	lines = 1;
	fd = open("lorem1.txt", O_RDONLY);
	while((line = get_next_line(fd)))
		printf("%d ->%s\n", lines++, line);
	close(fd);
}
*/