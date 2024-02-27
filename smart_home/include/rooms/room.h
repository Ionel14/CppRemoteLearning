#ifndef SMART_HOME_ROOMS_ROOM_H_
#define SMART_HOME_ROOMS_ROOM_H_

#include <string>

namespace rooms {

// Rule of Five implemented

class Room {
  public:
    Room(std::string name, const float size);

    Room(const Room& other) : name(other.name), size(other.size) {}

    Room& operator=(const Room& other);

    Room(const Room&& other) : name(std::move(other.name)), size(other.size) {}

    Room& operator=(Room&& other);

    ~Room() = default;

    inline float GetSize() {
      return size;
    };

    inline std::string GetName() {
      return name;
    };

  private:
    std::string name;
    float size = 0;
};

} // namespace rooms

#endif // SMART_HOME_ROOMS_ROOM_H_