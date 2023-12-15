#ifndef SMART_HOME_DEVICES_AC_UNIT_H_
#define SMART_HOME_DEVICES_AC_UNIT_H_

#include "../rooms/room.h"
#include "device.h"

namespace devices {

// Rule of Zero

class AcUnit : public Device {
  public:
    AcUnit(rooms::Room* room): Device(room) {}

    rooms::Room* GetRoom() override {
        return room;
    }

    inline int GetFanSpeed() {
        return fan_speed;
    }

    void SetFanSpeed(int value);

    inline float GetDesiredTemperature() {
        return desired_temperature;
    }

    void SetDesiredTemperature(float value);

    void SetOnAuto(sensors::Sensor* sensor) override;

  private:
    unsigned char fan_speed = 0;
    float desired_temperature = 21;
};

} // namespace devices

#endif // SMART_HOME_DEVICES_AC_UNIT_H_