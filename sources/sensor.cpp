#include "../headers/sensor.h"

namespace smarthome {
  
Sensor::Sensor(const std::string& name, int value) : name(name), value(value) {}
Sensor::Sensor(const Sensor& other) : type(other.type), name(other.name), value(other.value) {}
Sensor::Sensor(const Sensor&& other) : type(other.type), name(other.name), value(other.value) {}

Sensor& Sensor::operator=(const Sensor& other) {
  if (this != &other) {
    type = other.type;
    name = other.name;
    value = other.value;
  }
  return *this;
}

Sensor& Sensor::operator=(const Sensor&& other) {
  if (this != &other) {
    type = other.type;
    name = other.name;
    value = other.value;
  }
  return *this;
}

Sensor::~Sensor() {};

std::string Sensor::getName() {
  return name;
}

int Sensor::getValue() {
  return value;
}

std::string Sensor::getType() {
  return type;
}

void Sensor::setValue(int value) {
  this->value = value;
}

} // namespace smarthome