#ifndef SMART_HOME_SENSORS_SENSOR_H_
#define SMART_HOME_SENSORS_SENSOR_H_

#include <any>
#include "rooms/room.h"
#include "memory"

namespace sensors {

// Rule of Zero
// Room should be handled separately as it is shared by devices and sensors
// and it can exist even if there are no sensors or devices

class Sensor {
  public:
    Sensor(std::shared_ptr<rooms::Room> room);

    inline std::shared_ptr<rooms::Room> GetRoom() {
      return room;
    }

    virtual std::any GetData() = 0;

    virtual void SetData(const std::any &data) = 0;

  protected:
    std::shared_ptr<rooms::Room> room;
};

} // namespace sensors

#endif // SMART_HOME_SENSORS_SENSOR_H_