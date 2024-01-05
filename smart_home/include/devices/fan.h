#ifndef SMART_HOME_DEVICES_FAN_H_
#define SMART_HOME_DEVICES_FAN_H_

#include "rooms/room.h"
#include "device.h"

namespace devices {

// Rule of Zero

class Fan : public Device {
  public:
    Fan(rooms::Room* room): Device(room) {}

    void SetIsOn(bool value) override;

    inline uint8_t GetSpeed() {
        return speed;
    }

    void SetSpeed(uint8_t value);

    inline bool GetIsRotating() {
        return is_rotating;
    }

    void SetIsRotating(bool value);

    void SetOnAuto(sensors::Sensor* sensor) override;

  private:
    uint8_t speed = 0;
    bool is_rotating = false;
};

} // namespace devices

#endif // SMART_HOME_DEVICES_FAN_H_