#include "../headers/device.h"

namespace smarthome {
  
Device::Device(const std::string& name, bool state) : name(name), state(state) {}

Device::Device(const std::string& name, bool state, std::vector<UniquePointer<Sensor>>& sensors) : 
  name(name), state(state) {
    for (auto& sensor : sensors) {
      this->sensors.push_back(std::move(sensor));
    }
}

std::string Device::getName() const {
  return name;
}

bool Device::getState() const {
 return state;
}

std::vector<UniquePointer<Sensor>>& Device::getSensors() {
  return sensors;
}

std::string Device::getType() const {
  return type;
}

void Device::setState(bool state) {
  this->state = state;
}

void Device::addSensor(UniquePointer<Sensor> sensor){
  sensors.push_back(std::move(sensor));
}

} // namespace smarthome