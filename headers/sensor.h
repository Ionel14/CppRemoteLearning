#ifndef SMARTHOME_SENSOR_H_
#define SMARTHOME_SENSOR_H_

#include <iostream>

namespace smarthome {

class Sensor {
  std::string name;
  int value;

public:
  Sensor(const std::string& name, int value);

  std::string getName();
  int getValue();

  void setValue(int value);
};

} // namespace smarthome
#endif  // SMARTHOME_SENSOR_H_