/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsetyamu <hsetyamu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:31:50 by hsetyamu          #+#    #+#             */
/*   Updated: 2024/03/28 14:39:48 by hsetyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned char	reverse_bits(unsigned char octet)
{
	unsigned int	i = 8;
	unsigned char	bits = 0;

	while (i)
	{
		i--;
		bits = (bits << 1) | (octet & 1);
		octet = octet >> 1;
	}
	return (bits);
}

#include <unistd.h>

int	main(void)
{
	unsigned char bit = 0;
	unsigned char res = reverse_bits((unsigned char)'d');

	int i = 8;
	while (i)
	{
		i--;
		bit = (res >> i & 1);
		bit = bit + '0';
		write(1, &bit, 1);
	}
}