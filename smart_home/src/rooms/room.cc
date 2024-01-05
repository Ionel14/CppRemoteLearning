#include "rooms/room.h"

namespace rooms {

Room& Room::operator=(const Room& other) {
    if (this != &other) {
        name = other.name;
        size = other.size;
    }
    return *this;
}

Room& Room::operator=(Room&& other) {
    if (this != &other) {
        name = std::move(other.name);
        size = other.size;
    }
    return *this;
}

} // namespace rooms