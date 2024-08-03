/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:39:32 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/03/28 11:51:12 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *ft_strrev(char *str)
{
	char	temp;
	int	i = 0;
	int	j = 0;

	while (str[i])
		i++;
	i--;
	while (j < i)
	{
		temp = str[j];
		str[j] = str[i];
		str[i] = temp;
		j++;
		i--;
	}
	return (str);
}

#include <stdio.h>
int	main(void)
{
	char	res[] = "Dogdog catcat1";
	ft_strrev(res);
	printf("Res: %s\n", res);
	return (0);
}