unsigned char	reverse_bits(unsigned char octet)
{
	int i;
	unsigned char bit;

	i = 8;
	bit = 0;
	while (i > 0)
	{
		i--;
		bit = (bit << 1) | (octet & 1);
		octet = octet >> 1; 
	}
	return (bit);
}

#include <unistd.h>

int	main(void)
{
	unsigned char bit = 0;
	unsigned char res = reverse_bits('d');

	int i = 8;
	while (i > 0)
	{
		i--;
		bit = (res >> i) & 1;
		bit = bit + '0';
		write(1, &bit, 1);
	}
}