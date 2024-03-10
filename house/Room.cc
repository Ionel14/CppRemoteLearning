#include <iostream>
#include "Room.h"

namespace smart_home {
    Room::Room() : type(LIVING_ROOM) {}

    Room::Room(RoomType roomType) : type(roomType) {}

    RoomType Room::getType() const {
        return type;
    }

    void Room::addTemperatureSensor(const std::string& name) {
        try {
            sensors.emplace_back(std::make_shared<TemperatureSensor>(name));
         } catch (const std::bad_alloc& e) {
             std::cerr << "Failed to add temperature sensor due to memory allocation error: " << e.what() << std::endl;
             exit(1);
         }
    }

    void Room::addHumiditySensor(const std::string& name) {
        try {
            sensors.emplace_back(std::make_shared<HumiditySensor>(name));
        } catch (const std::bad_alloc& e) {
            std::cerr << "Failed to add humidity sensor due to memory allocation error: " << e.what() << std::endl;
            exit(1);
        }
    }

    void Room::addMonoxideSensor(const std::string& name) {
        try {
            sensors.emplace_back(std::make_shared<MonoxideSensor>(name));
        } catch (const std::bad_alloc& e) {
            std::cerr << "Failed to add monoxide sensor due to memory allocation error: " << e.what() << std::endl;
            exit(1);
        }
    }

    void Room::generateRandomSensorValues() const {
        for (auto& sensor : sensors) {
            sensor->generateRandomValue();
        }
    }

    const std::vector<std::shared_ptr<Sensor>>& Room::getSensors() const {
        return sensors;
    }
}
