#include <unistd.h>

void	ft_putnbr(int n)
{
	if (n > 9)
		ft_putnbr(n / 10);
	write(1, &"0123456789"[n % 10], 1);	
}

int main(int argc, char *argv[])
{
	int n;

	(void)argv;
	if (argc)
	{
		n = argc - 1;
		ft_putnbr(n);
	}
	write(1, "\n", 1);
	return (0);
}