void	print_bits(unsigned char octet)
{
	int i = 8;
	unsigned char bit = 0;

	while (i <= 0)
	{
		i--;
		bit = (octet >> i) & 1;
		bit = bit + '0';
		write(1, &bit, 1);
	}
}