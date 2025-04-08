#pragma once

#include <vector>
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"

/*
Base*	arr[3] = { NULL };
arr[0] = dynamic_cast<A*>(p);
arr[1] = dynamic_cast<B*>(p);
arr[2] = dynamic_cast<C*>(p);
*/

#define ARRAY 0
#define TREE 1
#define INVALID -1

class set : public searchable_array_bag, public searchable_tree_bag {
private:
    set() : searchable_array_bag(), searchable_tree_bag() {}
    int type;

public:
    searchable_bag& get_bag() {
        if (type == ARRAY)
            return static_cast<searchable_array_bag&>(*this);
        else  // if (type == TREE)
            return static_cast<searchable_tree_bag&>(*this);
    }
    const searchable_bag& get_bag() const {
        if (type == ARRAY)
            return static_cast<const searchable_array_bag&>(*this);
        else  // if (type == TREE)
            return static_cast<const searchable_tree_bag&>(*this);
    }
    ~set() {}
    set(const set& other) :
        searchable_array_bag(other),
        searchable_tree_bag(other) {}
    set(const searchable_bag& other) {
        type = INVALID;
        if (const searchable_array_bag *sab = dynamic_cast<const searchable_array_bag*>(&other)) {
            new (static_cast<searchable_array_bag*>(this)) searchable_array_bag(*sab);
            searchable_array_bag tmp = searchable_array_bag(*sab);
            for (int i = 0; i < size; i++) {
                if (!tmp.has(data[i]))
                    tmp.insert(data[i]);
            }
            searchable_array_bag::clear();
            new (static_cast<searchable_array_bag*>(this)) searchable_array_bag(tmp);
            type = ARRAY;
        }
        else if (const searchable_tree_bag *stb = dynamic_cast<const searchable_tree_bag*>(&other)) {
            new (static_cast<searchable_tree_bag*>(this)) searchable_tree_bag(*stb);
            type = TREE;
        }
    }
    set& operator=(const set& other) {
        type = INVALID;
        if (this != &other) {
            if (const searchable_bag *scenarioA = dynamic_cast<const searchable_array_bag*>(&other)) {
                searchable_array_bag::operator=(other);
                type = ARRAY;
                for (int i = 0; i < size; i++)
                    get_bag().insert(data[i]);
            }
            else if (const searchable_bag *scenarioB = dynamic_cast<const searchable_tree_bag*>(&other)) {
                searchable_tree_bag::operator=(other);
                type = TREE;
            }
        }
        return *this;
    }

    void insert(int num) {
        if (get_bag().has(num) == false)
            get_bag().insert(num);
    }

    void insert(int *range, int count) {
        if (type == ARRAY) {
            for (int i = 0; i < count; i++)
                insert(range[i]);
        }
        else  // TREE
            get_bag().insert(range, count);
    }

    void print() const {
        get_bag().print();
    }

    bool has(int num) {
        return get_bag().has(num);
    }

    void clear() {
        get_bag().clear();
    }

    // bool has(int num) {
    //     if (type == ARRAY) {
    //         std::cout << "finding in arr, size is: " << set_data.size() << std::endl;
    //         if (std::find(set_data.begin(), set_data.end(), num) != set_data.end())
    //             return true;
    //         return false;
    //     }
    //     else if (type == TREE) {
    //         // return searchable_tree_bag::has(num);
    //         return get_bag().has(num);  // segfault
    //     }
    //     else
    //         return false;
    // }
    // void insert(int num) {
    //     if (!has(num)) 
    //         {set_data.push_back(num);}
    // }
    // void insert(int* items, int count) {
    //     for (int i = 0; i < count; i++)
    //         insert(items[i]);
    // }
    // void print() const {
    //     if (type == TREE)
    //         get_bag().print();
    // }
    // void clear() {
    //     if (type == ARRAY)
    //         set_data.clear();
    //     if (type == TREE)
    //         searchable_tree_bag::clear();
    //
    // }
};