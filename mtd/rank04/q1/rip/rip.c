/*
 * Trim the )'s in the beggining, ('s at the end
 * Get the unsigned count of chars disturbing the balance
 *
 */


#include <stdio.h>
#include <stdbool.h>

#define TERMINATING_NULL 0

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

/* When need_o gets incremented, there's not way to rectify that in rec call,
 * that's pure invalid and is used for counting purposes only */
int	get_off_count(char *s, int need_c, int need_o)
{
	if (s[0] == TERMINATING_NULL)
		return (need_c + need_o);
	if (s[0] == ' ' || s[0] == '_')
		return (get_off_count(&s[1], need_c, need_o));
	if (s[0] == '(')
		return (get_off_count(&s[1], need_c + 1, need_o));
	if (s[0] == ')')
	{
		if (need_c)
			return (get_off_count(&s[1], need_c - 1, need_o));
		return (get_off_count(&s[1], need_c, need_o + 1));
	}
}

void	backtrack_print(char *s, int idx, int hm_off)
{
	if (s[idx] == TERMINATING_NULL) // base case
	{
		if (get_off_count(s, 0, 0) == 0 && hm_off == 0)
			puts(s);
		return ;
	}	
	if (s[idx] == ' ' || s[idx] == '_' || hm_off == 0) // next idx
		backtrack_print(s, idx + 1, hm_off);
	else
	/* (1) next idx
	   (2) if hm_off, next idx. but curr idx = '_' and hm_off--
	   once back, set char back to ')' or '('	*/
	{
		backtrack_print(s, idx + 1, hm_off);
		if (hm_off > 0)
		{
			char	tmp = s[idx];  // either '(' or ')'
			s[idx] = '_';
			backtrack_print(s, idx + 1, hm_off - 1);
			s[idx] = tmp;
		}
	}
}

void	trim_parentheses(char *s, char *argv1)
{
	int	i = -1;
	int	len = ft_strlen(argv1);
	bool	first_open = false;

	while (++i < len)
	{
		s[i] = argv1[i];
		if (s[i] == '(')
			first_open = true;
		if (s[i] == ')' && !first_open)
			s[i] = '_';
	}
	s[i] = 0;
	i = len;
	while (--i >= 0)
	{
		if (s[i] == ')')
			break ;
		if (s[i] == '(')
			s[i] = '_';
	}
}

int	main(int argc, char **argv)
{
	int	how_many_off;

	if (argc != 2)
		return (1);
	if (argv[1][0] == TERMINATING_NULL)
		return (puts(""));

	// return if balanced
	how_many_off = get_off_count(argv[1], 0, 0);
	printf("how_many_off in argv[1]: %d\n", how_many_off);
	if (how_many_off == 0)
		return (puts(argv[1]));

	char	trimmed[ft_strlen(argv[1])];
	trim_parentheses(trimmed, argv[1]);
	printf("rectified string: %s\n", trimmed);
	how_many_off = get_off_count(trimmed, 0, 0);
	printf("how_many_off after rectification: %d\n", how_many_off);
	backtrack_print(trimmed, 0, how_many_off);
}
