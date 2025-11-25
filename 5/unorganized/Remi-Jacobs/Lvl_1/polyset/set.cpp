#include "set.hpp"
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"

set::set(searchable_bag &bag)
{
	searchable_array_bag *array_ptr = dynamic_cast<searchable_array_bag*>(&bag);
	if(array_ptr)
		bag_ptr = new searchable_array_bag(*array_ptr);
	else
	{
		searchable_tree_bag *tree_ptr = dynamic_cast<searchable_tree_bag*>(&bag);
		if(tree_ptr)
			bag_ptr = new searchable_tree_bag(*tree_ptr);
	}
}
set::set(const set &other)
{
	searchable_array_bag *array_ptr = dynamic_cast<searchable_array_bag*>(other.bag_ptr);
	if(array_ptr)
		bag_ptr = new searchable_array_bag(*array_ptr);
	else
	{
		searchable_tree_bag *tree_ptr = dynamic_cast<searchable_tree_bag*>(other.bag_ptr);
		if(tree_ptr)
			bag_ptr = new searchable_tree_bag(*tree_ptr);
	}
}
set& set:: operator=(const set &other)
{
	if(this != &other)
	{
		delete bag_ptr;
		searchable_array_bag *array_ptr = dynamic_cast<searchable_array_bag*>(other.bag_ptr);
		if(array_ptr)
			bag_ptr = new searchable_array_bag(*array_ptr);
		else
		{
			searchable_tree_bag *tree_ptr = dynamic_cast<searchable_tree_bag*>(other.bag_ptr);
			if(tree_ptr)
				bag_ptr = new searchable_tree_bag(*tree_ptr);
		}
	}
	return *this;
}

set::~set()
{
	delete bag_ptr;
}

void set:: insert(int value)
{
	if (!bag_ptr->has(value))
		bag_ptr->insert(value);
}

void set::insert(int *array, int size)
{
	for(int i = 0; i <size; i++)
		insert(array[i]);
}

void set:: print() const
{
	bag_ptr->print();
}

void set:: clear()
{
	bag_ptr->clear();
}
bool set::has(int value) const
{
	return bag_ptr->has(value);
}

searchable_bag& set:: get_bag()const
{
	return *bag_ptr;
}