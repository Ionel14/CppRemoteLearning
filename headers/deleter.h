#ifndef SHA_DELETER_H_
#define SHA_DELETER_H_

#include <iostream>

namespace smarthome
{
    template<typename T>
    class Deleter {
        public:
            bool operator()(T* ptr) {
                if (ptr == nullptr) {
                    return false;
                }
                delete ptr;
                return true;
            }
    };
} // namespace smarthome


#endif // SHA_DELETER_H_