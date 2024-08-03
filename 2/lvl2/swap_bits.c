unsigned char	swap_bits(unsigned char octet)
{
	return ((octet << 4) | (octet >> 4));
}

#include <unistd.h>

int	main(void)
{
	unsigned char bit = 0;
	unsigned char res = swap_bits((unsigned char)'d');

	int i = 8;
	while (i)
	{
		i--;
		bit = (res >> i & 1);
		bit = bit + '0';
		write(1, &bit, 1);
	}
}