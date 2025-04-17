#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

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

void destroy_tree(node* n)
{
	if (n) 
	{
		if (n->type != VAL)
		{
			destroy_tree(n->l);
			destroy_tree(n->r);
		}
		free(n);
	}
}

void	unexpected(char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of input");
}

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

//...solution here:

node *parse_low(char **s);
node *parse_mid(char **s);
node *parse_high(char **s);
node *parse_numb(char **s);

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

//...solution ends

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
}
//main function modified
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
