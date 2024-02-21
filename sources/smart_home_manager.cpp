#include "../headers/smart_home_manager.h"

#include <fstream>
#include <regex>
#include <string>

namespace smarthome {

SmartHome SmartHomeManager::readDataFromFile(const std::string& filename) {
  SmartHome smarthome;

  std::ifstream myFile;
  myFile.open(resourses_directory + filename);

  if (!myFile) {
    throw std::invalid_argument("Couldn't open file \"" + filename + "\"\n");
  }

  std::string word1, word2, word3;
  while (!myFile.eof()) {
    myFile >> word1 >> word2;

    if (word1 == "" || word2 == "" || word1 != "Room:") {
      throw std::runtime_error("Data in the file \"" + filename + "\" is not in the correct format\n");
    }

    while (word1 == "Room:") {
      UniquePointer<Room> room (new Room (word2));

      myFile >> word1 >> word2;

      if (word1 == "" || word2 == "" || word2 != "Device:") {
        throw std::runtime_error("Data in the file \"" + filename + "\" is not in the correct format\n");
      }

      while (word2 == "Device:") {
        myFile >> word2 >> word3;

        if (word2 == "" || word3 == "") {
          throw std::runtime_error("Data in the file \"" + filename + "\" is not in the correct format\n");
        }
        
        bool state;
        if(word3 == "on") {
          state = 1;
        } else if (word3 == "off") {
          state = 0;
        } else {
          throw std::runtime_error("Data in the file \"" + filename + "\" is not in the correct format\n");
        }

        UniquePointer<Device> device;
        if(word1 == "AC"){
          device = UniquePointer<Device> (new DeviceAcUnit(word2, state));
        } else if (word1 == "Fan") {
          device = UniquePointer<Device> (new DeviceFan(word2, state));
        } else if (word1 == "Lightbulb") {
          device = UniquePointer<Device> (new DeviceLightbulb(word2, state));
        } else {
          throw std::runtime_error("Data in the file \"" + filename + "\" is not in the correct format\n");
        }

        myFile >> word1 >> word2;

        if (word1 == "" || word2 == "" || word2 != "Sensor:") {
          throw std::runtime_error("Data in the file \"" + filename + "\" is not in the correct format\n");
        }

        while (word2 == "Sensor:") {
          myFile >> word2 >> word3;

          if (word2 == "" || word3 == "") {
            throw std::runtime_error("Data in the file \"" + filename + "\" is not in the correct format\n");
          }

          try {
            std::string::size_type sz;
            int sensorValue = stoi(word3, &sz);

            if (word3.substr(sz) != "") {
              throw std::exception();
            }

            UniquePointer<Sensor> sensor;
            if(word1 == "Humidity"){
              sensor = UniquePointer<Sensor> (new SensorHumidity(word2, sensorValue));
            } else if (word1 == "Light") {
              sensor = UniquePointer<Sensor> (new SensorLight(word2, sensorValue));
            } else if (word1 == "Temperature") {
              sensor = UniquePointer<Sensor> (new SensorTemperature(word2, sensorValue));
            } else {
              throw std::exception();
            }

            device->addSensor(std::move(sensor));
          } catch (std::exception& e) {
            throw std::runtime_error("Data in the file \"" + filename + "\" is not in the correct format\n");
          }
  
          myFile >> word1 >> word2;

          if (word1 == "" || word2 == "") {
            throw std::runtime_error("Data in the file \"" + filename + "\" is not in the correct format\n");
          }
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
  
  if (!myFile) {
    throw std::invalid_argument("Couldn't create file \"" + filename + "\"\n");
  }

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