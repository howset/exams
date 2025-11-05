#include "bag.hpp"
#include "searchable_bag.hpp"

class set
{
    private:
        searchable_bag &bag;
    public:
        set(searchable_bag &bg) : bag(bg) {}
        ~set(){}

        bool has(int item) const {
            return (bag.has(item));
        }
        void insert(int item) {
            if (!bag.has(item))
                bag.insert(item);
        }
        void insert(int *items, int count) {
            for (int i = 0 ; i < count ; i++)
                bag.insert(items[i]);
        }

        void clear() {
            bag.clear();
        }

        void print() const {
            bag.print();
        }

        searchable_bag &get_bag() const {
            return (bag);
        }
};
