#ifndef SMART_HOME_SENSORS_TEMPERATURE_SENSOR_H_
#define SMART_HOME_SENSORS_TEMPERATURE_SENSOR_H_

#include "sensor.h"
#include "rooms/room.h"

namespace sensors {

// Rule of Zero

class TemperatureSensor : public Sensor {
  public:
    TemperatureSensor(std::shared_ptr<rooms::Room> room): Sensor(room) {}

    inline std::any GetData() {
        std::lock_guard<std::mutex> data_lock(data_mutex);
        return current_temperature;
    }

    inline void SetData(const std::any &data) {
        std::lock_guard<std::mutex> data_lock(data_mutex);
        current_temperature = std::any_cast<float>(data);
    }

  private:
    float current_temperature = 0;
};

} // namespace sensors

#endif // SMART_HOME_SENSORS_TEMPERATURE_SENSOR_H_