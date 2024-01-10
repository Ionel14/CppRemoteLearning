#ifndef CUSTOM_UNIQUE_PTR_FOO_H_
#define CUSTOM_UNIQUE_PTR_FOO_H_

#include <iostream>

namespace foo {
    class Foo {
        public:
            inline void Bar() {
                std::cout << "Called Bar Method" << std::endl;
            }
    };
} // namespace foo

#endif // CUSTOM_UNIQUE_PTR_FOO_H_