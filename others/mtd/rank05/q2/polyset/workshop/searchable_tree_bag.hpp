#pragma once

# include "tree_bag.hpp"
# include "searchable_bag.hpp"

class searchable_tree_bag : public tree_bag, public searchable_bag {
public:

    bool has_in_tree(node *t, int num) const {
        if (t->value == num)
            return true;
        if (t->l && has_in_tree(t->l, num))
            return true;
        if (t->r && has_in_tree(t->r, num))
            return true;
        return false;
    }

	bool has(int num) const {
		if (has_in_tree(tree, num))
            return true;
        return false;
	}
};