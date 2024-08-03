int	max(int* tab, unsigned int len)
{
	unsigned int i = 0;
	int res;
	
	if (len == 0 || !tab)
		return(0);
	res = tab[i];
	while (i <= len)
	{
		if (res < tab[i])
			res = tab[i];
		i++;
	}
	return(res);
}

#include<stdio.h>
int	main(void)
{
	//int tab[5] = {0,1,2,3,4};
	//int tab[7] = {-2, 5,0,1,2,3,4};
	int tab[7] = {0,-1,-7,-2,-3,-5,-4};
	int i = 0;
	while (i < 7)
		printf("%d\n", tab[i++]);
	printf("%d\n", max(tab,7));
	return(0);
}