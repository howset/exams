#include <unistd.h>

/* void	ft_putstr(char *str)
{
	int i = 0;

	while (str[i])
		write(1, &str[i++], 1);
}
 */
void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int	main(void)
{
	char *str;

	str = "test";

	ft_putstr(str);
	return(0);
}