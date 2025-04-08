/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nryser <nryser@student.42lausanne.ch>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:32:01 by nryser            #+#    #+#             */
/*   Updated: 2024/11/21 16:32:15 by nryser           ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif
# include <stdlib.h>
# include <unistd.h>
# include <string.h>  // For NULL
# include <fcntl.h>   // For open, read, close
# include <stdio.h>   // For debugging (can be removed later)

// Function prototype for get_next_line
char    *get_next_line(int fd);


#endif
