#pragma once

#include <cstddef>
#include <iostream>
#include "searchable_bag.hpp"
#include "tree_bag.hpp"

class searchable_tree_bag : public searchable_bag, public tree_bag
{
public:

    bool has_num(node *tree, int num) const {
        if (!tree)
            return false;
        if (tree->value == num)
            return true;
        
        if (tree->l && has_num(tree->l, num))
            return true;
        if (tree->r && has_num(tree->r, num))
            return true;
        return false;
    }

    virtual bool has(int num) const {
        if (has_num(tree, num))
            return true;
        return false;
    }

    searchable_tree_bag() : searchable_bag(), tree_bag() {}
    ~searchable_tree_bag() {}
    searchable_tree_bag(const searchable_tree_bag& other) :
        tree_bag(other) {}
    searchable_tree_bag operator=(const searchable_tree_bag& other) {
        if (this != &other) {
            searchable_bag::operator=(other);
            tree_bag::operator=(other);
        }
        return *this;
    }
};