/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:56:04 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/03/27 18:56:06 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char *src)
{
	int	i = 0;
	char	*res;

	while (src[i])
		i++;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (src[i])
	{
		res[i] = src[i];
		i++;
	}
	return (res);
}

#include <stdio.h>
#include <string.h>

int main()
{
	char	*a;
	a = "Catcat DogdogDog";
	printf("rl_strdup: %s\n", strdup(a));
	printf("ft_strdup: %s\n", ft_strdup(a));
}