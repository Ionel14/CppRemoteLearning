#ifndef SECURITY_DEVICE_H
#define SECURITY_DEVICE_H

#include "device.h"

namespace smartHome {
    class SecurityDevice : public Device {
    public:
        SecurityDevice(const std::string& deviceId, bool status, const std::vector<Sensor*>& sensors);

        void powerOn() override;

        void powerOff() override;
    };
}

#endif // SECURITY_DEVICE_H
