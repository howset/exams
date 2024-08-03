char tolower(char *str)
{
	char *res;
	int i = 0;

	while (str[i])
	{
		if(str[i] >= 'A' && str[i] <= 'Z')
			res[i] = str[i] + 32;
		else
			res[i] = str[i];
	}
	return(res);
}

int g_dig(char c, int str_base)
{
	int	max;

	if (str_base <= 10)
		max = str_base + '0';
	else
		max = str_base + 'a' - 10;
	if ((c >= '0' && c <= '9') && c <= max)
		return(c - '0');
	else if ((c >= 'a' && c <= 'z') && c <= max)
		return(c - 'a' + 10);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	i = 0;
	int	neg_flag = 1;
	int res;
	char *lowcase;

	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '-')
		neg_flag = -1;
	lowcase = tolower(str);
	while (g_dig(lowcase, str_base) >= 0)
	{
		res = res * str_base + 
	}
	 
}