#include "Room.h"

namespace smart_home {
    Room::Room() : type(LIVING_ROOM) {}

    Room::Room(RoomType roomType) : type(roomType) {}

    RoomType Room::getType() const {
        return type;
    }

    void Room::addTemperatureSensor(const std::string& name) {
        sensors.emplace_back(std::make_shared<TemperatureSensor>(name));
    }

    void Room::addHumiditySensor(const std::string& name) {
        sensors.emplace_back(std::make_shared<HumiditySensor>(name));
    }

    void Room::addMonoxideSensor(const std::string& name) {
        sensors.emplace_back(std::make_shared<MonoxideSensor>(name));
    }

    void Room::generateRandomSensorValues() {
        for (auto& sensor : sensors) {
            sensor->generateRandomValue();
        }
    }

    const std::vector<std::shared_ptr<Sensor>>& Room::getSensors() const {
        return sensors;
    }
}
