#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"
#include "set.hpp"
#include <iostream>

int main() {
    std::cout << "Testing searchable bags and set..." << std::endl;
    
    // Test searchable_array_bag
    searchable_array_bag array_bag;
    array_bag.insert(5);
    array_bag.insert(3);
    array_bag.insert(7);
    array_bag.insert(3); // duplicate
    
    std::cout << "Array bag contents: ";
    array_bag.print();
    std::cout << "Has 3: " << array_bag.has(3) << std::endl;
    std::cout << "Has 9: " << array_bag.has(9) << std::endl;
    
    // Test set with array bag
    set my_set(array_bag);
    my_set.insert(5); // duplicate (should be ignored)
    my_set.insert(9); // new value
    
    std::cout << "Set contents: ";
    my_set.print();
    std::cout << "Set has 3: " << my_set.has(3) << std::endl;
    std::cout << "Set has 9: " << my_set.has(9) << std::endl;
    
    return 0;
}
