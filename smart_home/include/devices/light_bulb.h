#ifndef SMART_HOME_DEVICES_LIGHT_BULB_H_
#define SMART_HOME_DEVICES_LIGHT_BULB_H_

#include "rooms/room.h"
#include "device.h"

namespace devices {

// Rule of Zero

class LightBulb : public Device {
  public:
    LightBulb(rooms::Room* room): Device(room) {}

    void SetIsOn(bool value) override;

    void SetOnAuto(sensors::Sensor* sensor) override;
};

} // namespace devices

#endif // SMART_HOME_DEVICES_LIGHT_BULB_H_