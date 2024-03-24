#ifndef AIRCONDITIONER_H
#define AIRCONDITIONER_H

#include "Device.h"

namespace smart_home {
    enum class ACMode { COOLING, HEATING };

    class AirConditioner : public Device {
    public:
        AirConditioner();
        void setTemperature(int temperature);
        void setMode(ACMode mode);
        int getTemperature() const;
        ACMode getMode() const;
        std::string displayStatuses() const override;
        AirConditioner* clone() const override;

    private:
        int temperature;
        ACMode mode;
    };
}

#endif

