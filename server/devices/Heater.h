#ifndef NAGARROREMOTELEARNING_HEATER_H
#define NAGARROREMOTELEARNING_HEATER_H

#include "Device.h"

namespace smart_home {
    class Heater : public Device {
    public:
        Heater();
        void setTemperature(int temperature);
        int getTemperature() const;
        std::string displayStatuses() const override;
        Heater* clone() const override;
    private:
        int temperature;
    };
}

#endif