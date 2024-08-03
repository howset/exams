/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:41:24 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/04/16 13:57:04 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(char *str)
{
	int	i = 0;
	int neg_flag = 1;
	int res = 0;
	
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		neg_flag = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (neg_flag * res);
}

#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	printf("rl_atoi: %d\n", atoi("  ---678a"));
	printf("ft_atoi: %d\n", ft_atoi("  ---678a"));
	printf("rl_atoi: %d\n", atoi("  -678"));
	printf("ft_atoi: %d\n", ft_atoi("  -678"));
}