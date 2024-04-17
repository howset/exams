unsigned char	swap_bits(unsigned char octet)
{
	return((octet << 4 | octet >> 4));
}

#include <unistd.h>
int main(void)
{
	int i = 8;
	unsigned char octet;
	unsigned char bit = 0;

	octet = swap_bits('d');
	while (i > 0)
	{
		i--;
		bit = (octet >> i) & 1;
		bit = bit + '0';
		write(1, &bit, 1);
	}
	return(0);
}