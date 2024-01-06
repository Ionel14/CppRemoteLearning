#ifndef NAGARROREMOTELEARNING_LIGHT_H
#define NAGARROREMOTELEARNING_LIGHT_H

#include "Device.h"

namespace smart_home {
    class Light : public Device {
    public:
        Light();
        void setBrightness(int brightness);
        int getBrightness() const;
        void displayStatuses() const override;
        Light* clone() const override;
    private:
        int brightness;
    };
}

#endif
