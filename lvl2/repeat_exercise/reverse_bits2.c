unsigned char	reverse_bits(unsigned char octet)
{
	int i = 8;
	unsigned char bit = 0;

	while (i >= 0)
	{
		i--;
		bit = (bit << 1) | (octet & 1);
		octet = octet >> 1;
	}
	return(bit);
}