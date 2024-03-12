#include "../headers/room.h"

namespace smarthome {

Room::Room(const std::string& name) : name(name) {}

Room::Room(const std::string& name, std::vector<UniquePointer<Device>>& devices) 
  : name(name) {
  for (auto& device : devices) {
    this->devices.push_back(std::move(device));
  }
}

std::string Room::getName() const {
  return name;
}

std::vector<UniquePointer<Device>>& Room::getDevices() {
  return devices;
}

void Room::addDevice(UniquePointer<Device> device){
  devices.push_back(std::move(device));
}

void Room::removeDevice(int index) {
  for (int i = 0; i < devices[index]->getSensors().size(); i++) {
    devices[index]->removeSensor(i);
  }
  devices.erase(devices.begin() + index);
}


} // namespace smarthome