#include <stdexcept>
#include "sensors/sensor.h"

namespace sensors {
    Sensor::Sensor(std::shared_ptr<rooms::Room> room): room(room) {
        if (!room) {
            throw std::runtime_error("Room is null.\n");
        }
    }
} // namespace sensors