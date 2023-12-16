#include "Room.h"

namespace SmartHome {
    Room::Room() : type(LIVING_ROOM) {
        sensors.reserve(0);
    }

    Room::Room(int numSensors, RoomType roomType) : type(roomType) {
        sensors.reserve(numSensors);
        sensors.emplace_back("Temperature", CELSIUS);
        sensors.emplace_back("Humidity", PERCENT);
    }

    RoomType Room::getType() const {
        return type;
    }

    const std::vector<Sensor> &Room::getSensors() const {
        return sensors;
    }

    void Room::generateRandomSensorValues() {
        for (Sensor &sensor: sensors) {
            sensor.generateRandomValue();
        }
    }
}