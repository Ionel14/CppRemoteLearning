#ifndef SMARTHOME_SENSOR_TEMPERATURE_H_
#define SMARTHOME_SENSOR_TEMPERATURE_H_

#include "sensor.h"

#include <iostream>

namespace smarthome {

class SensorTemperature : public Sensor {
  const std::string type = "Temperature";

public:
  SensorTemperature(const std::string& name, int value);

  std::string getType();
};

} // namespace smarthome
#endif  // SMARTHOME_SENSOR_TEMPERATURE_H_