#include <iostream>
#include "custom_unique_ptr.h"
#include "foo.h"

int main() {
    custom_memory::CustomUniquePtr<int> int_pointer(new int(5));

    std::cout << *int_pointer.Get() << " " << *int_pointer << std::endl;

    *int_pointer = 10;

    std::cout << *int_pointer.Get() << " " << *int_pointer << std::endl;

    custom_memory::CustomUniquePtr<int> int_array_pointer(new int[5]);
    
    int_array_pointer[1] = 5;

    std::cout << int_array_pointer[1] << std::endl;

    custom_memory::CustomUniquePtr<foo::Foo> foo_pointer(new foo::Foo());

    foo_pointer->Bar();
    (*foo_pointer).Bar();

    return 0;
}