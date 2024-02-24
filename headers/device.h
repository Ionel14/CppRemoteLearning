#ifndef SMARTHOME_DEVICE_H_
#define SMARTHOME_DEVICE_H_

#include "sensor.h"
#include "sensor_humidity.h"
#include "sensor_light.h"
#include "sensor_temperature.h"

#include "unique_ptr_colleague.h"

#include <iostream>
#include <vector>

namespace smarthome {

class Device {
public:
  Device(const std::string& name, bool state);
  Device(const std::string& name, bool state, std::vector<UniquePointer<Sensor>>& sensors);

  std::string getName() const;
  bool getState() const;
  std::vector<UniquePointer<Sensor>>& getSensors();
  std::string getType() const;

  void setState(bool state);

  void addSensor(UniquePointer<Sensor> sensor);

  virtual void printPurpose() const = 0;

protected:
  std::string type;
  std::string name;
  bool state;
  std::vector<UniquePointer<Sensor>> sensors;
};

} // namespace smarthome
#endif  // SMARTHOME_DEVICE_H_