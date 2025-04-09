int	main(int ac, char **av)
{
	char *input;
	node *tree;

	if (ac != 2)
		return 1;
	input = av[1];
	tree = parse_expr(input);
	if (!tree)
	{
		destroy_tree(tree);
		return 1;
	}	
	else if (*input)
	{
		unexpected(*input);
		destroy_tree(tree);
		return (1);
	}
	printf("%d\n", eval_tree(tree));
}

node *parse_expr(char **s)
{
	node	*left;
	node	*right;
	node	newnode;
	
	left = parse_term(s);
	while (accept(s, '+'))
	{
		right = parse_term(s);
		if (!right)
		{
			destroy_tree(left);
			return (NULL); 
		}
		newnode.type = ADD;
		newnode.l = left;
		newnode.r = right;
		left = new_node(newnode);
	}
	return (left);
}

node *parse_term(char **s)
{
	node	*left;
	node	*right;
	node	newnode;
	
	left = parse_factor(s);
	while (accept(s, '*'))
	{
		right = parse_factor(s);
		if (!right)
		{
			destroy_tree(left);
			return (NULL); 
		}
		newnode.type = MULTI;
		newnode.l = left;
		newnode.r = right;
		left = new_node(newnode);
	}
	return (left);
}

node *parse_factor(char **s)
{
	node	*expr;
	
	if(accept(s, '('))
	{
		expr = parse_expr(s);
		if (!expect(s, ')'))
		{
			destroy_tree(expr);
			return (NULL);
		}
		return (expr);
	}
	return (parse_numb(s));
}

node *parse_numb(char **s)
{
	node	newnode;

	if (isdigit(**s))
	{
		newnode.type = VAL;
		newnode.val = **s -'0';
		newnode.l = NULL;
		newnode.r = NULL;
		(*s)++;
		return (new_node(newnode));
	}
	else 
	{
		unexpected(**s);
		return (NULL);
	}
}


