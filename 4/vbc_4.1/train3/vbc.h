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

//main.c
node	*new_node(node n);
void	unexpected(char c);
int	accept(char **s, char c);
int	expect(char **s, char c);
int	eval_tree(node *tree);
void destroy_tree(node* tree);

//vbc.c
node	*parse_expr(char **s);
node	*parse_term(char **s);
node	*parse_fact(char **s);
node	*parse_numb(char **s);
