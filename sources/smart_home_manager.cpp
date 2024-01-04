#include "../headers/smart_home_manager.h"

#include <fstream>
#include <regex>
#include <string>

namespace smarthome {

SmartHome SmartHomeManager::readDataFromFile(const std::string& filename) {
  SmartHome smarthome;

  std::ifstream myFile;
  myFile.open(resourses_directory + filename);

  std::string word1, word2, word3;
  while (!myFile.eof()) {
    myFile >> word1 >> word2;
    while (word1 == "Room:") {
      Room room(word2);

      myFile >> word1 >> word2;
      while (word2 == "Device:") {
        myFile >> word2 >> word3;
        
        bool state;
        if(word3 == "on") {
          state = 1;
        } else {
          state = 0;
        }

        Device *device;
        if(word1 == "AC"){
          device = new DeviceAcUnit(word2, state);
        } else if (word1 == "Fan") {
          device = new DeviceFan(word2, state);
        } else {
          device = new DeviceLightbulb(word2, state);
        }

        myFile >> word1 >> word2;
        while (word2 == "Sensor:") {
          myFile >> word2 >> word3;

          Sensor *sensor;
          if(word1 == "Humidity"){
            sensor = new SensorHumidity(word2, stoi(word3));
          } else if (word1 == "Light") {
            sensor = new SensorLight(word2, stoi(word3));
          } else {
            sensor = new SensorTemperature(word2, stoi(word3));
          }

          device->addSensor(sensor);

          myFile >> word1 >> word2;
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
      if (device->getState()) {
        state = "on";
      } else {
        state = "off";
      }
      myFile << "\t" << device->getType() << " Device: " << device->getName() << " " << state << std::endl;

      for (auto sensor : device->getSensors()) {
        myFile << "\t\t" << sensor->getType() << " Sensor: " << sensor->getName() << " " << sensor->getValue() << std::endl;
      }
    }
  }
  myFile.close();
}

} // namespace smarthome