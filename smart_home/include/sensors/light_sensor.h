#ifndef SMART_HOME_SENSORS_LIGHT_SENSOR_H_
#define SMART_HOME_SENSORS_LIGHT_SENSOR_H_

#include "sensor.h"

namespace sensors {
  
// Rule of Zero

class LightSensor : public Sensor {
  public:
    LightSensor(std::shared_ptr<rooms::Room> room): Sensor(room) {}

    inline std::any GetData() override {
        return light_level;
    }

    inline void SetData(const std::any &data) override {
        light_level = std::any_cast<uint8_t>(data);
    }

  private:
    uint8_t light_level = 100;
};

} // namespace sensors

#endif // SMART_HOME_SENSORS_LIGHT_SENSOR_H_