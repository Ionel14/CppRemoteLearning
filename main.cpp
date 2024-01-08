#include "headers/smart_home.h"
#include "headers/smart_home_manager.h"

#include <fstream>
#include <vector>

using namespace smarthome;

void deallocateSensorsMemory(std::vector<Sensor*>& sensors) {
  for(auto sensor : sensors) {
      delete sensor;
    }
}

void deallocateDevicesMemory(std::vector<Device*>& devices) {
  for(auto device : devices) {
      delete device;
    }
}

int main () {
  std::vector<Sensor*> sensors1 = { new SensorTemperature("temperature1", 25), new SensorHumidity("humidity1", 30) };
  std::vector<Sensor*> sensors2 = { new SensorLight("light1", 0) };
  std::vector<Device*> devices1 = { new DeviceAcUnit("ac_unit1", 0, sensors1), new DeviceLightbulb("lightbulb1", 1, sensors2) };

  std::vector<Sensor*> sensors3 = { new SensorTemperature("temperature2", 20), new SensorHumidity("humidity2", 40) };
  std::vector<Device*> devices2 = { new DeviceFan("fan1", 0, sensors3) };

  std::vector<Sensor*> sensors4 = { new SensorLight("light2", 1) };
  std::vector<Device*> devices3 = { new DeviceLightbulb("lightbulb2", 0, sensors4) };

  std::vector<Room> rooms = { Room("bedroom", devices1), Room("living_room", devices2), Room("kitchen", devices3) };

  SmartHome smartHome(rooms);
  SmartHomeManager::writeDataToFile("data1.txt", smartHome);

  SmartHome smartHome2;
  smartHome2 = SmartHomeManager::readDataFromFile("data1.txt");
  SmartHomeManager::writeDataToFile("data2.txt", smartHome2);


  for(auto sensor : sensors1) {
    sensor->printPurpose();
  }
  for(auto sensor : sensors2) {
    sensor->printPurpose();
  }

  for(auto device : devices1) {
    device->printPurpose();
  }
  for(auto device : devices2) {
    device->printPurpose();
  }


  deallocateSensorsMemory(sensors1);
  deallocateSensorsMemory(sensors2);
  deallocateSensorsMemory(sensors3);
  deallocateSensorsMemory(sensors4);

  deallocateDevicesMemory(devices1);
  deallocateDevicesMemory(devices2);
  deallocateDevicesMemory(devices3);

  return 0;
}
