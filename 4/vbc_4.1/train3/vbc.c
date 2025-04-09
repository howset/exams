#include "vbc.h"

node *parse_expr(char **s)
{
	node	*left;
	node	*right;
	node	nnode;

	left = parse_term(s);
	while(accept(s, '+'))
	{
		right = parse_term(s);
		if (!right)
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
	node	*right;
	node	nnode;

	left = parse_fact(s);
	while(accept(s, '*'))
	{
		right = parse_fact(s);
		if (!right)
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

node *parse_fact(char **s)
{
	node *expr;

	if (accept(s, '('))
	{
		expr = parse_expr(s);
		if (!expect(s,')'))
		{
			destroy_tree(expr);
			return (NULL);
		}
		return (expr);
	}
	return (parse_numb(s));
}

node* parse_numb(char **s)
{
	node nnode;

	if (isdigit(**s))
	{
		nnode.type = VAL;
		nnode.val = **s - '0';
		nnode.l = NULL;
		nnode.r = NULL;
		(*s)++;
		return (new_node(nnode));
	}
	else
	{
		unexpected(**s);
		return (NULL);
	}
}