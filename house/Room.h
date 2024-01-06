#ifndef NAGARROREMOTELEARNING_ROOM_H
#define NAGARROREMOTELEARNING_ROOM_H

#include <vector>
#include <memory>
#include "../sensors/TemperatureSensor.h"
#include "../sensors/HumiditySensor.h"
#include "../sensors/MonoxidSensor.h"
#include "../utils/enums.h"
#include "../sensors/Sensor.h"

namespace smart_home {
    class Room {
    public:
        Room();
        explicit Room(RoomType roomType);
        Room(const Room&) = default;
        Room& operator=(const Room&) = default;
        Room(Room&&) noexcept = default;
        Room& operator=(Room&&) noexcept = default;
        RoomType getType() const;
        void addTemperatureSensor(const std::string& name);
        void addHumiditySensor(const std::string& name);
        void addMonoxideSensor(const std::string& name);

        void generateRandomSensorValues();

        const std::vector<std::shared_ptr<Sensor>>& getSensors() const;


    private:
        RoomType type;
        std::vector<std::shared_ptr<Sensor>> sensors;
    };
}

#endif
