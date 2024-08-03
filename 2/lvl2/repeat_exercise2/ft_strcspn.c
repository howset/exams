#include <stdlib.h>

size_t	ft_strcspn(const char *s, const char *reject)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (reject[j])
		{
			if (s[i] == reject[j])
				return(i);
			j++;
		}
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
	printf("rl_strcspn: %lu\n", strcspn(s1, s2));
	printf("ft_strcspn: %lu\n", ft_strcspn(s1, s2));
}