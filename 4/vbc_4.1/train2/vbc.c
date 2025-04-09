int	main(int ac, char **av)
{
	char *input;
	node *tree;
	
	if (ac != 2)
		return (1);
	input = av[1];
	tree = parse_expr(input);
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
	printf("%d\n", eval_tree(tree));
}

node *parse_expr(char **s)
{
	node	*left;
	node 	*right;
	node	nnode;
	
	left = parse_term(s);
	while(accept(s, '+'))
	{
		if(!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		nnode.type = ADD;
		nnode.l = left;
		nnode.r = right;
		left = new_node(nnode);
	}
	return (left);
}

node *parse_term(char **s)
{
	node	*left;
	node 	*right;
	node	nnode;
	
	left = parse_factor(s);
	while(accept(s, '*'))
	{
		if(!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		nnode.type = MULTI;
		nnode.l = left;
		nnode.r = right;
		left = new_node(nnode);
	}
	return (left);
}

node *parse_factor(char **s)
{
	node	*expr;
	
	if (accept(s, '('))
	{
		expr = parse_exp(s);
		if(!expect(s, ')'))
		{
			destroy_tree(expr);
			return (NULL);
		}
		return (expr);
	}
	return (parse_num(s));
}

node *parse_num(char **s)
{
	node	nnode;
	
	if(isdigit(**s))
	{
		nnode.type = VAL;
		nnode.val = **s - '0';
		nnode.l = NULL;
		nnode.r = NULL;
		(*s)++;
		return(new_node(nnode));
	}
	else
	{
		unexpected(**s);
		return (NULL);
	}
}
