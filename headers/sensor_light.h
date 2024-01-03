#ifndef SMARTHOME_SENSOR_LIGHT_H_
#define SMARTHOME_SENSOR_LIGHT_H_

#include "sensor.h"

#include <iostream>

namespace smarthome {

class SensorLight : public Sensor {
  const std::string type = "Light";

public:
  SensorLight(const std::string& name, int value);

  std::string getType();
};

} // namespace smarthome
#endif  // SMARTHOME_SENSOR_LIGHT_H_