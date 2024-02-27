#ifndef SMART_HOME_SENSORS_PRESENCE_SENSOR_H_
#define SMART_HOME_SENSORS_PRESENCE_SENSOR_H_

#include "sensor.h"

namespace sensors {
  
// Rule of Zero

class PresenceSensor : public Sensor {
  public:
    PresenceSensor(std::shared_ptr<rooms::Room> room): Sensor(room) {}

    inline std::any GetData() override {
        return is_any_presence;
    }

    inline void SetData(const std::any &data) override {
        is_any_presence = std::any_cast<bool>(data);
    }

  private:
    bool is_any_presence = false;
};

} // namespace sensors

#endif // SMART_HOME_SENSORS_PRESENCE_SENSOR_H_