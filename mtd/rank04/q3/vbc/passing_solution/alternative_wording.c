#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <stdlib.h>
#include <stddef.h>

typedef struct node {
	enum {
		ADD,
		MULTI,
		VAL
	}   type;
	int val;
	struct node *l;
	struct node *r;
}   node;


node *if_lowest_prio(char **s);


node * new_node(node n)
{
	node *ret = calloc(1, sizeof(node));
	if (!ret)
		return (NULL);
	*ret = n;
	return (ret);
}

void destroy_tree(node *n)
{
	if (!n)
		return ;
	if (n->type != VAL)
	{
		destroy_tree(n->l);
		destroy_tree(n->r);
	}
	free(n);
}

void unexpected_char(char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of input \n");
}

int accept(char **s, char c)
{
	if (**s == c)
	{
		(*s)++;
		return (1);
	}
	return (0);
}

int expect(char **s, char c)
{
	if (accept(s,c))
		return (1);
	unexpected_char(**s);
	return (0);
}

int eval_tree(node *tree)
{
	switch (tree->type)
	{
		case ADD:
			return (eval_tree(tree->l) + eval_tree(tree->r));
		case MULTI:
			return (eval_tree(tree->l) * eval_tree(tree->r));
		case VAL:
			return (tree->val);
	}
	return 0;
}


node *extract_num(char **s)
{
	if (isdigit(**s))
	{
		node n = { .type = VAL, .val = **s - '0', .l = NULL, .r = NULL };
		accept(s, **s);
		return new_node(n);
	}
	unexpected_char(**s);
	return NULL;
}

node *if_highest_prio(char **s)
{
	if (accept(s, '('))
	{
		node *ret = if_lowest_prio(s);
		if (!expect(s, ')'))
		{
			destroy_tree(ret);
			return NULL;
		}
		return ret;
	}
	return extract_num(s);
}

node *if_middle_prio(char **s)
{
	node *ret = if_highest_prio(s);
	while (accept(s, '*'))
	{
		node *right = if_highest_prio(s);
		if (!right) {
			destroy_tree(ret);
			return NULL;
		}
		node n = { .type = MULTI, .l = ret, .r = right };
		ret = new_node(n);
	}
	return ret;
}

node *if_lowest_prio(char **s)
{
	node *ret = if_middle_prio(s);
	while (accept(s, '+'))
	{
		node *right = if_highest_prio(s);
		if (!right) {
			destroy_tree(ret);
			return NULL;
		}
		node n = { .type = ADD, .l = ret, .r = right };
		ret = new_node(n);
	}
	return ret;
}

node *parse_expr(char **s)
{
	node *ret = if_lowest_prio(s);
	if(**s)
	{
		unexpected_char(**s);
		destroy_tree(ret);
		return (NULL);
	}
	return (ret);
}

int main (int argc, char** argv)
{
	if (argc!= 2)
		return 1;
	char *input = argv[1];
	node *tree = parse_expr(&input);
	if (!tree)
		return 1;
	printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
	return (0);
}
