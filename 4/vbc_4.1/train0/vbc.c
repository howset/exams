#include "vbc.h"

void destroy_tree(node* tree)
{
	if (tree)
	{
		if (tree->type != VAL)
		{
			destroy_tree(tree->l);
			destroy_tree(tree->r);
		}
		free(tree);
	}
}

node *parse_expression(char **s)
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
			return NULL;
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
			return NULL;
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
	node *expr;

	if (accept(s, '('))
	{
		expr = parse_expression(s);
		if (!expect(s, ')'))
		{
			destroy_tree(expr);
			return NULL;
		}
		return (expr);
	}
	return (parse_number(s));
}

node *parse_number(char **s)
{
	node	newnode;
	
	if(isdigit(**s))
	{
		newnode.type = VAL;
		newnode.val = **s - '0';
		newnode.l = NULL;
		newnode.r = NULL;
		(*s)++;
		return (new_node(newnode));
	}
	unexpected(**s);
	return (NULL);
}
