#include "../headers/smart_home.h"

#include <fstream>
#include <regex>
#include <string>

namespace smarthome {
  
SmartHome::SmartHome(std::vector<UniquePointer<Room>>& rooms) {
  for (auto& room : rooms) {
    this->rooms.push_back(std::move(room));
  }
}

std::vector<UniquePointer<Room>>& SmartHome::getRooms() {
  return rooms;
}

void SmartHome::addRoom(UniquePointer<Room> room) {
  rooms.push_back(std::move(room));
}

} // namespace smarthome