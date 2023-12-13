#ifndef SMARTHOME_SMARTHOME_H_
#define SMARTHOME_SMARTHOME_H_

#include "room.h"

#include <iostream>
#include <vector>

class SmartHome {
  // I'm using a vector, because it iterates through elements fast and it's easy to access an element. 
  // These are often used features because we need to be able to quickly choose a room or check every room.
  // It's slower at inserting/ removing elements, but a home's rooms/ devices/ sensors will not change that frequently.
  std::vector<Room> rooms;

  const char *resourses_directory="resources/";

public:
  SmartHome() = default;
  SmartHome(const std::vector<Room>& rooms);

  std::vector<Room> getRooms();

  void addRoom(const Room& room);

  void readDataFromFile(const std::string& filename);
  void writeDataToFile(const std::string& filename);
};

#endif  // SMARTHOME_SMARTHOME_H_