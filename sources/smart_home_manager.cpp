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
      UniquePointer<Room> room (new Room (word2));

      myFile >> word1 >> word2;
      while (word2 == "Device:") {
        myFile >> word2 >> word3;
        
        bool state;
        if(word3 == "on") {
          state = 1;
        } else {
          state = 0;
        }

        UniquePointer<Device> device;
        if(word1 == "AC"){
          device = UniquePointer<Device> (new DeviceAcUnit(word2, state));
        } else if (word1 == "Fan") {
          device = UniquePointer<Device> (new DeviceFan(word2, state));
        } else {
          device = UniquePointer<Device> (new DeviceLightbulb(word2, state));
        }

        myFile >> word1 >> word2;
        while (word2 == "Sensor:") {
          myFile >> word2 >> word3;

          UniquePointer<Sensor> sensor;
          if(word1 == "Humidity"){
            sensor = UniquePointer<Sensor> (new SensorHumidity(word2, stoi(word3)));
          } else if (word1 == "Light") {
            sensor = UniquePointer<Sensor> (new SensorLight(word2, stoi(word3)));
          } else {
            sensor = UniquePointer<Sensor> (new SensorTemperature(word2, stoi(word3)));
          }

          device->addSensor(std::move(sensor));

          myFile >> word1 >> word2;
        }
        room->addDevice(std::move(device));
      }
      smarthome.addRoom(std::move(room));
    }
  }
  myFile.close();
  return smarthome;
}

void SmartHomeManager::writeDataToFile(const std::string& filename, SmartHome& smarthome) {
  std::ofstream myFile;
  myFile.open(resourses_directory + filename);

  for (auto& room : smarthome.getRooms()) {
    myFile << "Room: " << room->getName() << std::endl;

    for (auto& device : room->getDevices()) {
      std::string state;
      if (device->getState()) {
        state = "on";
      } else {
        state = "off";
      }
      myFile << "\t" << device->getType() << " Device: " << device->getName() << " " << state << std::endl;

      for (auto& sensor : device->getSensors()) {
        myFile << "\t\t" << sensor->getType() << " Sensor: " << sensor->getName() << " " << sensor->getValue() << std::endl;
      }
    }
  }
  myFile.close();
}

} // namespace smarthome