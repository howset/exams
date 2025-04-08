/*
 * This version was trying to differentiate between '(' and ')' by returning -1 and +1,
 * but it backfired for '( ) ) (' bc the difference would be 0, same as for '( ) ( )'
*/

#include <stdio.h>
#include <stdbool.h>

#define TERMINATING_NULL 0
#define OK 0

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s || !(*s))
		return 0;
	while (s[i])
		i++;
	return (i);
}

int	is_balanced(char *s, int o, int c, int need_c, int need_o)
{
	if (s[0] == TERMINATING_NULL)  // if at the end of the string
	{
		printf("o: %d, c: %d, need_o: %d, need_c: %d\n", o, c, need_o, need_c);
		return (need_c - need_o);
	}
	if (s[0] == ' ' || s[0] == '_')
		return (is_balanced(&s[1], o, c, need_c, need_o));
	if (s[0] == '(')
	{
		return (is_balanced(&s[1], o + 1, c, need_c + 1, need_o));
	}
	if (s[0] == ')')
	{
		if (need_c)
			return (is_balanced(&s[1], o, c + 1, need_c - 1, need_o));
		return (is_balanced(&s[1], o, c + 1, need_c, need_o + 1));
	}
}

void	backtrack_print(char *s, int idx, int o, int c, int hm)
{
	// base case
	if (s[idx] == TERMINATING_NULL)
	{
		if (is_balanced(s, 0, 0, 0, 0) == OK && hm == 0)
			puts(s);
		return ;
	}
	if (s[idx] == ' ' || s[idx] == '_' || hm == 0)
		backtrack_print(s, idx + 1, o, c, hm);
	else if (s[idx] == '(')
	{
		backtrack_print(s, idx + 1, o + 1, c, hm);
		if (hm > 0)
		{
			s[idx] = '_';
			backtrack_print(s, idx + 1, o + 1, c, hm - 1);
			s[idx] = '(';
		}
	}
	else if (s[idx] == ')')
	{
		backtrack_print(s, idx + 1, o, c + 1, hm);
		if (hm < 0)
		{
			s[idx] = '_';
			backtrack_print(s, idx + 1, o, c + 1, hm + 1);
			s[idx] = ')';
		}
	}
}

int	main(int argc, char **argv)
{
	int	how_many_off;

	if (argc != 2)
		return (1);
	if (argv[1][0] == TERMINATING_NULL)
		return (puts(""));
	how_many_off = is_balanced(argv[1], 0, 0, 0, 0);
	if (how_many_off == 0)
		return (puts(argv[1]));
	else
		printf("is not balanced, bias: %d\n", how_many_off);
	char	auto_arr[ft_strlen(argv[1]) + 1];
	int	i = -1;
	bool	first_open = false;
	bool	final_close = false;
	while (++i < ft_strlen(argv[1]))
	{
		auto_arr[i] = argv[1][i];
		if (!first_open && argv[1][i] == '(')
			first_open = true;
		if (!first_open && argv[1][i] == ')')
			auto_arr[i] = '_';
	}
	auto_arr[i] = 0;
	while (--i >= 0)
	{
		if (argv[1][i] == ')')
			break ;
		if (argv[1][i] == '(')
			auto_arr[i] = '_';
	}
	printf("rectified string: %s\n", auto_arr);
	how_many_off = is_balanced(auto_arr, 0, 0, 0, 0);
	printf("how_many_off in auto_arr: %d\n", how_many_off);
	backtrack_print(auto_arr, 0, 0, 0, how_many_off);
}
