#include "searchable_tree_bag.hpp"

bool searchable_tree_bag::has(int value) const
{
	node *current = tree;

	while(current != 0)
	{
		if (value == current->value)
			return true;
		else if (value < current->value)
			current = current->l;
		else
			current = current->r;
	}
	return false;
}