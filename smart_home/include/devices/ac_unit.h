#ifndef SMART_HOME_DEVICES_AC_UNIT_H_
#define SMART_HOME_DEVICES_AC_UNIT_H_

#include "rooms/room.h"
#include "device.h"

namespace devices {

// Rule of Zero

class AcUnit : public Device {
  public:
    AcUnit(rooms::Room* room): Device(room) {}

    void SetIsOn(bool value) override;

    inline uint8_t GetFanSpeed() {
        return fan_speed;
    }

    void SetFanSpeed(uint8_t value);

    inline float GetDesiredTemperature() {
        return desired_temperature;
    }

    void SetDesiredTemperature(float value);

    void SetOnAuto(sensors::Sensor* sensor) override;

  private:
    uint8_t fan_speed = 0;
    float desired_temperature = 21;
};

} // namespace devices

#endif // SMART_HOME_DEVICES_AC_UNIT_H_