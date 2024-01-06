#ifndef NAGARROREMOTELEARNING_DEVICE_H
#define NAGARROREMOTELEARNING_DEVICE_H

#include <iostream>
#include "../utils/enums.h"

namespace smart_home {
    class Device {
    public:
        explicit Device(DeviceType deviceType);
        virtual ~Device() = default;
        std::string getDeviceType() const;
        std::string getDeviceStatus() const;
        virtual void setDeviceStatus(int status);
        void setDeviceType(DeviceType deviceType);
        void turnOn();
        void turnOff();
        virtual void displayStatuses() const = 0;
        virtual Device* clone() const = 0;
    private:
        int status = 0;
        DeviceType type;
    };
}

#endif
