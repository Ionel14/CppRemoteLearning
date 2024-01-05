#ifndef SMARTHOME_SENSOR_HUMIDITY_H_
#define SMARTHOME_SENSOR_HUMIDITY_H_

#include "sensor.h"

#include <iostream>

namespace smarthome {

class SensorHumidity : public Sensor {
public:
  SensorHumidity(const std::string& name, int value);

  void printPurpose();
};

} // namespace smarthome
#endif  // SMARTHOME_SENSOR_HUMIDITY_H_