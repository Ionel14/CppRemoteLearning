#ifndef SMARTHOME_ROOMS_H_
#define SMARTHOME_ROOMS_H_

#include "devices_and_sensors.h"

class Rooms {
  // I'm using maps because i need to store key-value pairs 
  // where the keys represent the rooms, thus they need to be unique.
  // I'm also using unordered maps because the order of tha data doesnt matter,
  // all of the rooms need to be controlloed at all times by the smart home.
  std::unordered_map<std::string, DevicesAndSensors> rooms;

public:
  void modifyRoomNumericData(std::string room, std::string sensor, int value);  
  void modifyRoomOnOffData(std::string room, std::string device, bool state);
  void readDataFromFile(std::string filename);
  void writeDataToFile(std::string filename);
};

#endif  // SMARTHOME_ROOMS_H_