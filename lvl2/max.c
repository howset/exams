/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:26:27 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/03/28 12:26:28 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	max(int* tab, unsigned int len)
{
	unsigned int	i = 0;
	int res;

	if (len == 0)
		return (0);
	res = tab[i];
	while (i < len)
	{
		if (res < tab[i] )
			res = tab[i];
		i++;
	}
	return (res);
}

#include <stdio.h>

int main()
{
	int tab[] = {-3, -2, -1, -10, -9};
	//int tab[] = {-3, -2, -1, 10, -9};
	printf("%d", max(tab, 5));
}