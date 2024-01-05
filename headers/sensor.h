#ifndef SMARTHOME_SENSOR_H_
#define SMARTHOME_SENSOR_H_

#include <iostream>

namespace smarthome {

class Sensor {
public:
  Sensor(const std::string& name, int value);
  Sensor(const Sensor& other);
  Sensor(const Sensor&& other);
  
  Sensor& operator=(const Sensor& other);
  Sensor& operator=(const Sensor&& other);

  ~Sensor();

  std::string getName();
  int getValue();
  std::string getType();

  void setValue(int value);

  virtual void printPurpose() = 0;

protected:  
  std::string type;
  std::string name;
  int value;
};

} // namespace smarthome
#endif  // SMARTHOME_SENSOR_H_