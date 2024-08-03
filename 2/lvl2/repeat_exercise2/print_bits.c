#include <unistd.h>
void	print_bits(unsigned char octet)
{
	int	i;
	unsigned char	bit;

	i = 8;
	bit = 0;
	while (i > 0)
	{
		i--;
		bit = (octet >> i) & 1;
		bit = bit + '0';
		write(1, &bit, 1);
	}
	
}

#include <stdio.h>
int	main(void)
{
	unsigned char octet;

	octet = 'd';
	print_bits(octet);
	return(0);
}