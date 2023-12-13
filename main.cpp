#include "headers/smart_home.h"

#include <fstream>
#include <vector>

using namespace smarthome;

int main () {
  std::vector<Sensor> sensors1 = { Sensor("temperature", 25), Sensor("humidity", 30) };
  std::vector<Sensor> sensors2 = { Sensor("light", 0) };
  std::vector<Device> devices1 = { Device("ac_unit", 0, sensors1), Device("lightbulb", 1, sensors2) };

  std::vector<Sensor> sensors3 = { Sensor("temperature", 20), Sensor("humidity", 40) };
  std::vector<Device> devices2 = { Device("fan", 0, sensors3) };

  std::vector<Sensor> sensors4 = { Sensor("light", 1) };
  std::vector<Device> devices3 = { Device("lightbulb", 0, sensors4) };

  std::vector<Room> rooms = { Room("bedroom", devices1), Room("living_room", devices2), Room("kitchen", devices3) };

  SmartHome smartHome(rooms);
  smartHome.writeDataToFile("data1.txt");

  SmartHome smartHome2;
  smartHome2.readDataFromFile("data1.txt");
  smartHome2.writeDataToFile("data2.txt");

  return 0;
}
