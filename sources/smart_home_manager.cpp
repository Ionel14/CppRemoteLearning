#include "../headers/smart_home_manager.h"

#include <fstream>
#include <regex>
#include <string>

namespace smarthome {

SmartHome SmartHomeManager::readDataFromFile(const std::string& filename) {
  SmartHome smarthome;

  std::ifstream myFile;
  myFile.open(resourses_directory + filename);

  std::string word1, word2;
  while (!myFile.eof()) {
    myFile >> word1;
    while (word1 == "Room:") {
      myFile >> word1;
      Room room(word1);

      myFile >> word1;
      while (word1 == "Device:") {
        myFile >> word1 >> word2;
        
        bool state;
        if(word2 == "on") {
          state = 1;
        } else {
          state = 0;
        }
        Device device(word1, state);

        myFile >> word1;
        while (word1 == "Sensor:") {
          myFile >> word1 >> word2;
          Sensor sensor(word1, stoi(word2));

          device.addSensor(sensor);

          myFile >> word1;
        }
        room.addDevice(device);
      }
      smarthome.addRoom(room);
    }
  }
  myFile.close();
  return smarthome;
}

void SmartHomeManager::writeDataToFile(const std::string& filename, SmartHome smarthome) {
  std::ofstream myFile;
  myFile.open(resourses_directory + filename);

  for (auto room : smarthome.getRooms()) {
    myFile << "Room: " << room.getName() << std::endl;

    for (auto device : room.getDevices()) {
      std::string state;
      if (device.getState()) {
        state = "on";
      } else {
        state = "off";
      }
      myFile << "\tDevice: " << device.getName() << " " << state << std::endl;

      for (auto sensor : device.getSensors()) {
        myFile << "\t\tSensor: " << sensor.getName() << " " << sensor.getValue() << std::endl;
      }
    }
  }
  myFile.close();
}

} // namespace smarthome