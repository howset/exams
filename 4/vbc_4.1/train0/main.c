#include "vbc.h"

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

int	accept(char **s, char c)  //changed from *s to **s
{
	if (**s == c)
	{
		(*s)++;
		return 1;
	}
	return 0;
}

int	expect(char **s, char c) //changed from *s to **s
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
}

int	main(int ac, char **av) //overhauled
{
	char *input;
	node *tree;

	if (ac != 2)
		return 1;
	input = av[1];
	tree = parse_expression(&input);
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
