#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	enum {
		ADD,
		MULTI,
		VAL
	} type;
	int		val;
	struct node	*l;
	struct node	*r;
} node;

node	*new_node(node n)
{
	node *ret = calloc(1, sizeof(node));
	if (!ret)
		return NULL;
	*ret = n;
	return ret;
}

void	unexpected(char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of input");
}

int	accept(char **s, char c)  //here **s
{
	if (**s == c)
	{
		(*s)++;
		return 1;
	}
	return 0;
}

int	expect(char **s, char c) //here **s
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
	//return (0);
}

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

node *parse_expr(char **s);

node *parse_fact(char **s)
{
	node *expr;
	
	if (accept(s, '('))
	{
		expr = parse_expr(s);
		if(!expect(s, ')'))
		{
			destroy_tree(expr);
			return (NULL);
		}
		return (expr);
	}
	else
		return(parse_numb(s));
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

int	main(int ac, char **av) //overhauled
{
	char *input;
	node *tree;

	if (ac != 2)
		return 1;
	input = av[1];
	tree = parse_expr(&input);
	if (!tree)
	{
		destroy_tree(tree);
		return 1;
	}
	else if (*input)
	{
		unexpected(*input);
		destroy_tree(tree);
		return 1;
	}
	printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
}
