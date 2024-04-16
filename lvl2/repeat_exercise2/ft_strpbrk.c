char	*ft_strpbrk(const char *s1, const char *s2)
{
	int	i;

	while (*s1)
	{
		i = 0;
		while (s2[i])
		{
			if (*s1 == s2[i])
				return((char *)s1);
			i++;
		}
		s1++;
	}
	return(0);
}

#include <stdio.h>
#include <string.h>
int	main(void)
{
	char *s1;
	char *s2;
	s1 = "location";
	s2 = "cat";
	printf("rl_strpbrk: %s\n", strpbrk(s1, s2));
	printf("ft_strpbrk: %s\n", ft_strpbrk(s1, s2));
}