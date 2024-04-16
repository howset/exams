#include <stdlib.h>

size_t	ft_strspn(const char *s, const char *accept)
{
	int	i;
	int j;
	int	flag;

	i = 0;
	while (s[i])
	{
		j = 0;
		flag = 0;
		while (accept[j])
		{
			if (s[i] == accept[j])
				flag = 1;
			j++;
		}
		if (flag == 0)
			return(i);
		i++;
	}
	return(i);
}

#include <stdio.h>
#include <string.h>
int	main(void)
{
	char *s1;
	char *s2;
	s1 = "locates";
	//s2 = "cat";
	s2 = "ate";
	printf("rl_strspn: %lu\n", strspn(s1, s2));
	printf("ft_strspn: %lu\n", ft_strspn(s1, s2));
}