#ifndef SMART_HOME_ROOMS_ROOM_H_
#define SMART_HOME_ROOMS_ROOM_H_

namespace rooms {

// Rule of Zero

class Room {
  public:
    Room(const float size): size(size) {}

    inline float GetSize() {
      return size;
    };

  private:
    const float size = 0;
};

} // namespace rooms

#endif // SMART_HOME_ROOMS_ROOM_H_