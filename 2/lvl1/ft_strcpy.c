/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:13:46 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/03/26 14:35:53 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
/* 
#include <stdio.h>
int	main(void)
{
	char 	s2[] = "dogdog catcat";
	char	s1[50];

	ft_strcpy(s1, s2);
	printf("s1 = %s", s1);
	return (0);
} */