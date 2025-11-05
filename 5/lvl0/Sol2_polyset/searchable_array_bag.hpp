#include "searchable_bag.hpp"
#include "array_bag.hpp"

class searchable_array_bag : public array_bag , public searchable_bag
{
    public:
        searchable_array_bag () : array_bag() {}
        searchable_array_bag (const searchable_array_bag &oth) : array_bag(oth) {};
        searchable_array_bag &operator=(const searchable_array_bag &oth)
        {
            if (this != &oth)
            {
                array_bag::operator=(oth);
            }
            return (*this);
        }

        bool has(int item) const {
            for (int i = 0 ; i < size ; i++)
            {
                if (data[i] == item)
                    return (true);
            }
            return (false);
        }
};