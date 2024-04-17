unsigned char	reverse_bits(unsigned char octet)
{
	int i = 8;
	unsigned char bit = 0;

	while (i > 0)
	{
		i--;
		bit = (bit << 1) | (octet & 1);
		octet = octet >> 1;
	}
	return(bit);
}

#include <unistd.h>
int	main(void)
{
	unsigned char octet;
	int i = 8;
	unsigned char bit = 0;

	octet = reverse_bits('d');
	while (i > 0)
	{
		i--;
		bit = (octet >> i) & 1;
		bit = bit + '0';
		write(1, &bit, 1);
	}
	return(0);
}