/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:07:51 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/04/15 15:43:41 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void print_bits(unsigned char octet)
{
	int i = 8;
	unsigned char bit = 0;

	while (i)
	{
		i--;
		bit = (octet >> i) & 1;
		bit = bit + '0';
		write(1, &bit, 1);
	}
}

int main(void)
{
	unsigned char octet = 'd';

	print_bits(octet);
	return (0);
}