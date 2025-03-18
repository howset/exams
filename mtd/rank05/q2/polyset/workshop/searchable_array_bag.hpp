#ifndef SEARCHABLE_ARRAY_BAG_HPP
# define SEARCHABLE_ARRAY_BAG_HPP

# include "array_bag.hpp"
# include "searchable_bag.hpp"

class searchable_array_bag : public array_bag, public searchable_bag {
public:
	bool has(int num) const {
		for (int i = 0; i < this->size; i++) {
			if (data[i] == num)
				return true;
		}
		return false;
	}
};

#endif