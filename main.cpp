#include "headers/smart_home.h"
#include "headers/smart_home_manager.h"

#include <fstream>
#include <vector>

using namespace smarthome;

int main () {
  std::vector<Sensor> sensors1 = { SensorTemperature("temperature1", 25), SensorHumidity("humidity1", 30) };
  std::vector<Sensor> sensors2 = { SensorLight("light1", 0) };
  std::vector<Device> devices1 = { DeviceAcUnit("ac_unit1", 0, sensors1), DeviceLightbulb("lightbulb1", 1, sensors2) };

  std::vector<Sensor> sensors3 = { SensorTemperature("temperature2", 20), SensorHumidity("humidity2", 40) };
  std::vector<Device> devices2 = { DeviceFan("fan1", 0, sensors3) };

  std::vector<Sensor> sensors4 = { SensorLight("light2", 1) };
  std::vector<Device> devices3 = { DeviceLightbulb("lightbulb2", 0, sensors4) };

  std::vector<Room> rooms = { Room("bedroom", devices1), Room("living_room", devices2), Room("kitchen", devices3) };

  SmartHome smartHome(rooms);
  SmartHomeManager::writeDataToFile("data1.txt", smartHome);

  SmartHome smartHome2;
  smartHome2 = SmartHomeManager::readDataFromFile("data1.txt");
  SmartHomeManager::writeDataToFile("data2.txt", smartHome2);

  return 0;
}
