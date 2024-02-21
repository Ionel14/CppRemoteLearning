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

  virtual ~Sensor();

  std::string getName() const;
  int getValue() const;
  std::string getType() const;
  int getMinValue() const;
  int getMaxValue() const;

  void setValue(int value);

  virtual void printPurpose() const = 0;

protected:  
  std::string type;
  std::string name;
  int value;
  int minValue, maxValue;
};

} // namespace smarthome
#endif  // SMARTHOME_SENSOR_H_