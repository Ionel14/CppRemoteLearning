#include "House.h"
#include <fstream>
#include <iostream>

namespace smart_home {
        House::House(int numRooms) {
            if (numRooms > MAX_ROOMS) {
                std::cerr << "Error: Number of rooms exceeds maximum number of rooms.\n";
                return;
            }

            initializeRooms();
        }

        void House::initializeRooms() {
            for (size_t i = 0; i < rooms.size(); ++i) {
                RoomType type = static_cast<RoomType>(i % 3);
                rooms[i] = Room(type);
            }
            for (auto& room : rooms) {
                room.addTemperatureSensor("TempSensor_" + std::to_string(room.getType()));
                room.addHumiditySensor("HumiditySensor_" + std::to_string(room.getType()));
                if (room.getType() == RoomType::KITCHEN) {
                    room.addMonoxideSensor("MonoxideSensor_" + std::to_string(room.getType()));
                }
                room.generateRandomSensorValues();
            }
        }

    void House::writeDataToFile() {
        std::ofstream outFile("house_data.txt");
        if (!outFile.is_open()) {
            std::cerr << "Unable to open file for writing." << std::endl;
            return;
        }

        for (const auto& room : rooms) {
            std::string roomTypeStr;
            if (room.getType() == LIVING_ROOM) {
                roomTypeStr = "Living Room";
            } else if (room.getType() == BEDROOM){
                roomTypeStr = "Bedroom";
            } else if (room.getType() == KITCHEN){
                roomTypeStr = "Kitchen";
            } else {
                roomTypeStr = "Unknown";
            }
            outFile << "Room Type: " << roomTypeStr << std::endl;

            const auto& sensors = room.getSensors();
            for (const auto& sensor : sensors) {
                outFile << "Sensor Type: " << getSensorTypeName(*sensor) << ", ";
                outFile << "Value: " << sensor->getValue() << std::endl;
            }
            outFile << std::endl;
        }

        outFile.close();
    }

    std::string House::getSensorTypeName(const Sensor &sensor) {
        const std::type_info& ti = typeid(sensor);
        if (ti == typeid(TemperatureSensor)) {
            return "TemperatureSensor";
        } else if (ti == typeid(HumiditySensor)) {
            return "HumiditySensor";
        } else if (ti == typeid(MonoxideSensor)) {
            return "MonoxideSensor";
        }
        return "UnknownSensor";
        }

}

