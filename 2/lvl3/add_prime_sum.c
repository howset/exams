#include <unistd.h>

int	ft_atoi(char *nbr)
{
	int res = 0;
	int i = 0;
	while (nbr[i])
	{
		res = res * 10 + nbr[i] - '0';
		i++;
	}
	return(res);
}

void	ft_putnbr(int nbr)
{
	while (nbr > 9)
		ft_putnbr(nbr / 10);
	write(1, &"0123456789"[nbr % 10], 1);
}

int	is_prime(int n)
{
	int i = 2;

	while (i < n)
	{
		if (n % i == 0)
			return(0);
		++i;
	}
	return(1);
}

/* int	main(int argc, char *argv[])
{
	int nbr;
	int sum;

	nbr = ft_atoi(argv[1]);
	sum = 0;
	if (argc == 2)
	{
		while (nbr > 0)
		{
			if (is_prime(nbr))
			{
				sum = sum + nbr;
			}
			nbr--;
		}
		ft_putnbr(sum);
	}
	write(1, "\n", 1);
	return(0);
} */

int		add_prime_sum(int n)
{
	int sum = 0;
	int i = 2;

	while (i <= n)
	{
		if (is_prime(i) == 1)
			sum += i;
		++i;
	}
	return (sum);
}

int		main(int argc, char **argv)
{
	int n;

	if (argc == 2 && (n = ft_atoi(argv[1])))
		ft_putnbr(add_prime_sum(n));
	else
		ft_putnbr(0);
	write(1, "\n", 1);
	return (0);
}