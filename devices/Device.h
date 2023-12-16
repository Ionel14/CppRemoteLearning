#ifndef NAGARROREMOTELEARNING_DEVICE_H
#define NAGARROREMOTELEARNING_DEVICE_H

#include <iostream>
#include "../utils/enums.h"

namespace SmartHome {
    class Device {
    public:
        explicit Device(DeviceType deviceType);
        std::string getDeviceType() const;
        std::string getDeviceStatus() const;
        void setDeviceStatus(int status);
        void setDeviceType(DeviceType deviceType);
        void turnOn();
        void turnOff();
        void displayStatuses() const;
    private:
        int status = 0;
        DeviceType type;
    };
}
#endif
