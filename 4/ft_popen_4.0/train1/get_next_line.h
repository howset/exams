/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:47:24 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/02/19 14:19:02 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h> // free malloc
# include <unistd.h> // read
# include <fcntl.h> // O_RDONLY
# include <stdint.h> // SIZE_MAX

char	*get_next_line(int fd);
char	*read_line(int fd, char *stock);
char	*extract_line(char *stock);
char	*clean_up(char *stock);

char	*null_malloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char *str);
char	*freebuf_join(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);

#endif