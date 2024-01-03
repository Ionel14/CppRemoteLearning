#ifndef SMARTHOME_DEVICE_H_
#define SMARTHOME_DEVICE_H_

#include "sensor.h"
#include "sensor_humidity.h"
#include "sensor_light.h"
#include "sensor_temperature.h"

#include <iostream>
#include <vector>

namespace smarthome {

class Device {
  std::string name;
  bool state;
  std::vector<Sensor> sensors;

  const std::string type = "Undefined";

public:
  Device(const std::string& name, bool state);
  Device(const std::string& name, bool state, const std::vector<Sensor>& sensors);

  std::string getName();
  bool getState();
  std::vector<Sensor> getSensors();
  virtual std::string getType();

  void setState(bool state);

  void addSensor(const Sensor& sensor);
};

} // namespace smarthome
#endif  // SMARTHOME_DEVICE_H_