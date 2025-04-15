int	main(int ac, char *av[])
{
	if (ac != 2)
		return (-1);
	char *input = av[1];
	node *tree = parse_low(input);
	if (!tree)
	{
		destroy_tree(tree);
		return (1);
	}
	else if (*input)
	{
		unexpected(*input);
		destroy_tree(tree);
		return (1);
	}
	(printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
	return (0);
}

node	*parse_low(char **s)
{
	node	*left;
	node	*right;
	node	new;
	
	left = parse_mid(s);
	while (accept(s, '+'))
	{
		right = parse_mid(s);
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		n.type = ADD;
		n.l = left;
		n.r = right;
		left = new_node(n);
	}
	return (left);
}

node	*parse_mid(char **s)
{
	node	*left;
	node	*right;
	node	new;
	
	left = parse_high(s);
	while (accept(s, '*'))
	{
		right = parse_high(s);
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		n.type = MULTI;
		n.l = left;
		n.r = right;
		left = new_node(n);
	}
	return (left);
}

node	*parse_high(char **s)
{
	node	*expr;
	
	if (accept(s, '('))
	{
		expr = parse_low(s);
		if (!expect(s, ')'))
		{
			destroy_tree(expr);
			return (NULL);
		}
		return (expr)
	}
	return (parse_numb(s));
}

node	*parse_numb(char **s)
{
	node	*n;
	
	if (isdigit(**s))
	{
		n.type = VAL;
		n.val = **s - '0';
		n.l = NULL;
		n.r = NULL;
		*s++;
		return (new_node(n));
	}
	else
	{
		unexpected(**s);
		return (NULL);
	}
}
