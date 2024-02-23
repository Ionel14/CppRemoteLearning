#ifndef NAGARROREMOTELEARNING_STATUSPRINTER_H
#define NAGARROREMOTELEARNING_STATUSPRINTER_H

#include <vector>
#include "../devices/Device.h"
#include "../sensors/Sensor.h"

namespace smart_home {
    class StatusPrinter {
    public:
        static void printDeviceStatus(const std::vector<const Device*> &devices);
        static void printSensorDataFromRoom(RoomType roomType);
    };
}

#endif
