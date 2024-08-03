/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:22:51 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/03/27 14:22:52 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int av1;
	int	av3;

	if (argc != 4)
	{
		printf("\n");
		return (0);
	}
	av1 = atoi(argv[1]);
	av3 = atoi(argv[3]);

	if (argv[2][0] == '+')
		printf("%d", (av1 + av3));
	else if (argv[2][0] == '-')
		printf("%d", (av1 - av3));
	else if (argv[2][0] == '*')
		printf("%d", (av1 * av3));	
	else if (argv[2][0] == '/')
		printf("%d", (av1 / av3));
	else if (argv[2][0] == '%')
		printf("%d", (av1 % av3));
	printf("\n");
	return (0);
}