#include "../headers/room.h"

namespace smarthome {

Room::Room(const std::string& name) : name(name) {}

Room::Room(const std::string& name, const std::vector<Device>& devices) 
  : name(name), devices(devices) {}

std::string Room::getName() {
  return name;
}

std::vector<Device> Room::getDevices() {
  return devices;
}

void Room::addDevice(const Device& device){
  devices.push_back(device);
}

} // namespace smarthome