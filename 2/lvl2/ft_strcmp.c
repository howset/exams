/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:41:18 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/03/28 10:41:19 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	int	i = 0;

	while ((s1[i] != '\0' || s2[i] != '\0') && s1[i] == s2[i])
		i++;
	return(s1[i]-s2[i]);
}

#include <stdio.h>
#include <string.h>
int main(void)
{
	printf("rl_strcmp: %d\n", strcmp("dogcat", "dog"));
	printf("ft_strcmp: %d\n", ft_strcmp("dogcat", "dog"));
	printf("rl_strcmp: %d\n", strcmp("dog", "dogcat"));
	printf("ft_strcmp: %d\n", ft_strcmp("dog", "dogcat"));
}