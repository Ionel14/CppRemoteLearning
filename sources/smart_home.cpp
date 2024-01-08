#include "../headers/smart_home.h"

#include <fstream>
#include <regex>
#include <string>

namespace smarthome {
  
SmartHome::SmartHome(const std::vector<Room>& rooms) : rooms(rooms) {}

std::vector<Room> SmartHome::getRooms() const {
  return rooms;
}

void SmartHome::addRoom(const Room& room) {
  rooms.push_back(room);
}

} // namespace smarthome