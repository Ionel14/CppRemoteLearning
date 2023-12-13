#ifndef SMARTHOME_SENSOR_H_
#define SMARTHOME_SENSOR_H_

#include <iostream>

class Sensor {
  std::string name;
  int value;

public:
  Sensor(const std::string& name, int value);

  std::string getName();
  int getValue();

  void setValue(int value);
};

#endif  // SMARTHOME_SENSOR_H_