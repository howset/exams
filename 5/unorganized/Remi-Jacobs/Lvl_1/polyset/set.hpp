#ifndef SET_HPP
#define SET_HPP

#include "searchable_bag.hpp"

class set
{
private:
	searchable_bag *bag_ptr;
public:
	set(searchable_bag &bag);
	set(const set &other);
	set& operator=(const set &other);
	~set();

    void insert(int value);
    void insert(int *array, int size);
    void print() const;
    void clear();
	bool has(int value) const;
	searchable_bag &get_bag()const;
};

#endif