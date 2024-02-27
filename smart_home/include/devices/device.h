#ifndef SMART_HOME_DEVICES_DEVICE_H_
#define SMART_HOME_DEVICES_DEVICE_H_

#include "rooms/room.h"
#include "sensors/sensor.h"

namespace devices {

// Rule of Zero
// Room pointer should be handled separately as it is shared by devices and sensors

class Device {
  public:
    Device(std::shared_ptr<rooms::Room> room);

    inline bool GetIsOn() {
      return is_on;
    }

    virtual void SetIsOn(bool value);

    inline std::shared_ptr<rooms::Room> GetRoom() {
      return room;
    }

    virtual void SetOnAuto(sensors::Sensor* sensor) = 0;

  protected:
    bool is_on = false;
    std::shared_ptr<rooms::Room> room;
};

} // namespace devices

#endif // SMART_HOME_DEVICES_DEVICE_H_