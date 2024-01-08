#ifndef SMARTHOME_SENSOR_TEMPERATURE_H_
#define SMARTHOME_SENSOR_TEMPERATURE_H_

#include "sensor.h"

#include <iostream>

namespace smarthome {

class SensorTemperature : public Sensor {
public:
  SensorTemperature(const std::string& name, int value);

  void printPurpose() const;
};

} // namespace smarthome
#endif  // SMARTHOME_SENSOR_TEMPERATURE_H_