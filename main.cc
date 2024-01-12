#include <iostream>
#include "pointers/unique_ptr.h"

int main() {
    std::cout << "Demo Unique Pointer\n";
    my_unique_ptr::unique_ptr<int> singlePtr(new int(42));
    std::cout << "singlePtr points to: " << *singlePtr << std::endl;

    singlePtr.reset(new int(55));
    std::cout << "singlePtr now points to: " << *singlePtr << std::endl;
    return 0;
}
