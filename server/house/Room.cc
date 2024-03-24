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

    void Room::removeTemperatureSensor(const std::string& name) {
       for (const auto& sensor : getSensors()) {
              if (sensor->getName() == name) {
                  sensors.erase(std::remove(sensors.begin(), sensors.end(), sensor), sensors.end());
                  return;
              }
       }
        std::cerr << "Temperature sensor not found." << std::endl;
    }

    void Room::removeHumiditySensor(const std::string& name) {
        for (const auto& sensor : getSensors()) {
            if (sensor->getName() == name) {
                sensors.erase(std::remove(sensors.begin(), sensors.end(), sensor), sensors.end());
                return;
            }
        }
        std::cerr << "Humidity sensor not found." << std::endl;
    }

    void Room::removeMonoxideSensor(const std::string& name) {
        for (const auto& sensor : getSensors()) {
            if (sensor->getName() == name) {
                sensors.erase(std::remove(sensors.begin(), sensors.end(), sensor), sensors.end());
                return;
            }
        }
        std::cerr << "Monoxide sensor not found." << std::endl;
    }

    void Room::generateRandomSensorValues() const {
        for (auto& sensor : sensors) {
            sensor->generateRandomValue();
        }
    }

    std::string Room::displaySensorStatuses() const {
        std::string result;
        for (const auto& sensor : sensors) {
            result += sensor->displayStatus() + "\n";
        }
        return result;
    }

    const std::vector<std::shared_ptr<Sensor>>& Room::getSensors() const {
        std::cout << "Getting sensors." << std::endl;
        return sensors;
    }
}
