#include "House.h"
#include <fstream>
#include <iostream>

namespace smart_home {
    House::House(int numRooms) {
        if (numRooms > ROOM_NUM) {
            std::cerr << "Error: Number of rooms exceeds maximum number of rooms.\n";
            return;
        }
        
        initializeRooms();
    }

    void House::initializeRooms() {
        for (size_t i = 0; i < rooms.size(); ++i) {
            auto type = static_cast<RoomType>(i % ROOM_NUM);
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
    
    std::array<Room, ROOM_NUM> House::getRooms() const {
        return rooms;
    }

    Room House::getRoom(RoomType roomType) const {
        for (const auto& room : rooms) {
            if (room.getType() == roomType) {
                return room;
            }
        }
        std::cerr << "Room not found." << std::endl;
        return {};
    }

    void House::regenerateSensorValue(){
        for (const auto& room : rooms){
            room.generateRandomSensorValues();
        }
    }

    void House::writeDataToFile() {
        std::ofstream outFile("house_data.txt");
        if (!outFile.is_open()) {
            std::cerr << "Unable to open file for writing." << std::endl;
            return;
        }

        try {
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
        } catch (const std::ios_base::failure& e) {
            std::cerr << "I/O error while writing data: " << e.what() << std::endl;
            outFile.close();
            return;
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

