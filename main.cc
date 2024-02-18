#include <iostream>
#include "marc_pop_unique_ptr/custom_unique_ptr.h"

int main() {
    custom_memory::CustomUniquePtr<int> int_pointer(new int(5));
    std::cout << *int_pointer.Get() << " " << *int_pointer << std::endl;

    *int_pointer = 10;

    std::cout << *int_pointer.Get() << " " << *int_pointer << std::endl;

    custom_memory::CustomUniquePtr<int> int_array_pointer(new int[5]);

    int_array_pointer[1] = 5;

    std::cout << int_array_pointer[1] << std::endl;
    return 0;
}
