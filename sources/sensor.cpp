#include "../headers/sensor.h"

namespace smarthome {
  
Sensor::Sensor(const std::string& name, int value) {
  this->name = name;
  this->value = value;
}

std::string Sensor::getName() {
  return name;
}

int Sensor::getValue() {
  return value;
}

void Sensor::setValue(int value) {
  this->value = value;
}

} // namespace smarthome