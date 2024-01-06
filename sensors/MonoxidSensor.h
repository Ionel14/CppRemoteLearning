#ifndef NAGARROREMOTELEARNING_MONOXIDSENSOR_H
#define NAGARROREMOTELEARNING_MONOXIDSENSOR_H
#include "Sensor.h"

namespace smart_home {
    class MonoxideSensor : public Sensor {
    public:
        MonoxideSensor(const std::string &name);

        void generateRandomValue() override;
        double getMonoxideLevel() const;
        bool isDangerousLevel() const;

    private:
        static constexpr double DANGER_LEVEL = 50.0;
    };
}
#endif
