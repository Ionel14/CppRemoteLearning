#ifndef THERMOSTAT_DEVICE_H
#define THERMOSTAT_DEVICE_H

#include "device.h"

namespace smartHome {
    class ThermostatDevice : public Device {
    public:
        ThermostatDevice(const std::string& deviceId, bool status, const std::vector<Sensor*>& sensors);

        void powerOn() override;

        void powerOff() override;
    };
}

#endif // THERMOSTAT_DEVICE_H
