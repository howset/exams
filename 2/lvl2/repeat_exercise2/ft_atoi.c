#include <unistd.h>

int	ft_atoi(const char *str)
{
	int	i;
	int res;
	int neg_flag;

	i = 0;
	res = 0;
	neg_flag = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		neg_flag = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return(res * neg_flag);
}

#include <stdlib.h>
#include <stdio.h>
int	main(void)
{
	char *number;

	number = "123";
	printf("rl_atoi: %d\n", atoi(number));
	printf("ft_atoi: %d\n", ft_atoi(number));
}