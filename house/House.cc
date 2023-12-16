
#include "House.h"
#include <fstream>
#include <vector>

namespace SmartHome {
    House::House(int numRooms, int numSensorsPerRoom) {
        for (int i = 0; i < numRooms; ++i) {
            auto type = static_cast<RoomType>(i % 3);
            rooms[i] = Room(numSensorsPerRoom, type);
        }
    }

    void House::writeDataToFile() {
        std::ofstream outFile("house_data.txt");
        if (!outFile.is_open()) {
            return;
        }

        for (Room room: rooms) {
            room.generateRandomSensorValues();
            outFile << "Room Type: ";
            switch (room.getType()) {
                case LIVING_ROOM:
                    outFile << "Living Room";
                    break;
                case BEDROOM:
                    outFile << "Bedroom";
                    break;
                case KITCHEN:
                    outFile << "Kitchen";
                    break;
            }
            outFile << std::endl;

            for (const Sensor &sensor: room.getSensors()) {
                outFile << sensor.getName() << ": " << sensor.getValue()
                        << " (" << (sensor.getUnit() == CELSIUS ? "Celsius" :
                                    (sensor.getUnit() == PERCENT ? "Percent" : "Other")) << ")"
                        << std::endl;
            }
        }

        outFile.close();
    }
}