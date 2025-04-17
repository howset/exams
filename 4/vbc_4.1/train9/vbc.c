int main(int c, char *v[])
{
	if (c != 2)
		return (1);
	char *inp = v[1];
	node *tree = parse_low(inp);
	if (!tree)
	{
		desstroy_tree(tree);
		return (1);
	}
	else if (*inp)
	{
		unexpected(*inp);
		destroy_tree(tree);
		return (1);
	}
	printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
	return (0);
}

node *parse_low(char **s)
{
	node	*left;
	node	*right;
	node	n;
	
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

node *parse_mid(char **s)
{
	node	*left;
	node	*right;
	node	n;
	
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

node *parse_high(char **s)
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
		return (expr);
	}
	else
		return (parse_numb(s));
}

node *parse_numb(char **s)
{
	node	numb;
	
	if (isdigit(s))
	{
		numb.type = VAL;
		numb.val = **s - '0';
		numb.l = NULL;
		numb.r = NULL;
		*s++;
		return (new_node(numb));	
	}
	else
	{
		unexpected(**s);
		return(NULL);
	}
}
