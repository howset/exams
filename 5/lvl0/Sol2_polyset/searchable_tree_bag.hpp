#include "searchable_bag.hpp"
#include "tree_bag.hpp"

class searchable_tree_bag : public tree_bag , public searchable_bag
{
    public:
        searchable_tree_bag () : tree_bag() {}
        searchable_tree_bag (const searchable_tree_bag &oth) : tree_bag(oth) {};
        searchable_tree_bag &operator=(const searchable_tree_bag &oth)
        {
            if (this != &oth)
            {
                tree_bag::operator=(oth);
            }
            return (*this);
        }

        bool has(int item) const
        {
            node *current = tree;
            while (current)
            {
                if (item == current->value)
                    return (true);
                else if (item > current->value)
                    current = current->r;
                else
                    current = current->l;
            }
            return (false);
        }
};