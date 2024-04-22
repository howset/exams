unsigned int    lcm(unsigned int a, unsigned int b)
{
	int n;
	
	if (a > b)
		n = a;
	else
		n = b;
	while (1)
	{
		if ((n % a == 0) && (n % b == 0))
			return (n);
		n++;
	}
}

#include <stdio.h>

int main(void)
{

	printf("%d\n", lcm(3, 15));
	return (0);
}