int	accept(char **s, char c)
{
	if (**s == c)
	{
		(*s)++;
		return 1;
	}
	return 0;
}

int	expect(char **s, char c)
{
	if (accept(s, c))
		return 1;
	unexpected(**s);
		return 0;
}

int	eval_tree(node *tree)
{
	switch (tree->type)
	{
		case ADD:
			return (eval_tree(tree->l) + eval_tree(tree->r));
		case MULTI:
			return (eval_tree(tree->l) * eval_tree(tree->r));
		case VAL:
			return tree->val;
	}
	return (0);
}


int	main(int ac, char **av)
{
	if (ac != 2)
		return 1;
	char *input = av[1];
	node *tree = pars_expr(input);
	if (!tree)
	{
		destroy_tree(tree);
		return 1;
	}
	else if (*input)
	{
		(unexpected(*input));
		destroy_tree(tree);
		return 1;
	}
	printf("%d\n", eval_tree(tree));
}

node *parse_expr(char **s)
{
	node *left;
	node *right;
	node newnode;
	
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
	node *left;
	node *right;
	node newnode;
	
	left = parse_fact(s);
	while (accept(s, '*'))
	{
		right = parse_fact(s);
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

node *parse_fact(char **s)
{
	node *expr
	
	if (accept(s, '('))
	{
		expr = parse_expr(s);
		if (!expect(s, ')'))
		{
			destroy_tree(expr);
			return (NULL);
		}
		return (expr)
	}
	return (parse_numb(s));
}

node *parse_numb(char **s)
{
	node newnode;
	
	if (isdigit(**s))
	{
		newnode.type = VAL;
		newnode.val = **s - '0';
		newnode.l = NULL;
		newnode.r = NULL;
		(*s)++;
		return(new_node(newnode));
	}
	else
	{
		unexpected(**s);
		return(NULL);
	}
}
