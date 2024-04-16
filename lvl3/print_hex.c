#include <unistd.h>

int ft_atoi(char *str)
{
    int res = 0; 
	int i = 0;

    while (str[i] && str[i] >= '0' && str[i] <= '9')
    {
		res = res * 10 + str[i] -'0';
		i++;
    }
    return (res);
}

void put_hex(int nbr)
{
    if (nbr >= 16)
        put_hex(nbr / 16);
    write(1, &"0123456789abcdef"[nbr % 16], 1);
}

int main(int ac, char **av)
{
    if (ac == 2)
        put_hex(ft_atoi(av[1]));
    write(1, "\n", 1);
    return (0);
}