#include <unistd.h>

int	ft_atoi(char *nbr)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (nbr[i] && nbr[i] >= '0' && nbr[i] <= '9')
	{
		res = res * 10 + nbr[i] - '0';
		i++;
	}
	return(res);
}

void	ft_putnbr(int nbr)
{
	if (nbr > 9)
		ft_putnbr(nbr / 10);
	write(1, &"0123456789"[nbr % 10], 1);
}

int	main(int argc, char *argv[])
{
	int i;
	int nbr;
	
	i = 1;
	nbr = ft_atoi(argv[1]);
	if (argc == 2)
	{
		while (i <= 9)
		{
			ft_putnbr(i);
			write(1, " x ", 3);
			ft_putnbr(nbr);
			write(1, " = ", 3);
			ft_putnbr(i * nbr);
			write(1, "\n", 1);
			i++;
		}
	}
	else
		write(1, "\n", 1);
	return(0);
}
