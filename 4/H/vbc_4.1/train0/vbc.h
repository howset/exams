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
int	accept(char **s, char c); //changed from *s to **s
int	expect(char **s, char c); //changed from *s to **s
int	eval_tree(node *tree);
void	destroy_tree(node* tree);

//vbc.c
node	*parse_expression(char **s); //moved from main.c, changed from *s to **s
node	*parse_term(char **s);
node	*parse_factor(char **s);
node	*parse_number(char **s);